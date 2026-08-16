import re
import shutil
from pathlib import Path

import requests
from bs4 import BeautifulSoup
from dotenv import dotenv_values
from markdownify import markdownify


REPO = Path(__file__).resolve().parent
PROBLEMS = REPO / "problems"
CONFIG = Path.home() / ".leetcode_sync" / ".env"

GRAPHQL_URL = "https://leetcode.com/graphql"

QUERY = """
query questionData($titleSlug: String!) {
    question(titleSlug: $titleSlug) {
        questionFrontendId
        title
        titleSlug
        content
        difficulty
        exampleTestcases
        topicTags {
            name
        }
    }
}
"""


def load_credentials():
    if not CONFIG.exists():
        raise RuntimeError(f"LeetCode config not found: {CONFIG}")

    env = dotenv_values(CONFIG)

    session = env.get("LEETCODE_SESSION")
    csrf = env.get("CSRFTOKEN")

    if not session or not csrf:
        raise RuntimeError("Missing LeetCode credentials")

    return session, csrf


def fetch_question(slug, session, csrf):
    headers = {
        "Content-Type": "application/json",
        "Referer": "https://leetcode.com/",
        "User-Agent": "Mozilla/5.0",
        "x-csrftoken": csrf,
    }

    cookies = {
        "LEETCODE_SESSION": session,
        "csrftoken": csrf,
    }

    payload = {
        "operationName": "questionData",
        "variables": {"titleSlug": slug},
        "query": QUERY,
    }

    response = requests.post(
        GRAPHQL_URL,
        json=payload,
        headers=headers,
        cookies=cookies,
        timeout=30,
    )

    response.raise_for_status()

    data = response.json()

    if "errors" in data:
        raise RuntimeError(data["errors"])

    question = data["data"]["question"]

    if question is None:
        raise RuntimeError(f"Question not found: {slug}")

    return question


def clean_markdown(content):
    soup = BeautifulSoup(content, "html.parser")

    text = markdownify(
        str(soup),
        heading_style="ATX",
    )

    return re.sub(r"\n{3,}", "\n\n", text).strip()


def is_placeholder(readme):
    if not readme.exists():
        return True

    return (
        "Add any notes or explanations about your solution here."
        in readme.read_text(encoding="utf-8")
    )


def build_readme(question):
    number = question["questionFrontendId"]
    title = question["title"]
    slug = question["titleSlug"]
    difficulty = question["difficulty"]

    content = clean_markdown(question["content"])

    tags = [
        tag["name"]
        for tag in question.get("topicTags", [])
    ]

    examples = question.get("exampleTestcases") or ""

    lines = [
        f"# {number}. {title}",
        "",
        f"**Difficulty:** {difficulty}",
        "",
        f"**LeetCode:** https://leetcode.com/problems/{slug}/",
        "",
    ]

    if tags:
        lines.extend([
            "**Topics:** " + ", ".join(tags),
            "",
        ])

    lines.extend([
        "## Problem",
        "",
        content,
        "",
    ])

    if examples:
        lines.extend([
            "## Example Testcases",
            "",
            "```text",
            examples.strip(),
            "```",
            "",
        ])

    return "\n".join(lines)


def build_directory_name(question):
    number = int(question["questionFrontendId"])
    slug = question["titleSlug"]

    return f"{number:04d}-{slug}"


def get_submission_directories():
    """
    Return directories created by leetcode-sync.

    We intentionally handle:
        problems/easy/foo
        problems/medium/bar
        problems/hard/baz

    as well as an unnumbered top-level directory if one appears.
    """

    directories = []

    for difficulty in ("easy", "medium", "hard"):
        difficulty_dir = PROBLEMS / difficulty

        if not difficulty_dir.is_dir():
            continue

        for problem_dir in difficulty_dir.iterdir():
            if problem_dir.is_dir():
                directories.append(problem_dir)

    # Also handle unexpected unnumbered top-level directories.
    for problem_dir in PROBLEMS.iterdir():
        if not problem_dir.is_dir():
            continue

        if problem_dir.name in ("easy", "medium", "hard"):
            continue

        if not re.match(r"^\d{4}-", problem_dir.name):
            directories.append(problem_dir)

    return directories


def merge_into_numbered_directory(source_dir, target_dir):
    """
    Move the latest LeetCode solution into the canonical numbered directory.

    Existing README is preserved.
    """

    target_dir.mkdir(parents=True, exist_ok=True)

    source_solution = source_dir / "solution.c"
    target_solution = target_dir / "solution.c"

    if source_solution.exists():
        # Latest LeetCode submission becomes the canonical solution.
        shutil.move(
            str(source_solution),
            str(target_solution),
        )

    # Remove the generated duplicate directory.
    if source_dir.exists():
        shutil.rmtree(source_dir)


def cleanup_empty_difficulty_dirs():
    for difficulty in ("easy", "medium", "hard"):
        directory = PROBLEMS / difficulty

        if not directory.exists():
            continue

        try:
            directory.rmdir()
            print(f"Removed empty directory: problems/{difficulty}")
        except OSError:
            # Non-empty directory means something unexpected remains.
            pass


def process_submission_directory(source_dir, session, csrf):
    slug = source_dir.name.replace("_", "-")

    print(f"Fetching: {slug}")

    question = fetch_question(
        slug,
        session,
        csrf,
    )

    target_name = build_directory_name(question)
    target_dir = PROBLEMS / target_name

    target_exists = target_dir.exists()

    if source_dir != target_dir:
        if target_exists:
            print(
                f"  Merging: {source_dir} -> {target_name}"
            )
        else:
            print(
                f"  Creating: {target_name}"
            )

        merge_into_numbered_directory(
            source_dir,
            target_dir,
        )

    readme = target_dir / "README.md"

    if is_placeholder(readme):
        readme.write_text(
            build_readme(question),
            encoding="utf-8",
        )

        print(f"  README updated: {target_name}")

    return target_dir


def process_existing_numbered_directories(session, csrf):
    """
    Only generate missing/placeholder READMEs.

    Existing complete READMEs are never overwritten.
    """

    updated = 0
    failed = 0

    for directory in PROBLEMS.iterdir():
        if not directory.is_dir():
            continue

        match = re.match(
            r"^(\d{4})-(.+)$",
            directory.name,
        )

        if not match:
            continue

        readme = directory / "README.md"

        if not is_placeholder(readme):
            continue

        slug = match.group(2)

        try:
            print(f"Fetching README: {slug}")

            question = fetch_question(
                slug,
                session,
                csrf,
            )

            readme.write_text(
                build_readme(question),
                encoding="utf-8",
            )

            updated += 1

        except Exception as error:
            failed += 1
            print(f"  ERROR: {error}")

    return updated, failed


def main():
    session, csrf = load_credentials()

    renamed = 0
    readmes_updated = 0
    failed = 0

    # --------------------------------------------------
    # Process the folders freshly created by leetcode-sync
    # --------------------------------------------------

    submission_dirs = get_submission_directories()

    print(
        f"New submission directories: {len(submission_dirs)}"
    )

    for source_dir in submission_dirs:
        try:
            process_submission_directory(
                source_dir,
                session,
                csrf,
            )

            renamed += 1

        except Exception as error:
            failed += 1
            print(
                f"  ERROR processing {source_dir.name}: {error}"
            )

    cleanup_empty_difficulty_dirs()

    # --------------------------------------------------
    # Generate missing READMEs for numbered directories
    # --------------------------------------------------

    updated, readme_failed = process_existing_numbered_directories(
        session,
        csrf,
    )

    readmes_updated += updated
    failed += readme_failed

    # --------------------------------------------------
    # Final state
    # --------------------------------------------------

    numbered_dirs = [
        directory
        for directory in PROBLEMS.iterdir()
        if directory.is_dir()
        and re.match(r"^\d{4}-", directory.name)
    ]

    solutions = list(PROBLEMS.glob("*/solution.c"))

    print()
    print(f"Numbered problems: {len(numbered_dirs)}")
    print(f"C solutions:       {len(solutions)}")
    print(f"Processed:          {renamed}")
    print(f"READMEs updated:    {readmes_updated}")
    print(f"Failed:             {failed}")

    if failed:
        raise SystemExit(1)


if __name__ == "__main__":
    main()

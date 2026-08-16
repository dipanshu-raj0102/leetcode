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
        heading_style="ATX"
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
        lines += [
            "**Topics:** " + ", ".join(tags),
            "",
        ]

    lines += [
        "## Problem",
        "",
        content,
        "",
    ]

    if examples:
        lines += [
            "## Example Testcases",
            "",
            "```text",
            examples.strip(),
            "```",
            "",
        ]

    return "\n".join(lines)


def directory_name(question):
    number = int(question["questionFrontendId"])
    slug = question["titleSlug"]

    return f"{number:04d}-{slug}"


def move_solution_to_numbered_dir(old_dir, new_dir):
    old_solution = old_dir / "solution.c"
    new_solution = new_dir / "solution.c"

    if old_solution.exists():
        # The latest LeetCode submission wins.
        shutil.move(str(old_solution), str(new_solution))

    # Remove the old unnumbered directory.
    if old_dir.exists():
        shutil.rmtree(old_dir)


def process_problem(problem_dir, session, csrf):
    name = problem_dir.name

    numbered = re.match(r"^(\d{4})-(.+)$", name)

    if numbered:
        # Already numbered.
        if not is_placeholder(problem_dir / "README.md"):
            return "skip"

        slug = numbered.group(2)

    else:
        # Newly created by leetcode-sync.
        slug = name

    slug = slug.replace("_", "-")

    print(f"Fetching: {slug}")

    question = fetch_question(
        slug,
        session,
        csrf,
    )

    target = PROBLEMS / directory_name(question)

    # --------------------------------------------------
    # Unnumbered directory created by leetcode-sync
    # --------------------------------------------------

    if problem_dir != target:

        if target.exists():
            print(
                f"  Merging: {name} -> {target.name}"
            )

            move_solution_to_numbered_dir(
                problem_dir,
                target,
            )

        else:
            problem_dir.rename(target)

            print(
                f"  Renamed: {name} -> {target.name}"
            )

    # --------------------------------------------------
    # Generate README only if missing/placeholder
    # --------------------------------------------------

    readme = target / "README.md"

    if is_placeholder(readme):
        readme.write_text(
            build_readme(question),
            encoding="utf-8",
        )

        return "updated"

    return "renamed"


def main():
    session, csrf = load_credentials()

    directories = [
        p
        for p in PROBLEMS.iterdir()
        if p.is_dir()
    ]

    print(f"Total directories: {len(directories)}")

    renamed = 0
    updated = 0
    skipped = 0
    failed = 0

    for directory in directories:
        try:
            result = process_problem(
                directory,
                session,
                csrf,
            )

            if result == "renamed":
                renamed += 1
            elif result == "updated":
                updated += 1
            else:
                skipped += 1

        except Exception as error:
            failed += 1
            print(f"  ERROR: {error}")

    print()
    print(f"Renamed: {renamed}")
    print(f"Updated: {updated}")
    print(f"Skipped: {skipped}")
    print(f"Failed:  {failed}")


if __name__ == "__main__":
    main()

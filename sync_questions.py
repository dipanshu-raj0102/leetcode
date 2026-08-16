import re
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
        "variables": {
            "titleSlug": slug
        },
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

    content = readme.read_text(encoding="utf-8")

    return (
        "Add any notes or explanations about your solution here."
        in content
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


def rename_problem_directory(old_dir, question):
    new_name = build_directory_name(question)
    new_dir = PROBLEMS / new_name

    if old_dir == new_dir:
        return new_dir

    if new_dir.exists():
        print(f"  Target already exists: {new_name}")

        for item in old_dir.iterdir():
            destination = new_dir / item.name

            if not destination.exists():
                item.rename(destination)

        try:
            old_dir.rmdir()
        except OSError:
            pass

        return new_dir

    old_dir.rename(new_dir)

    print(f"  Renamed: {old_dir.name} -> {new_name}")

    return new_dir


def main():
    session, csrf = load_credentials()

    problem_dirs = [
        directory
        for directory in PROBLEMS.iterdir()
        if directory.is_dir()
    ]

    print(f"Total problems: {len(problem_dirs)}")

    renamed = 0
    updated = 0
    failed = 0

    for problem_dir in problem_dirs:

        name = problem_dir.name

        # Already numbered: 0001-two-sum
        already_numbered = bool(
            re.match(r"^\d{4}-", name)
        )

        # Convert directory name to LeetCode slug.
        if already_numbered:
            slug = name[5:]
        else:
            slug = name

        slug = slug.replace("_", "-")

        readme = problem_dir / "README.md"

        needs_readme = is_placeholder(readme)

        # Existing numbered directory with complete README:
        # nothing to do.
        if already_numbered and not needs_readme:
            continue

        try:
            print(f"Fetching: {slug}")

            question = fetch_question(
                slug,
                session,
                csrf,
            )

            # ----------------------------------------
            # Rename unnumbered directory
            # ----------------------------------------

            current_dir = problem_dir

            if not already_numbered:
                current_dir = rename_problem_directory(
                    problem_dir,
                    question,
                )

                renamed += 1

            # ----------------------------------------
            # Generate README only if necessary
            # ----------------------------------------

            if needs_readme:
                new_readme = current_dir / "README.md"

                new_readme.write_text(
                    build_readme(question),
                    encoding="utf-8",
                )

                updated += 1

        except Exception as error:
            failed += 1
            print(f"  ERROR: {error}")

    print()
    print(f"Renamed: {renamed}")
    print(f"Updated: {updated}")
    print(f"Failed:  {failed}")


if __name__ == "__main__":
    main()

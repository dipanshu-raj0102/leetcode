#!/usr/bin/env fish

set -l ROOT (dirname (status --current-filename))
set -l PYTHON "$ROOT/.venv/bin/python"
set -l SYNC "$ROOT/.venv/bin/leetcode-sync"

cd $ROOT

# --------------------------------------------------
# Sync LeetCode submissions
# --------------------------------------------------

echo "==> Syncing LeetCode submissions..."

$SYNC --sync

if test $status -ne 0
    echo "ERROR: LeetCode submission sync failed."
    exit 1
end

# --------------------------------------------------
# Flatten difficulty directories
# --------------------------------------------------

echo "==> Flattening problem directories..."

for difficulty in easy medium hard

    set -l DIR "$ROOT/problems/$difficulty"

    if not test -d "$DIR"
        continue
    end

    for problem in "$DIR"/*

        if not test -d "$problem"
            continue
        end

        set -l name (basename "$problem")
        set -l destination "$ROOT/problems/$name"

        if test -e "$destination"

            echo "  Merging: $name"

            cp -rn "$problem"/. "$destination"/
            rm -rf "$problem"

        else

            echo "  Moving: $name"
            mv "$problem" "$destination"

        end
    end

    rmdir "$DIR" 2>/dev/null
end

# --------------------------------------------------
# Generate question README + numbered directories
# --------------------------------------------------

echo "==> Updating problem statements..."

$PYTHON "$ROOT/sync_questions.py"

if test $status -ne 0
    echo "ERROR: Question sync failed."
    exit 1
end

# --------------------------------------------------
# Git
# --------------------------------------------------

echo "==> Checking Git changes..."

git add README.md problems sync_questions.py sync.fish .gitignore

if git diff --cached --quiet
    echo "Nothing new to commit."
    exit 0
end

echo "==> Committing changes..."

git commit -m "Sync LeetCode solutions"

if test $status -ne 0
    echo "ERROR: Git commit failed."
    exit 1
end

# --------------------------------------------------
# Push
# --------------------------------------------------

echo "==> Pushing to GitHub..."

git push

if test $status -ne 0
    echo "ERROR: Git push failed."
    exit 1
end

echo "==> LeetCode -> GitHub sync complete."

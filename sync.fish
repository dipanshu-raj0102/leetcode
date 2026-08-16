#!/usr/bin/env fish

set -l ROOT (dirname (status --current-filename))
set -l PYTHON "$ROOT/.venv/bin/python"
set -l SYNC "$ROOT/.venv/bin/leetcode-sync"

cd $ROOT

echo "==> Syncing LeetCode submissions..."

$SYNC --sync

if test $status -ne 0
    echo "ERROR: LeetCode submission sync failed."
    exit 1
end

echo "==> Organizing problems..."

$PYTHON "$ROOT/sync_questions.py"

if test $status -ne 0
    echo "ERROR: Problem organization failed."
    exit 1
end

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

echo "==> Pushing to GitHub..."

git push

if test $status -ne 0
    echo "ERROR: Git push failed."
    exit 1
end

echo "==> LeetCode -> GitHub sync complete."

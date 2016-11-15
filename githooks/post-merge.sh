#!/bin/sh

echo "Doing post merge"

HOOKS_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

#bash $HOOKS_DIR/pre-commit

git commit --amend --no-edit

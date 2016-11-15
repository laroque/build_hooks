#!/bin/sh

echo "doing pre-commit hook"
HOOKS_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

if [ $(git symbolic-ref --short HEAD) == "master" ]
then
  echo "on master, bumping"
  python $HOOKS_DIR/bump_version.py
  git add VERSION
else
  echo "not on master, not bumping"
fi

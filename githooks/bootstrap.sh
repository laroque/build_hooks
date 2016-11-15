#!/bin/sh

if [ ! -d "./.git" ]
then
    echo "not in the top level of a git repo"
    exit 1
fi

rel_pa="`dirname \"$0\"`"
abs_pa="`( cd \"$rel_pa\" && pwd )`"

ln -s $abs_pa/post-merge.sh .git/hooks/post-merge
ln -s $abs_pa/pre-commit.sh .git/hooks/pre-commit
ln -s $abs_pa/post-commit.sh .git/hooks/post-commit
ln -s $abs_pa/bump_version.py .git/hooks/bump_version.py

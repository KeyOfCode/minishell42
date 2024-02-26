#!/bin/bash
# force remove file from git repository.
git filter-branch --index-filter 'git update-index --remove test.sh' HEAD
git push --force --verbose --dry-run --set-upstream origin executor
git push --force --set-upstream origin executor
#!/bin/bash
set -x
dir=${1:-\.}
git add $dir
git commit $dir -m update
git push origin main

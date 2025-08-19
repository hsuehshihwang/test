#!/bin/bash
file=${1:-sample.md}
# npx markmap-cli@0.14 --no-open ${file}
[ -f $file ] && markmap --no-open ${file}

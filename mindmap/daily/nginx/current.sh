#!/bin/bash
curr=$(pwd)
echo "Current Folder: .${curr#*/tree}"
echo -ne "Current Sub-folders: "
find . -maxdepth 1 -type d ! -path . ! -path "*.git*" | sed -e "s%^./%%" | awk '{printf $1" "} END{printf "\n"}'
howdeep=$(find . -type d | awk -F/ '{print NF-1}' | sort -n | tail -1)
# echo howdeep=$howdeep

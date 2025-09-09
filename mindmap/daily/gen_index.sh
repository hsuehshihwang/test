#!/bin/bash

# echo $(dirname $(realpath ${BASH_SOURCE[0]}))

s=$(realpath ${BASH_SOURCE[0]})
d=$(dirname $(realpath ${BASH_SOURCE[0]}))
ds=$(find $d -type d ! -path "*.git*" -o -type l)

# echo s=$s, d=$d ds=$ds

gen(){
  rm -rf README.md
  mds=$(find . -maxdepth 1 -name "*.md")
  if [ -z "$mds" ]; then
cat << EOF > header.md
---
markmap:
  color:
    - blue
  initialExpandLevel: 4
  # other options
---

# [go back](../index.html)
EOF
  fi
  if [ -f "header.md" ]; then
    cat header.md > README.md
  fi
  mds=$(find . -maxdepth 1 -name "*.md" | sed "/header.md/d" | sed "/README.md/d")
  for md in $mds; do
    cat $md >> README.md
  done
  l=$(find . -maxdepth 4 -type d ! -path "*.git*" -o -type l | sed -e 's%^./%%' -e '/^.$/d')
  for li in $l; do
    # echo "# [${li}](${li}/index.html)" >> README.md
    echo "${li}" | awk -F "/" 'BEGIN{n=0} { for(i=1;i<=NF;i++){ printf "#"; if(i==NF) print " ["$i"]""("$0"/index.html)"; } }' >> README.md
  done
  markmap --no-open README.md -o index.html
}

for di in $ds; do
  ( cd $di; \
    gen\
    cd - \
  ) #> /dev/null 2>&1
done


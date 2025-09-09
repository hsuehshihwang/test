#!/bin/bash
s=$(realpath ${BASH_SOURCE[0]})
d=$(dirname $(realpath ${BASH_SOURCE[0]}))
longspace=$(printf "%0.s " {1..100})
depth=0
currdir(){
  cd $1
  printf "%.*s|-> %s\n" "$depth" "$longspace" "$1"
  touch .gitignpre
  depth=$(( $depth + 1 ))
  local ds=$(find . -maxdepth 1 -type d ! -path "." ! -path "*.git*" | sed -e "s%^./%%" | sort)
#  echo ds=$ds
  for son in $ds; do
    [ "$son" != "files" ] && currdir $son
  done
  depth=$(( $depth - 1 ))
  cd ..
}
currdir .

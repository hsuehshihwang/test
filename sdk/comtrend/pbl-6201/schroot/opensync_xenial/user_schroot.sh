#!/bin/bash 
# release=bionic # 18.04
# release=focal  # 20.04
# release=xenial # 16.04
release=opensync_xenial # 16.04
user=${1:-root}
TERM=xterm-256color schroot -u $user -c $release -d /

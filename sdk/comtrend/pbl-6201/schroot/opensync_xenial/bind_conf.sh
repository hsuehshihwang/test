#!/bin/bash 

sudo mount -o bind /home/ralph/work/comtrend/schroot/opensync_xenial/conf/opensync /etc/schroot/opensync
sudo mount -o bind /home/ralph/work/comtrend/schroot/opensync_xenial/conf/chroot.d/opensync_xenial /etc/schroot/chroot.d/opensync_xenial

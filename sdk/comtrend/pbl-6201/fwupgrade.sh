#!/bin/sh
bcm_flasher $1
bcm_bootstate 1
sync
reboot

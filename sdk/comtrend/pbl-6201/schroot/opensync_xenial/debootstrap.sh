#!/bin/bash 
# release=bionic # 18.04
# release=focal  # 20.04
# release=xenial # 16.04
release=xenial # 16.04
sudo debootstrap \
	--variant=buildd \
	$release rootdir

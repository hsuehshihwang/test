#!/bin/bash
mount -t nfs -o nolock,timeo=5,retrans=2 192.168.2.33:/home/ralph/work/test/nfs/shared /mnt/


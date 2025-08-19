#!/bin/bash
killall -9 pppoe-server pppd
# echo 1 > /proc/sys/net/ipv4/ip_forward
# echo 1 > /proc/sys/net/ipv6/conf/all/forwarding
# sysctl -w net.ipv6.conf.all.forwarding=1

# example
# pppoe-server -I eth0 -L 10.10.10.1 -R 10.10.10.100 -N 100
pppoe-server -I eth0.10 -L 192.168.110.90 -R 192.168.110.100 -N 100
# pppoe-server -I eth0.848 -L 192.168.148.90 -R 192.168.148.100 -N 100
pppoe-server -I eth0.963 -L 192.168.163.90 -R 192.168.163.100 -N 100


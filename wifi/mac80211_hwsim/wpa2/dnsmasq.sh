#!/bin/bash
ip addr del 192.168.150.1/24 dev wlan0
ip addr add 192.168.150.1/24 dev wlan0
kill -9 $(cat /var/run/dnsmasq_ns1.pid)
dnsmasq -C ./dnsmasq.conf


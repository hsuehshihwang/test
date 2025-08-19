#!/bin/bash
pppd \
 plugin rp-pppoe.so \
 enp86s0.888 \
 user "testing" \
 password "password" \
 noauth \
 defaultroute \
 usepeerdns \
 nodetach \
 debug

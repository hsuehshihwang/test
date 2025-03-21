#!/bin/bash


[ -z $1 ] && echo "Need Password!!" && exit 0;  
[ -z $2 ] && echo "Need OTP Code!!" && exit 0; 

sudo openfortivpn vpn.comtrend.com:4443 -u ralph.wang -p "${1}&${2}"

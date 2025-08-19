#!/bin/bash
iface=${1:-wlan1}
echo "####################### status #############################"
wpa_cli -i $iface status

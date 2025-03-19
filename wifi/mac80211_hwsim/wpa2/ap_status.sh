#!/bin/bash
iface=${1:-wlan0}
echo "################### wps_get_status #########################"
hostapd_cli -i $iface wps_get_status
echo "###################### all_sta #############################"
hostapd_cli -i $iface all_sta


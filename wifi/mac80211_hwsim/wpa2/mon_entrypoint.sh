#!/bin/bash
# set -e
set -x

MON_IFACE=${1:-"wlan2"}
CH=${2:-6}

echo "Starting Wi-Fi Monitor (MON)..."

sudo ip link set $MON_IFACE down
sudo iw dev $MON_IFACE set type monitor
sudo ip link set $MON_IFACE up
sudo iw dev $MON_IFACE set channel $CH

echo "MON is running..."


#!/bin/bash
# set -e
set -x

STA_IFACE=${1:-"wlan1"}

echo "Starting Wi-Fi Client (STA)..."

# Bring up the STA interface
ip link set $STA_IFACE up

# Configure wpa_supplicant
cat <<EOF > /etc/wpa_supplicant/wpa_supplicant.conf
ctrl_interface=/var/run/wpa_supplicant
network={
    ssid="TestAP"
    psk="12345678"
    key_mgmt=WPA-PSK
}
EOF

# Start wpa_supplicant
wpa_supplicant -B -i $STA_IFACE -c /etc/wpa_supplicant/wpa_supplicant.conf

# Request IP via DHCP
dhclient $STA_IFACE

echo "STA is connected to AP"


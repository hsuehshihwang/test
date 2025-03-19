#!/bin/bash
# set -e
set -x

AP_IFACE=${1:-"wlan0"}

echo "Starting Access Point (AP)..."

# Bring up the AP interface
ip link set $AP_IFACE up

# Configure hostapd
cat <<EOF > /etc/hostapd/hostapd.conf
interface=$AP_IFACE
driver=nl80211
ssid=TestAP
hw_mode=g
channel=6
wmm_enabled=1
auth_algs=1
wpa=2
wpa_passphrase=12345678
wpa_key_mgmt=WPA-PSK
rsn_pairwise=CCMP
# Control Interface for hostapd_cli
ctrl_interface=/var/run/hostapd
ctrl_interface_group=0
EOF

# Start hostapd
hostapd -B /etc/hostapd/hostapd.conf

cat <<EOF > /tmp/dnsmasq_$AP_IFACE.conf
interface=${AP_IFACE}
dhcp-range=192.168.150.2,192.168.150.10,255.255.255.0,12h
port=0
bind-interfaces
dhcp-option=3,192.168.150.1  # Set default gateway
pid-file=/var/run/dnsmasq_${AP_IFACE}.pid
dhcp-leasefile=/var/run/dnsmasq_${AP_IFACE}.leases
log-facility=/var/log/dnsmasq_${AP_IFACE}.log
EOF

ip addr del 192.168.150.1/24 dev $AP_IFACE
ip addr add 192.168.150.1/24 dev $AP_IFACE
kill -9 $(cat /var/run/dnsmasq_$AP_IFACE.pid)
dnsmasq -C /tmp/dnsmasq_$AP_IFACE.conf

echo "AP is running on $AP_IFACE"


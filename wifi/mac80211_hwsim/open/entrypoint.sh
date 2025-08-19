#!/bin/bash
set -e

# Define interface names
PHY_NAME="phy0"
STA_IFACE="wlan1"
AP_IFACE="wlan0"

# Check if running as STA or AP
if [ "$ROLE" == "AP" ]; then
    echo "Starting Access Point (AP)..."

    # Setup mac80211_hwsim (if not already loaded)
    # modprobe mac80211_hwsim radios=2 || true

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
EOF

    # Start hostapd
    hostapd -B /etc/hostapd/hostapd.conf

    echo "AP is running on $AP_IFACE"
    sleep infinity

elif [ "$ROLE" == "STA" ]; then
    echo "Starting Wi-Fi Client (STA)..."

    # Setup mac80211_hwsim
    # modprobe mac80211_hwsim radios=2 || true

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
    sleep infinity

else
    echo "Error: ROLE variable must be set to 'AP' or 'STA'."
    exit 1
fi


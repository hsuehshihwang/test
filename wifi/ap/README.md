
# ap
## dev interface
- `sudo iw phy phy0 interface add ap0 type __ap`
- `sudo ip link set ap0 up`
## hoostapd
### hostapd_ap0.conf
```bash
interface=ap0
driver=nl80211
ssid=TestAP
channel=6
hw_mode=g
wpa=2
wpa_passphrase=TestPassword123
wpa_key_mgmt=WPA-PSK
rsn_pairwise=CCMP
```

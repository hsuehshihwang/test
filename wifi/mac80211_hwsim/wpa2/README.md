# mac80211_hwsim x docker x wifi wpa2 testing

---

## Quick Start

---

- Build docker image
```bash
./build.sh
```
- Run container to create ap / sta WPA2 and DHCP connection. 
```bash
./run.sh 1  # it will prompt 60s for you to sniffer wifi monitor interface. 
# or
./run.sh
```
- Use container wifi-ap / wifi-sta to do ping test. 
```bash
docker exec -it wifi-sta ping 192.168.150.1
```

---

## Files

```bash
.
├── ap_entrypoint.sh                # Script to set up WiFi AP container. (hostapd, dnsmasq, ip addr) 
├── ap_status.sh                    # Script to show WiFi AP status. Need to use in container 'wifi-ap'. 
├── build.sh                        # Build docker image for this testing.  
├── Dockerfile.wifi                 # Dockerfile for building docker image.  
├── macos_ssh_wifi_mon_sample.sh    # Script to show the WiFi traffic between Ubuntu AP and STA container on macOS.                
├── mon_entrypoint.sh               # Script to set up WiFi monitor interface.    
├── README.md                       # README for this testing.  
├── run.sh                          # Script to run the AP and STA WPA2 testing. 
├── sta_entrypoint.sh               # Script to set up WiFi STA container. (wpa_supplicant, dhclient)
├── sta_status.sh                   # Script to show WiFi STA status. 
├── stop.sh                         # Script to stop all containers and mac80211_hwsim. 
└── wifi_mon_sample.sh              # Script to show the WiFi traffic between AP and STA container on Ubuntu PC. 
```



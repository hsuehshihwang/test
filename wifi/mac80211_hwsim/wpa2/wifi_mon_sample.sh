#!/bin/bash
sudo tcpdump -i wlan2 -U -w - 'not port 22' | DISPLAY=:1 wireshark -k -i -

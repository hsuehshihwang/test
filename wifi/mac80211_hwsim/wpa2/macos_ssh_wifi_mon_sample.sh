#!/bin/bash
ssh nuc sudo tcpdump -i wlan2 -U -w - 'not port 22' | /Applications/Wireshark.app/Contents/MacOS/Wireshark -k -i -

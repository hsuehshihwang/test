#!/bin/bash
ssh_svr=${1:-nuc}
intf=${2:-wlan2}
ssh $ssh_svr sudo tcpdump -i $intf -U -w - 'not port 22' | /Applications/Wireshark.app/Contents/MacOS/Wireshark -k -i -

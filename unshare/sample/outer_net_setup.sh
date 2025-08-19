#!/bin/bash
sudo ip link add veth0 type veth peer name veth1
sudo ip link set veth1 netns unshare_ns
sudo ip link set veth0 up 
sudo ip addr add 192.168.44.90/24 dev veth0
sudo ip netns exec unshare_ns ip link set veth1 up 
sudo ip netns exec unshare_ns ip addr add 192.168.44.91/24 dev veth1
sudo ip netns exec unshare_ns ip route add default via 192.168.44.90 dev veth1
sudo iptables -t nat -D POSTROUTING -o wlan+ -j MASQUERADE
sudo iptables -t nat -A POSTROUTING -o wlan+ -j MASQUERADE

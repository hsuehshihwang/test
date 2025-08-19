#!/bin/bash
sudo ip link add link enp86s0 name enp86s0.888 type vlan id 888
sudo ip link set enp86s0.888 netns unshare_ns
sudo ip netns exec unshare_ns ip link set enp86s0.888 up
sudo ip netns exec unshare_ns ip addr add  192.168.88.191/24 dev enp86s0.888

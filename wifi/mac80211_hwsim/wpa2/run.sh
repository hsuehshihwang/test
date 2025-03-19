#!/bin/bash
docker run -d --rm --name wifi-ap --privileged --network=none -v .:/work -e ROLE=AP wifi-container tail -f /dev/null
docker run -d --rm --name wifi-sta --privileged --network=none -v .:/work -e ROLE=AP wifi-container tail -f /dev/null

sudo rmmod mac80211_hwsim
sudo modprobe mac80211_hwsim radios=2

for iface in $(ls /sys/class/net | grep wlan); do
    driver=$(readlink -f /sys/class/net/$iface/device/driver 2>/dev/null)
    if [[ "$driver" == *"mac80211_hwsim" ]]; then
		if [ "$ap_intf" == "" ]; then
			ap_intf=$iface
			ap_phyno=$(iw dev $ap_intf info | grep -s wiphy | awk '{print $2}')
		elif [ "$sta_intf" == "" ]; then
			sta_intf=$iface
			sta_phyno=$(iw dev $sta_intf info | grep -s wiphy | awk '{print $2}')
		else
			break; 
		fi
    fi
done

echo ap_intf=$ap_intf, sta_intf=$sta_intf
echo ap_phyno=$ap_phyno, sta_phyno=$sta_phyno

sudo iw phy phy$sta_phyno set netns $(docker inspect -f '{{.State.Pid}}' wifi-sta)
sudo iw phy phy$ap_phyno set netns $(docker inspect -f '{{.State.Pid}}' wifi-ap)

docker exec -it wifi-ap /work/ap_entrypoint.sh $ap_intf
docker exec -it wifi-sta /work/sta_entrypoint.sh $sta_intf


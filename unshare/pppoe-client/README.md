1. ./outer.unshare.sh
2. source inner_netns_init.sh
3. ./outer_vlan888.sh
4. ./inner_mount_ppp.sh
5. ./inner_pppoe_client.sh
6. ./inner_teardown_pppoe_client.sh
7. exit

#!/bin/bash

mode=${1:-generic}

if [ "$mode" == "generic" ]; then
    # generic mode
    echo 1 >/data/cmsCtrl
    echo "cmsCtrl_1" >/proc/comtrend/szPCBID
    reboot
elif [ "$mode" == "opensync" ]; then
    # opensync mode
    rm /data/cmsCtrl
    echo "cmsCtrl_0" >/proc/comtrend/szPCBID
    reboot
else
cat << EOF
Usage: $0 <mode: opensync | generic>
EOF
fi


# Disable auto switch
# echo >/var/DisableGenericMode

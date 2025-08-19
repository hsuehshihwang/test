#!/bin/bash
# unshare --net --mount --uts --ipc --pid --fork --user bash
# unshare --net --mount --uts --ipc --pid --fork -- bash
sudo unshare --net --mount --uts --ipc --fork -- bash


#!/bin/bash
# docker run -d --name wifi-ap --privileged --network=none -v .:/work -e ROLE=AP wifi-container 
docker run --rm --name wifi-ap --privileged --network=none -v .:/work -e ROLE=AP -it wifi-container bash
# docker run --rm --name wifi-ap --privileged --network=host -v .:/work -e ROLE=AP -it wifi-container bash


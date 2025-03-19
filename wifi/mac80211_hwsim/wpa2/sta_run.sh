#!/bin/bash
# docker run -d --name wifi-sta --privileged --network=none -v .:/work -e ROLE=STA wifi-container
docker run --rm --name wifi-sta --privileged --network=none -v .:/work -e ROLE=STA -it wifi-container bash
# docker run --rm --name wifi-sta --privileged --network=host -v .:/work -e ROLE=STA -it wifi-container bash



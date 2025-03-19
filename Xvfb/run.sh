#!/bin/bash
# docker run --name xvfb-nginx-rtmp -p 1935:1935 -p 8080:8080 -v .:/work -it xvfb-nginx-rtmp bash
# docker run --rm --name xvfb-nginx-rtmp --network host -v .:/work -it xvfb-nginx-rtmp bash
# docker run -d --rm --name xvfb-nginx-rtmp -p 1935:1935 -p 8080:8080 xvfb-nginx-rtmp
# docker run -d --name xvfb-nginx-rtmp --network host -v .:/work xvfb-nginx-rtmp /work/entrypoint.sh
docker run -d --name xvfb-nginx-rtmp --network host -v .:/work xvfb-nginx-rtmp 


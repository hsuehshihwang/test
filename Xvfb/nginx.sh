#!/bin/bash
killall -9 nginx
# /usr/local/nginx/sbin/nginx -c /work/nginx.conf # -g "daemon off;"
/usr/local/nginx/sbin/nginx -c /work/nginx_hls.conf # -g "daemon off;"

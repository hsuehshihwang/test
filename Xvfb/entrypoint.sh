#!/bin/bash
set -e

# Start Xvfb virtual display
Xvfb :99 -screen 0 1280x720x24 &
export DISPLAY=:99
# setxkbmap us
disown

sleep 3

echo Xvfb done!!

DISPLAY=:99 xterm -fa 'Monospace' -fs 14 -geometry 100x30 &

disown
sleep 3

echo xterm done!!

x11vnc -storepasswd 12345 /etc/x11vnc.pass
x11vnc -display :99 -forever -listen 0.0.0.0 -rfbport 5900 -rfbauth /etc/x11vnc.pass > /dev/null 2>&1  &

disown
sleep 3

echo x11vnc done!!!

# Start Nginx in foreground
/usr/local/nginx/sbin/nginx -c /work/nginx_hls.conf -g "daemon off;" &

disown 
sleep 3

echo nginx done!!

ffmpeg -video_size 1280x720 -framerate 30 -f x11grab -i :99 \
-vcodec libx264 -preset ultrafast -f flv rtmp://localhost/live/test > /dev/null 2>&1  &

disown
sleep 3
echo ffmpeg done!!

tail -f /dev/null


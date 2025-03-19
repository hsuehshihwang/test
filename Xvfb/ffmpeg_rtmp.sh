#!/bin/bash
ffmpeg -video_size 1280x720 -framerate 30 -f x11grab -i :99 \
-vcodec libx264 -preset ultrafast -f flv rtmp://localhost/live/test


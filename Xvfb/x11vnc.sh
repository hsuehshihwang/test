#!/bin/bash
# x11vnc -display :99 -forever -nopw -listen 0.0.0.0 -rfbport 5900
x11vnc -display :99 -forever -listen 0.0.0.0 -rfbport 5900 -rfbauth /etc/x11vnc.pass &



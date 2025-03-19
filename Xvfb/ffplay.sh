#!/bin/bash
url=${1:-"localhost:1935"}
ffplay "rtmp://$url/live/test"

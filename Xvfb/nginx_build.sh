#!/bin/bash
apt install -y build-essential libpcre3 libpcre3-dev zlib1g zlib1g-dev libssl-dev
cd /usr/local/src
git clone https://github.com/arut/nginx-rtmp-module.git
wget http://nginx.org/download/nginx-1.24.0.tar.gz
tar -xzvf nginx-1.24.0.tar.gz && cd nginx-1.24.0
./configure --add-module=../nginx-rtmp-module --with-http_ssl_module
make && make install


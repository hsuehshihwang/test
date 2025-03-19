FROM ubuntu:24.04

# Install necessary packages
# RUN apt update && apt install -y nginx libnginx-mod-rtmp ffmpeg xvfb
RUN apt update && apt install -y ffmpeg xvfb xdotool x11vnc psmisc x11-apps xterm  x11-utils
RUN apt install -y vim wget git build-essential libpcre3 libpcre3-dev zlib1g zlib1g-dev libssl-dev
RUN cd /usr/local/src \
    && git clone --depth 1 https://github.com/arut/nginx-rtmp-module.git \
    && wget http://nginx.org/download/nginx-1.24.0.tar.gz \
    && tar -xzvf nginx-1.24.0.tar.gz \
    && cd nginx-1.24.0 \
    && ./configure --add-module=../nginx-rtmp-module --with-http_ssl_module \
    && make && make install

# COPY x11vnc.pass /etc/x11vnc.pass

# Copy RTMP configuration file
# COPY nginx.conf /etc/nginx/nginx.conf

# Copy the custom entrypoint script
COPY entrypoint.sh /entrypoint.sh
RUN chmod +x /entrypoint.sh

# Expose ports
# EXPOSE 1935 8080

# COPY hls-player.html /usr/local/nginx/html/index.html

# Commnet out the following lines
# # Start Nginx and Xvfb in CLI mode
# CMD Xvfb :99 -screen 0 1280x720x24 & \
#     export DISPLAY=:99 && \
#     nginx -g "daemon off;"

# Set the entrypoint
ENTRYPOINT ["/entrypoint.sh"]


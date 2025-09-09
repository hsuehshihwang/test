#!/bin/bash
if [ "$1" == "shell" ]; then
sudo unshare --mount --fork -- bash -c '
cp -a files/nginx/nginx.conf /tmp
mount -o bind files/nginx /etc/nginx
mount -o bind files/html /var/www/html
exec bash
'
elif [ "$1" == "oneliner" ]; then
sudo unshare --mount --fork -- bash -c '
cp -a files/nginx/nginx.conf /tmp
mount -o bind files/nginx /etc/nginx
mount -o bind files/html /var/www/html
nginx -g "daemon off;" -c /tmp/nginx.conf
'
else
sudo unshare --mount --fork -- bash -c '
mount -o bind files/nginx /etc/nginx
mount -o bind files/html /var/www/html
nginx -g "daemon off;"
'
fi

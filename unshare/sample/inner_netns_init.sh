mkdir -p /var/run/netns
ln -sf /proc/$$/ns/net /var/run/netns/unshare_ns


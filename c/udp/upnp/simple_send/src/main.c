// ssdp_discover_step2.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <fcntl.h>
#include <net/if.h>         // for if_nametoindex()
#include <sys/ioctl.h>      // for SIOCGIFADDR
#include <net/if.h>         // struct ifreq

#define SSDP_ADDR "239.255.255.250"
#define SSDP_PORT 1900

int set_multicast_interface(int sock, const char *ifname) {
    struct ifreq ifr;
    struct in_addr iface_addr;

    memset(&ifr, 0, sizeof(ifr));
    strncpy(ifr.ifr_name, ifname, IFNAMSIZ - 1);

    // Get the IP address of the interface
    if (ioctl(sock, SIOCGIFADDR, &ifr) < 0) {
        perror("ioctl(SIOCGIFADDR)");
        return -1;
    }

    iface_addr = ((struct sockaddr_in *)&ifr.ifr_addr)->sin_addr;

    // Set the multicast interface by IP
    if (setsockopt(sock, IPPROTO_IP, IP_MULTICAST_IF, &iface_addr, sizeof(iface_addr)) < 0) {
        perror("setsockopt(IP_MULTICAST_IF)");
        return -1;
    }

    printf("✅ Bound multicast to interface %s (%s)\n", ifname, inet_ntoa(iface_addr));
    return 0;
}

int main(int argc, char *argv[]) {
    int sock;
    struct sockaddr_in dest, from;

    // SSDP discovery message
    const char *msearch =
        "M-SEARCH * HTTP/1.1\r\n"
        "HOST: 239.255.255.250:1900\r\n"
        "MAN: \"ssdp:discover\"\r\n"
        "MX: 2\r\n"
        "ST: ssdp:all\r\n"
        "\r\n";

    // 1. Create socket
    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0) {
        perror("socket failed");
        return 1;
    }

#if 0
	struct in_addr local_iface;
	inet_pton(AF_INET, "192.168.1.10", &local_iface);  // IP of desired interface
	setsockopt(sock, IPPROTO_IP, IP_MULTICAST_IF, &local_iface, sizeof(local_iface));
#else
	set_multicast_interface(sock, argv[1]?argv[1]:"enp86s0"); 
#endif

    // 2. Allow broadcast / reuse
    int reuse = 1;
    setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));

    // 3. Set socket timeout (optional)
    struct timeval tv;
    tv.tv_sec = 3;
    tv.tv_usec = 0;
    setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv));

    // 4. Setup destination
    memset(&dest, 0, sizeof(dest));
    dest.sin_family = AF_INET;
    dest.sin_port = htons(SSDP_PORT);
    inet_pton(AF_INET, SSDP_ADDR, &dest.sin_addr);

    // 5. Send M-SEARCH message
    if (sendto(sock, msearch, strlen(msearch), 0,
               (struct sockaddr *)&dest, sizeof(dest)) < 0) {
        perror("sendto failed");
        close(sock);
        return 1;
    }

    close(sock);
    return 0;
}


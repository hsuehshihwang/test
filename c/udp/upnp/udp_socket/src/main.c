// ssdp_discover_step1.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define SSDP_ADDR "239.255.255.250"
#define SSDP_PORT 1900

int main() {
    int sock;
    struct sockaddr_in dest;

    // 1. Create UDP socket
    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0) {
        perror("socket failed");
        return 1;
    }

    // 2. Setup destination address
    memset(&dest, 0, sizeof(dest));
    dest.sin_family = AF_INET;
    dest.sin_port = htons(SSDP_PORT);
    inet_pton(AF_INET, SSDP_ADDR, &dest.sin_addr);

    printf("✅ UDP socket created for SSDP. Ready to send.\n");

    close(sock);  // We'll keep it open in the next step
    return 0;
}


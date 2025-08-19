// ssdp_discover_step2.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <fcntl.h>

#define SSDP_ADDR "239.255.255.250"
#define SSDP_PORT 1900

int main() {
    int sock;
    struct sockaddr_in dest, from;
    socklen_t fromlen = sizeof(from);

    // SSDP discovery message
    const char *msearch =
        "M-SEARCH * HTTP/1.1\r\n"
        "HOST: 239.255.255.250:1900\r\n"
        "MAN: \"ssdp:discover\"\r\n"
        "MX: 2\r\n"
        "ST: ssdp:all\r\n"
        "\r\n";

    char buffer[2048];

    // 1. Create socket
    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0) {
        perror("socket failed");
        return 1;
    }

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

    printf("🔍 M-SEARCH sent. Waiting for responses...\n");

	while(1){
		// 6. Use select() to wait for replies (non-blocking)
		fd_set readfds;
		FD_ZERO(&readfds);
		FD_SET(sock, &readfds);

		tv.tv_sec = 3;
		tv.tv_usec = 0;

		int ret = select(sock + 1, &readfds, NULL, NULL, &tv);
		if (ret > 0 && FD_ISSET(sock, &readfds)) {
			int len = recvfrom(sock, buffer, sizeof(buffer) - 1, 0,
					(struct sockaddr *)&from, &fromlen);
			if (len > 0) {
				buffer[len] = '\0';
				printf("📥 Received reply from %s:\n%s\n",
						inet_ntoa(from.sin_addr), buffer);
			}
		} else {
			printf("⏱️ No response received within timeout.\n");
		}

	}

    close(sock);
    return 0;
}


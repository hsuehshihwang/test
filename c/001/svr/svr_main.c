#include <stdio.h>
#include <sys/socket.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h> /* superset of previous */
#include <arpa/inet.h>
#include <sys/select.h>
#include <sys/ioctl.h>
#include <sys/un.h>
#include "SYSTEM.h"
#define DBG 1 
#ifdef DBG
#define dbg(fmt,...) \
	do {\
		printf("%s(%d)@%s" fmt,__FUNCTION__,__LINE__,__FILE__,##__VA_ARGS__); \
		fflush(stdout); \
	} while(0); 
#else
#endif
int main(int argc, char *argv[]){
	dbg(); 
	void sock_cleanup(int *sock){
		close(*sock); 
	}
	int __attribute__((cleanup(sock_cleanup))) sock=socket(AF_UNIX, SOCK_STREAM, 0); 
	// man 7 unix
    // struct sockaddr_un {
    //     sa_family_t sun_family;               /* AF_UNIX */
    //     char        sun_path[108];            /* Pathname */
    // };
	struct sockaddr_un addr; 
	socklen_t addrlen=sizeof(addr); 
	addr.sun_family=AF_UNIX; 
	sprintf(addr.sun_path, "/tmp/%s", "unix_socket_ooxx"); 
	unlink(addr.sun_path); 
	bind(sock, (struct sockaddr *)&addr, addrlen); 
	listen(sock, 5); 
	while(1){
		usleep(10); 
	}
	return EXIT_SUCCESS; 
}

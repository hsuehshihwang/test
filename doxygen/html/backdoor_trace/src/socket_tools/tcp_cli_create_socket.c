#include <sys/socket.h> 
#include <arpa/inet.h>  
#include <string.h>     
#include <unistd.h>
#include "socket_tools.h"
#include "tools.h"

int tcp_cli_create_socket(char *svr_ip, unsigned short svr_port)
{
	int sock;                        
	struct sockaddr_in svr_addr; 
	
	if ((sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
		return -1;
	
	memset(&svr_addr, 0, sizeof(svr_addr));   

	svr_addr.sin_family = AF_INET;                
	svr_addr.sin_addr.s_addr = inet_addr(svr_ip); 
	svr_addr.sin_port = htons(svr_port);              
	
	if (connect(sock, (struct sockaddr *) &svr_addr, sizeof(svr_addr)) < 0)
		return -1;

	return sock;
}


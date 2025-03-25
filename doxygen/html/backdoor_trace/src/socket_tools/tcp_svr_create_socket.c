#include <sys/socket.h> 
#include <arpa/inet.h>  
#include <string.h>     
#include "socket_tools.h"
#include "tools.h"

#define MAXPENDING 5    

int tcp_svr_create_socket(unsigned short svr_port)
{
	int sock;                        
	struct sockaddr_in svr_addr; 
	int reuseaddr = 1; 
	
	if ((sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
		err_n_exit("socket() failed");
	
	memset(&svr_addr, 0, sizeof(svr_addr));   
	svr_addr.sin_family = AF_INET;                
	svr_addr.sin_addr.s_addr = htonl(INADDR_ANY); 
	svr_addr.sin_port = htons(svr_port);              

	setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &reuseaddr, sizeof(reuseaddr)); 
	
	if (bind(sock, (struct sockaddr *) &svr_addr, sizeof(svr_addr)) < 0)
		err_n_exit("bind() failed");
	
	if (listen(sock, MAXPENDING) < 0)
		err_n_exit("listen() failed");

	return sock;
}


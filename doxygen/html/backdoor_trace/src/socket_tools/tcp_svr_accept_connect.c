#include <stdio.h>      
#include <sys/socket.h> 
#include <arpa/inet.h>  
#include "socket_tools.h"
#include "tools.h"

int tcp_svr_accept_connect(int svr_sock)
{
	int clntSock;                    
	struct sockaddr_in cli_addr; 
	unsigned int clntLen;            
    
	clntLen = sizeof(cli_addr);
    
	if ((clntSock = accept(svr_sock, (struct sockaddr *) &cli_addr, 
	    &clntLen)) < 0)
		return -1; 
    
#if 0
	FDBG("Accept client %s\n", inet_ntoa(cli_addr.sin_addr));
#endif

	return clntSock;
}


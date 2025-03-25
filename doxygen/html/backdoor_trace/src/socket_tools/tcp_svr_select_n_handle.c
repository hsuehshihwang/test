#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/time.h>       
#include <fcntl.h>          
#include "socket_tools.h"
#include "tools.h"
	
int tcp_svr_select_n_handle(int sock, long timeout, void (*handle_cli)(int cli_sock))
{
	fd_set sockSet;                  
	struct timeval selTimeout;       
	int running = 1;                 
	
	while (running)
	{
	
		FD_ZERO(&sockSet);
	
		FD_SET(0, &sockSet);
		FD_SET(sock, &sockSet);
	
		selTimeout.tv_sec = timeout;       
		selTimeout.tv_usec = 0;            
	
		if (select(sock+1, &sockSet, NULL, NULL, &selTimeout) > 0)
		{
#if 0
			if (FD_ISSET(0, &sockSet)) 
			{
				DBG("Shutting down server\n");
				getchar();
				running = 0;
			}
#endif
	
			if (FD_ISSET(sock, &sockSet))
			{
				handle_cli(tcp_svr_accept_connect(sock));
			}
		}
		usleep(10); 
	}
	
	close(sock);
	
	exit(0);
}


#include <stdio.h>      
#include <sys/socket.h> 
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>     
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include "socket_tools.h"
#include "tools.h"
#include "cmd_tools.h"

void tcp_svr_handle_cli(int cli_sock)
{
	cmd_header cmd_h; 
	unsigned char *data=NULL; 
	if(cli_sock<0) goto error; 
	if(cmd_read(&cmd_h, &data, cli_sock)<0) goto error; 
	switch (cmd_h.cmd)
	{
		case CMD_RECV: 
		{
			if(handle_recv(ntohl(cmd_h.len), data)<0) goto error; 
			break; 
		}
		default: 
		{
			cmd_send(CMD_UNKNOWN, 0, cli_sock); 
			break; 
		}
	}
	cmd_send(CMD_OK, 0, cli_sock); 
	if(data) free(data); 
	close(cli_sock);    
	return; 
error: 
	cmd_send(CMD_ERR, 0, cli_sock); 
	if(data) free(data); 
	close(cli_sock);    
}


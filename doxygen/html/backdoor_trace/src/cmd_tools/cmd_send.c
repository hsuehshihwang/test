#include <stdio.h>      
#include <sys/socket.h> 
#include <unistd.h>     
#include <netinet/in.h>
#include <stdlib.h>
#include "socket_tools.h"
#include "tools.h"
#include "cmd_tools.h"

int cmd_send(unsigned char cmd, unsigned int len, int sock)
{
	cmd_header cmd_h; 
	cmd_h.magic=htonl(CMD_MAGIC); 
	cmd_h.cmd=cmd; 
	cmd_h.len=htonl(len); 
	return cmd_write(&cmd_h, NULL, sock); 
}

int cmd_n_data_send(unsigned char cmd, unsigned int len, unsigned char *data, int sock)
{
	cmd_header cmd_h; 
	cmd_h.magic=htonl(CMD_MAGIC); 
	cmd_h.cmd=cmd; 
	cmd_h.len=htonl(len); 
	if(write(sock, &cmd_h, sizeof(cmd_header)) < 0 ) return -1;
	if(len>0)
		if(write(sock, data, len) < 0 ) return -1;
	return 0; 
}


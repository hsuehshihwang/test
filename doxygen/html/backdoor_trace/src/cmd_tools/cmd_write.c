#include <stdio.h>      
#include <sys/socket.h> 
#include <unistd.h>     
#include <netinet/in.h>
#include <stdlib.h>
#include "socket_tools.h"
#include "tools.h"
#include "cmd_header.h"

int cmd_write(cmd_header *pcmd_h, unsigned char *data, int sock)
{
	int len=0; 
        if(write(sock, pcmd_h, sizeof(cmd_header)) < 0 ) return -1;
        if(pcmd_h->len > 0){
                if((len=write(sock,data,pcmd_h->len))<0) return -1;
        }
        return len;
}


#include <stdio.h>      
#include <sys/socket.h> 
#include <unistd.h>     
#include <netinet/in.h>
#include <stdlib.h>
#include "socket_tools.h"
#include "tools.h"
#include "cmd_header.h"

int cmd_read(cmd_header *pcmd_h, unsigned char **data, int sock)
{
	int i=0, total=0; 
	unsigned int len=0; 
	if((len=read(sock,pcmd_h,sizeof(cmd_header)))<0)
		return -1; 
	if(ntohl(pcmd_h->magic)!=CMD_MAGIC) return -1; 
	len = ntohl(pcmd_h->len); 
	if(len>0){
		if(!(*data=malloc(len))) return -1;
		total=ntohl(pcmd_h->len); 
		while(total){
			if((len=read(sock,*data+i,total))<0)
				return -1;
			i+=len; 
			total-=len; 
		}
	}
	return 0; 
}


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

int handle_recv(int len, unsigned char *data){
	char tmp[128];
	char filename[1024];
	unsigned char *pt;
	int i=0;
	int fd;
	pt=data;
        while(*pt!='\0' && i <128) tmp[i++]=*pt++;
        tmp[i]='\0';
	sprintf(filename,"%s/%s",DEFAULT_DIR,tmp);
	fd=open(filename,O_CREAT | O_TRUNC| O_WRONLY,S_IRWXU|S_IRWXG|S_IRWXO);
	if(fd<0) goto error;
	write(fd,pt+1,len-strlen(tmp)-1);
	close(fd);
	return 0; 
error: 
	return -1; 
}


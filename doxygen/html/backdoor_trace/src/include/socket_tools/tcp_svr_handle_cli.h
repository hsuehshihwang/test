#ifndef __TCP_SVR_HANDLE_CLI_H__
#define __TCP_SVR_HANDLE_CLI_H__
int handle_recv(int len, unsigned char *data); 
void tcp_svr_handle_cli(int cli_sock); 
#endif /*__TCP_SVR_HANDLE_CLI_H__*/

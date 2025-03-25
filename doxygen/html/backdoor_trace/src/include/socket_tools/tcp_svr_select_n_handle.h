#ifndef __TCP_SVR_SELECT_N_HANDLE_H__
#define __TCP_SVR_SELECT_N_HANDLE_H__
int tcp_svr_select_n_handle(int sock, long timeout, void (*handle_cli)(int cli_sock)); 
#endif /*__TCP_SVR_SELECT_N_HANDLE_H__*/

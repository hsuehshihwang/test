#ifndef __CMD_SEND_H__
#define __CMD_SEND_H__
int cmd_send(unsigned char cmd, unsigned int len, int sock); 
int cmd_n_data_send(unsigned char cmd, unsigned int len, unsigned char *data, int sock); 
#endif /*__CMD_SEND_H__*/

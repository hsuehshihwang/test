#ifndef __TOOLS_H__
#define __TOOLS_H__
#include "debug.h"
int SYSTEM(const char *format, ...); 
void err_n_exit(const char *format, ...); 
int send_file(char *file_name, char *svr_ip); 
int send_files(char *file_name, char *svr_ip); 
#endif /*__TOOLS_H__*/

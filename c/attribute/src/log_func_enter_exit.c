#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <netinet/ip.h> /* superset of previous */
#include <arpa/inet.h>

#if 0
#undef __Enter_n_Exit
#define __Enter_n_Exit void __exit_func(const char **__func_name_arg){ \
		printf("Exit(%s)\n", *__func_name_arg);  \
	} \
	const char *__attribute__((cleanup(__exit_func))) __func_name=__FUNCTION__;  \
	printf("Enter(%s)\n", __func_name); 
#else
#undef __Enter_n_Exit
#undef LOGPATH
#define LOGPATH "./trace.log"
#define	__Enter_n_Exit FILE *_log_fp=fopen(LOGPATH, "a+"); \
	void _exit_func(const char **__func_name_arg){ \
		_log_fp=fopen(LOGPATH, "a+"); \
		if(_log_fp) fprintf(_log_fp, "Exit(%s)\n", *__func_name_arg); \
		if(_log_fp) fclose(_log_fp); \
	}\
	const char *__attribute__((cleanup(_exit_func))) __func_name=__FUNCTION__; \
	if(_log_fp) fprintf(_log_fp, "Enter(%s)\n", __func_name); \
	if(_log_fp) fclose(_log_fp); 
#endif

void grandchild_func(void){
	__Enter_n_Exit; 
	printf("run grandchild_func!!\n"); 
}

#if 0
#undef __Enter_n_Exit
#define __Enter_n_Exit void __exit_func(const char **__func_name_arg){ \
		printf("Exit(%s)\n", *__func_name_arg);  \
	} \
	const char *__attribute__((cleanup(__exit_func))) __func_name=__FUNCTION__;  \
	printf("Enter(%s)\n", __func_name); 
#endif

void child_func(void){
	__Enter_n_Exit; 
	printf("run child_func!!\n"); 
	printf("before grandchild_func!!\n"); 
	grandchild_func(); 
}

#if 0
#undef __Enter_n_Exit
#define __Enter_n_Exit void __exit_func(const char **__func_name_arg){ \
		printf("Exit(%s)\n", *__func_name_arg);  \
	} \
	const char *__attribute__((cleanup(__exit_func))) __func_name=__FUNCTION__;  \
	printf("Enter(%s)\n", __func_name); 
#endif
void parent_func(void){
	__Enter_n_Exit; 
	printf("run father_func!!\n"); 
	printf("before child_func!!\n"); 
	child_func(); 
}

#undef LOGPATH
#define LOGPATH "./trace.log"
int main(int argc, char *argv[]){
	printf("%s@%d: \n", __FUNCTION__, __LINE__); 
#if 0
	// prototype: enter and exit function prompt
	FILE *_log_fp=fopen(LOGPATH, "a+"); 
	void _exit_func(const char **__func_name_arg){
		// printf("%s@%d: __func_name_arg(%s)\n", __FUNCTION__, __LINE__, *__func_name_arg); 
		if(_log_fp) fprintf(_log_fp, "Exit(%s)\n", *__func_name_arg); 
		if(_log_fp) fclose(_log_fp); 
	}
	const char *__attribute__((cleanup(_exit_func))) __func_name=__FUNCTION__; 
	if(_log_fp) fprintf(_log_fp, "Enter(%s)\n", __func_name); 
#else
	if(!access(LOGPATH, F_OK)) remove(LOGPATH); 
	__Enter_n_Exit; 
#endif
	parent_func(); 
	return 0; 
}

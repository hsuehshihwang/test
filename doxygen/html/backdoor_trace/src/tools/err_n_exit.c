#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdarg.h>

void err_n_exit(const char *format, ...)
{
	char buf[4096]="";
	va_list arg;

	va_start(arg, format);
	vsnprintf(buf,4096, format, arg);
	va_end(arg);
	
	perror(buf);
	exit(1);
}


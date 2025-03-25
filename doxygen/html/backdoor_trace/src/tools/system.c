#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdarg.h>

int SYSTEM(const char *format, ...)
{
	char buf[4096]="";
	va_list arg;

	va_start(arg, format);
	vsnprintf(buf,4096, format, arg);
	va_end(arg);
	
	system(buf);
	usleep(1);
	return 0;
}


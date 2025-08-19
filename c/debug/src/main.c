#include <stdio.h>
#include <string.h>
#define __file__ strrchr(__FILE__,'/')?(strrchr(__FILE__,'/')+1):__FILE__
#define dbge(fmt,...) do{ \
	fprintf(stderr,"%s(%d)@%s: "fmt"\n",__FUNCTION__,__LINE__,__file__,##__VA_ARGS__); \
}while(0);
int main(int argc, char *argv[]){
	printf("%s@%d: \n", __FUNCTION__, __LINE__); 
	dbge(); 
	return 0; 
}

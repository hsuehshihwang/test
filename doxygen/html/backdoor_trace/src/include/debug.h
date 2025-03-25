#ifndef __DEBUG_H__
#define __DEBUG_H__

#define DBG(msg) printf("%s", msg)

#define FDBG(_format,_argv...) printf(_format,## _argv)

#define EDBG() printf("File:%s, Line:%d, Func.:%s()",__FILE__,__LINE__,__FUNCTION__)

#endif /*__DEBUG_H__*/

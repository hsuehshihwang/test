#ifndef __CMD_HEADER_H__
#define __CMD_HEADER_H__

#define CMD_MAGIC 0x11223344

typedef struct cmd_header_t{
	unsigned int magic; 
	unsigned char cmd; 
	unsigned int len; 
} cmd_header ; 


enum {
	CMD_FIRST=1, 
	CMD_RECV=CMD_FIRST, 
	CMD_OK,
	CMD_UNKNOWN,
	CMD_ERR,
	CMD_LAST
}; 

#endif /*__CMD_HEADER_H__*/

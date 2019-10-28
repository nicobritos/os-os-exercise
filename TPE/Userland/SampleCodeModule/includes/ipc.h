#ifndef _IPC_H
	#define _IPC_H
	#include <stdint.h>

	#define _PIPE_NO_ERROR 0
	#define _PIPE_UNKNOWN_NAME -5
	#define _PIPE_NAME_ALREADY_EXISTS -6
	#define _PIPE_INVALID_NAME -7

	#define _PIPE_READ (1L)
	#define _PIPE_WRITE (1L << 1)
	#define _PIPE_CREATE (1L << 2)
	#define _PIPE_BUFFER 1024

	typedef struct t_pipeCDT *t_pipeADT;
	typedef struct t_pipe_listCDT *t_pipe_listADT;
	
#endif
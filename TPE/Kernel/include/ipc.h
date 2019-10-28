#ifndef _IPC_H
	#define _IPC_H
	#include <stdint.h>

	#define _PIPE_NO_ERROR 0
	#define _SEM_INVALID_SEMAPHORE -1
	#define _SEM_SEMAPHORE_MAX_VALUE -2
	#define _SEM_SEMAPHORE_MIN_VALUE -3
	#define _SEM_MEMORY_ALLOC_ERROR -4
	#define _PIPE_UNKNOWN_NAME -5
	#define _PIPE_NAME_ALREADY_EXISTS -6
	#define _PIPE_INVALID_NAME -7

	#define _PIPE_READ (1L)
	#define _PIPE_WRITE (1L << 1)
	#define _PIPE_CREATE (1L << 2)
	#define _PIPE_BUFFER 1024

	typedef struct t_pipeCDT *t_pipeADT;
	typedef struct t_pipe_listCDT *t_pipe_listADT;

	t_pipeADT openPipe(const char *name, uint8_t mode, int pid);
	void closePipe(t_pipeADT pipe, int pid);

	uint64_t read(t_pipeADT pipe, char *dst, uint64_t length);
	uint64_t write(t_pipeADT pipe, char *src, uint64_t length);
	
	// TODO: Listar
	t_pipe_listADT createPipeList();
	uint64_t getPipeListLength(t_pipe_listADT pipeList);
	uint8_t hasNextPipe(t_pipe_listADT pipeList);
	t_pipeADT getNextPipe(t_pipe_listADT pipeList);
	void freePipeList(t_pipe_listADT pipeList);
	
#endif
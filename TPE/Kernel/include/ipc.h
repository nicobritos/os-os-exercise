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

	typedef struct t_semCDT *t_semADT;

	t_pipeADT createPipe(const char *name);
	t_pipeADT openPipe(const char *name, uint8_t mode);
	void closePipe(t_pipeADT pipe);

	void read(char *dst, uint64_t length);
	void write(char *src, uint64_t length);
	
	// TODO: Listar
	
#endif
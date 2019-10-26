#ifndef _SYNC_H
	#define _SYNC_H
	#include <stdint.h>

	#define _SEM_NO_ERROR 0
	#define _SEM_INVALID_SEMAPHORE -1
	#define _SEM_SEMAPHORE_MAX_VALUE -2
	#define _SEM_SEMAPHORE_MIN_VALUE -3
	#define _SEM_MEMORY_ALLOC_ERROR -4
	#define _SEM_UNKNOWN_NAME -5
	#define _SEM_NAME_ALREADY_EXISTS -6
	#define _SEM_INVALID_NAME -7

	typedef struct t_semCDT *t_semADT;

	t_semADT createSemaphore(const char *name);
	t_semADT openSemaphore(const char *name);
	void closeSemaphore(t_semADT semaphore);

	int8_t post(t_semADT semaphore);
	int8_t wait(t_semADT semaphore);

	void removeProcess(int pid);

	// TODO: Listar

#endif
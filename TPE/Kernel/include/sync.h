#ifndef _SYNC_H
	#define _SYNC_H
	#include <stdint.h>

	#define _SEM_NO_ERROR 0
	#define _SEM_INVALID_SEMAPHORE -1
	#define _SEM_SEMAPHORE_MAX_VALUE -2
	#define _SEM_SEMAPHORE_MIN_VALUE -3
	#define _SEM_MEMORY_ALLOC_ERROR -4
	// #define _SEM_UNKNOWN_NAME -5
	// #define _SEM_NAME_ALREADY_EXISTS -6
	// #define _SEM_INVALID_NAME -7

	typedef struct t_semCDT *t_semADT;
	typedef struct t_process_nodeCDT *t_process_nodeADT;
	typedef struct t_semaphore_listCDT *t_semaphore_listADT;
	typedef struct t_semaphore_list_nodeCDT *t_semaphore_list_nodeADT;

	t_semADT createSemaphore(const char *name, int64_t initialValue);
	t_semADT openSemaphore(const char *name);
	void closeSemaphore(t_semADT semaphore, int pid);

	int8_t post(t_semADT semaphore);
	int8_t wait(t_semADT semaphore, int pid);
	int64_t getValue(t_semADT semaphore);

	void removeProcessSemaphore(int pid);

	// TODO: Listar
	t_semaphore_listADT createSemaphoreList();
	uint64_t getSemaphoreListLength(t_semaphore_listADT semaphoreList);
	uint64_t getWaitingProcessLength(t_semaphore_list_nodeADT semaphoreListNode);
	uint8_t hasNextSemaphore(t_semaphore_listADT semaphoreList);
	uint8_t hasNextWaitingProcess(t_semaphore_list_nodeADT semaphoreListNode);
	t_semaphore_list_nodeADT getNextSemaphore(t_semaphore_listADT semaphoreList);
	int getNextWaitingProcessPid(t_semaphore_list_nodeADT semaphoreListNode);
	void freeSemaphoreList(t_semaphore_listADT semaphoreList);

#endif
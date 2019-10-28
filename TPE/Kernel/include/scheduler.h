#ifndef _SCHEDULER_H
	#define _SCHEDULER_H
	#include "memManager.h"
	#include <stdint.h>
	#include "process.h"
	#include "lib.h"

	typedef enum {HIGH = 0, LOW} t_priority;
	typedef struct processListNodeCDT *processListNodeADT;
	typedef struct processListCDT *processListADT;

	void initializeScheduler(t_process *idleProcess);
	void runScheduler(t_stack *currentProcessStack);
	uint8_t addProcess(t_process *process, t_priority priority);

	void killProcess(int pid);
	t_process *getCurrentProcess();
	int getpid();
	void lockProcess(int pid);
	void unlockProcess(int pid);
	t_state getCurrentProcessState();

	// Process iterator
	processListADT createProcessList();
	uint64_t getProcessListLength(processListADT processList);
	uint8_t hasNextProcess(processListADT processList);
	t_process *getNextProcess(processListADT processList);
	void freeProcessesList(processListADT processList);
#endif

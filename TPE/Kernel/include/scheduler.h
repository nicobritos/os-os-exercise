#ifndef _SCHEDULER_H
	#define _SCHEDULER_H
	#include <stdint.h>
	#include "process.h"
	#include "list.h"
	#include "lib.h"

	typedef enum {HIGH = 0, LOW} t_priority;

	void initializeScheduler();
	void runScheduler(t_stack currentProcessStack);
	uint8_t addProcess(t_process process, t_priority priority);

	void killProcess(pid_t pid);
	t_process getCurrentProcess();
	pid_t getCurrentProcessPid();
	void lockProcess(pid_t pid);
	void unlockProcess(pid_t pid);
	t_state getCurrentProcessState();

	// Process iterator
	listADT createProcessList();
	uint64_t getProcessListLength(listADT processList);
	uint8_t hasNextProcess(listADT processList);
	t_process getNextProcess(listADT processList);
	void freeProcessesList(listADT processList);
#endif

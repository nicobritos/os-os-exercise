#ifndef _SCHEDULER_H
	#define _SCHEDULER_H
	#include <stdint.h>
	#include "process.h"
	#include "list.h"
	#include "lib.h"

	typedef enum {S_P_HIGH = 0, S_P_LOW, S_P_INVALID} t_priority;
	typedef enum {S_M_FOREGROUND = 0, S_M_BACKGROUND, S_M_INVALID} t_mode;

	void initializeScheduler();
	void runScheduler(t_stack currentProcessStack);
	uint8_t addProcess(t_process process, t_priority priority, t_mode mode);

	void killProcess(pid_t pid);
	t_process getCurrentProcess();
	void lockProcess(pid_t pid);
	void unlockProcess(pid_t pid);
	t_priority getCurrentProcessPriority();
	void setCurrentProcessPriority(t_priority priority);
	t_state getCurrentProcessState();
	void setCurrentProcessMode(t_mode mode);
	t_mode getCurrentProcessMode();

	void setOnProcessKillScheduler(void(_onProcessKill) (t_process process));


	// Process iterator
	listADT createProcessList();
	uint64_t getProcessListLength(listADT processList);
	uint8_t hasNextProcess(listADT processList);
	t_process getNextProcess(listADT processList);
	void freeProcessesList(listADT processList);
#endif

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
	
	uint8_t addProcess(t_process process, t_priority priority, t_mode mode, t_stack currentProcessStack);
	
	int8_t killProcess(pid_t pid, t_stack stackFrame);
	
	t_process getCurrentProcess();
	
	t_priority getCurrentProcessPriority();
	
	t_priority getProcessPriority(pid_t pid);

	t_state getCurrentProcessState();

	t_mode getCurrentProcessMode();

	t_mode getProcessMode(pid_t pid);

	void setCurrentProcessPriority(t_priority priority);

	void setProcessPriority(pid_t pid, t_priority priority);

	void setCurrentProcessMode(t_mode mode, t_stack currentProcessStack);
	
	void setProcessMode(pid_t pid, t_mode mode, t_stack currentProcessStack);
	
	void lockProcess(pid_t pid, t_stack stackFrame, t_lock_reason lockReason);
	
	void unlockProcess(pid_t pid, t_lock_reason lockReason);

	t_state toggleProcessLock(pid_t pid, t_stack stackFrame);

	void setOnProcessKillScheduler(void(_onProcessKill) (t_process process));

	void yieldScheduler(t_stack stackFrame);

	void waitpid(pid_t pid, t_stack currentProcessStack);

	void printProcessesScheduler();
	
	void sleepScheduler(uint64_t ms, t_stack currentProcessStack);

#endif

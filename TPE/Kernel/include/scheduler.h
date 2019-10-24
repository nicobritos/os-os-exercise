#ifndef _SCHEDULER_H
	#define _SCHEDULER_H

	#include <types.h>

	typedef enum {HIGH = 0, LOW} t_priority;

	void runScheduler();
	void addProcess(t_process process, t_priority priority);
	void killProcess(t_process process);
	void blockProcess(t_process process);
	void unblockProcess(t_process process);
	void getProcesses();
	void getCurrentProcess();
#endif

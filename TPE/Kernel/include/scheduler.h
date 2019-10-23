#ifndef _SCHEDULER_H
	#define _SCHEDULER_H

	#include <types.h>

	void init_scheduler();
	void run_scheduler();
	void run_process(process_t process);
	void kill_process(process_t process);
	void lock_process(process_t process);
	void unlock_process(process_t process);
	void get_processes();
	void get_current_process();
#endif

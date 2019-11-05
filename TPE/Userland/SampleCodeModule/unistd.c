#include "newSyscalls.h"
#include "unistd.h"
#include "defines.h"
#include "stdlib.h"
#include "process.h"

pid_t newProcessArgs(char * name, int(* foo)(int argc, char** argv), int argc, char * argv[], t_mode mode){
    return sys_newProcess(name, foo, argc, argv, mode);
}

pid_t newProcess(char * name, int(* foo)(int argc, char** argv), t_mode mode) {
	return newProcessArgs(name, foo, 0, NULL, mode);
}

void freeProcess(pid_t pid){
    sys_freeProcess(pid);
}

int getPid(){
    return sys_getPid();
}

int waitpid(pid_t pid) {
	return sys_wait_pid(pid);
}

void killProcess(pid_t pid) {
	sys_freeProcess(pid);
}

void setProcessMode(pid_t pid, t_mode mode) {   
    sys_set_process_mode(pid, mode);
}

void setProcessPriority(pid_t pid, t_priority priority){
    sys_set_process_priority(pid,priority);
}

t_state toogleProcessLock(pid_t pid){
    return sys_toggle_process_lock(pid);
}

void sleep(uint64_t ms) {
	sys_sleep(ms);
}

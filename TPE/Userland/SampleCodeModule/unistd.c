#include "newSyscalls.h"
#include "unistd.h"
#include "defines.h"

pid_t newProcessArgs(char * name, int(* foo)(int argc, char** argv), int argc, char * argv[]){
    return sys_newProcess(name, foo, argc, argv);
}

pid_t newProcess(char * name, int(* foo)(int argc, char** argv)) {
	return newProcessArgs(name, foo, 0, NULL);
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

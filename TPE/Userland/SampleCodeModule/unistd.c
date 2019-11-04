#include "newSyscalls.h"
#include "unistd.h"
#include "defines.h"

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

void changeProcessState(pid_t pid){
    t_state state = sys_get_process_state(pid);
    if (state == P_READY)
    {
       //cambiar a P_LOCKED 
    }
    else if(state == P_LOCKED){
        // cambiar a P_READY
    }
    
}


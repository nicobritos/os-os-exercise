#include "includes/unistd.h"
#include "includes/newSyscalls.h"

void * newProcess(char * name, int(* foo)(int argc, char** argv), int argc, char * argv[]){
    return sys_newProcess(name, foo, argc, argv);
}

void freeProcess(pid_t pid){
    sys_freeProcess(pid);
}

int getPid(){
    return sys_getPid();
}

int execute(void * process){
    //return os_exec(process);
    // return sys_exec(process);
}
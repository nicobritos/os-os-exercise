#include "includes/unistd.h"
#include "includes/newSyscalls.h"

pid_t newProcess(char * name, int(* foo)(int argc, char** argv), int argc, char * argv[]){
    return sys_newProcess(name, foo, argc, argv);
}

void freeProcess(pid_t pid){
    sys_freeProcess(pid);
}

int getPid(){
    return sys_getPid();
}
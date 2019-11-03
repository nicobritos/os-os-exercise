#include "includes/unistd.h"
//#include "includes/syscalls.h"
#include "includes/newSyscalls.h"

void * newProcess(char * name, int(* foo)(int argc, char** argv), int ppid, int argc, char * argv[], void * returnPosition){
    //return os_new_process(name, foo, ppid, argc, argv, returnPosition);
    return sys_newProcess(name, foo, ppid, argc, argv, returnPosition);
}

void freeProcess(void * process){
    //os_free_process(process);
    sys_freeProcess(process);
}

int getPid(void * process){
    //return os_get_pid(process);
    return sys_getPid(process);
}
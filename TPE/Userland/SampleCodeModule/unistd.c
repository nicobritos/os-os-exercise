#include "includes/unistd.h"
#include "includes/syscalls.h"

void * newProcess(char * name, int(* foo)(int argc, char** argv), int ppid, int argc, char * argv[], void * returnPosition){
    return os_new_process(name, foo, ppid, argc, argv, returnPosition);
}
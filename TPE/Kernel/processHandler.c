#include "processHandler.h"
#include "memManager.h"
#include "scheduler.h"

typedef struct
    {
    int pid;
    int pPid;
    char * name;
    t_state state; 
    void * stackPointer;
    void * processMemoryLowerAddress;
    void * processMemoryUpperAddress;
    int (*entryPoint)(int,char **); //a chequear
}t_process;

t_process * createProcess(uint64_t pid, char * name, int(* foo)(int argc, char** argv)){
    t_process * newProcess = initializeProcess(pid, name, foo);
    addProcess(newProcess);
    return newProcess;
}

int exec(t_process * process){
    return exec(process->processMemoryLowerAddress d)
}

int free(t_process * process){
    removeProcess(newProcess);
    pfree(process->pid, process);
}
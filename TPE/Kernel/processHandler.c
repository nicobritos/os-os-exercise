#include "processHandler.h"
#include "memManager.h"
//#include "scheduler.h"

#define NULL ((void *) 0)

char pids[MAX_PROC] = {0};

t_process * newProcess(char * name, int(* foo)(int argc, char** argv), int ppid, int argc, char * argv[], void * returnPosition){
    char finished = 0;
    unsigned int i;
    for (i = 0; i < MAX_PROC && !finished; i++)
    {
        if(pids[i] == 0){
            finished = 1;
        }
    }
    if(!finished)
        return NULL;
    t_process * newProcess = createProcess(name, (void *)foo, i, ppid, argc, argv, returnPosition);
    if(newProcess == NULL){
        return NULL;
    }
    //addProcess(newProcess);
    return newProcess;
}

int exec(t_process * process){
    // if(process != NULL)
    //     return sys_execv(process->processMemoryLowerAddress);
    // else
        return 1;
}

int free(t_process * process){
    if(process != NULL){
        freeProcess(newProcess);
        pfree(process->pid, process);
        return 0;
    }
    return 1;
}
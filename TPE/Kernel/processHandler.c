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
            pids[i] = 1;
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
     if(process != NULL)
         return process->processMemoryLowerAddress(0, NULL); //CAMBIAR, DEBERIA HACERLO EL SCHEDULER PORQUE LOS PARAMS ESTAN EN EL STACK
     else
        return 1;
}

int free(t_process * process){
    if(process != NULL){
        if(process->pid != 0)
            pids[(process->pid) - 1] = 0;
        freeProcess(process);
        return 0;
    }
    return 1;
}
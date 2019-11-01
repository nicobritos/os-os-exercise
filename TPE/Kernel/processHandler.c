#include "processHandler.h"
#include "memManager.h"
#include "scheduler.h"

void processWrapper(int argc, char * argv[], void * startingPoint);

static char pids[MAX_PROC] = {0};

t_process newProcess(char * name, int(* foo)(int argc, char** argv), int ppid, int argc, char * argv[]){
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
    t_process newProcess = createProcess(name, processWrapper, i, ppid, argc, argv, (void *) foo);
    if(newProcess == NULL){
        return NULL;
    }
    addProcess(newProcess, LOW);
    return newProcess;
}

void 
processWrapper(int argc, char * argv[], void * startingPoint)
{
    ((int (*)(int, void**))(startingPoint))(argc, argv);
    // int currentPid = getpid();
    //killProcess(currentPid);
}

int exec(t_process process) {

}

int free(t_process process){
//     if(process != NULL){
//         if(process->pid != 0)
//             pids[(process->pid) - 1] = 0;
//         freeProcess(process);
//         return 0;
//     }
//     return 1;
}

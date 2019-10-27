#include "process.h"
#include "scheduler.h"

#define NULL ((void *)0)

static int nextPid = 0; 
static t_process processes[MAX_PROC];

t_process *
createProcess(char * name, void* startingPoint,int ppid, int argc, char * argv[])
{
    t_process *  newProcess = malloc(sizeof(t_process));
    if(newProcess == NULL)
    {
        return NULL;
    }
    newProcess->pid = nextPid;
    newProcess->pPid = ppid;
    newProcess->name = name;
    newProcess->processMemoryLowerAddress = malloc(PROC_SIZE);
    if (newProcess->processMemoryLowerAddress == NULL)
    {
        free(newProcess);
        return NULL;
    }
    void * processMemoryUpperAddress = newProcess->processMemoryLowerAddress + PROC_SIZE - 1;
    newProcess->state = READY;
    newProcess->stackPointer = processMemoryUpperAddress - sizeof(t_stack) + 1;
    initializeStack(newProcess->stackPointer,argc, argv, startingPoint);
    
    processes[nextPid++] = * newProcess;
    int success = addProcess(newProcess,LOW);
    if (!success)
    {
        freeProcess(newProcess);
        return NULL;
    }

    return newProcess;
}

void 
processWrapper(int argc, char * argv[], void * startingPoint)
{
    ((int (*)(int, void**))(startingPoint))(argc, argv);
    int currentPid = getpid();
    killProcess(currentPid);
}

void
initializeStack(t_stack * stackFrame, int argc, char * argv[], void * startingPoint) {
    stackFrame->gs = 0x000;
    stackFrame->fs = 0x000;
    stackFrame->r15 = 0x000;
    stackFrame->r14 = 0x000;
    stackFrame->r13 = 0x000;
    stackFrame->r12 = 0x000;
    stackFrame->r11 = 0x000;
    stackFrame->r10 = 0x000;
    stackFrame->r9 =  0x000;
    stackFrame->r8 = 0x000;
    stackFrame->rsi = (uint64_t)argv;
    stackFrame->rdi = (uint64_t)argc;
    stackFrame->rdx = startingPoint;;
    stackFrame->rbp = 0x000
    stackFrame->rcx = 0x000;
    stackFrame->rbx = 0x000;
    stackFrame->rax = 0x000;
    stackFrame->rip = (void *)&processWrapper;
    stackFrame->cs = 0x008;
    stackFrame->eflags = 0x202;
    stackFrame->rsp = (uint64_t)&(stackFrame->base);
    stackFrame->ss = 0x000;
    stackFrame->base = 0x000;
}


void 
freeProcess(t_process * process)
{
    free(process->stackPointer);
    free(process);
}
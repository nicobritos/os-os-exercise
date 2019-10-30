#include "process.h"
#include "memManager.h"
//#include "scheduler.h"

#define NULL ((void *)0)
#define SYSTEM_PID 0


t_process * createProcess(char * name, void* startingPoint, int pid, int pPid, int argc, char * argv[], void * rip)
{
    t_process *  newProcess = pmalloc(sizeof(*newProcess), pid);
    if(newProcess == NULL)
    {
        return NULL;
    }
    newProcess->pid = pid;
    newProcess->pPid = pPid;
    newProcess->name = name;
    newProcess->processMemoryLowerAddress = pmalloc(PROC_SIZE, pid);
    if (newProcess->processMemoryLowerAddress == NULL)
    {
        pfree(newProcess, pid);
        return NULL;
    }
    void * processMemoryUpperAddress = newProcess->processMemoryLowerAddress + PROC_SIZE - 1;
    newProcess->state = READY;
    newProcess->stackPointer = processMemoryUpperAddress - sizeof(t_stack) + 1;
    initializeStack((t_stack *)(newProcess->stackPointer),argc, argv, startingPoint,rip);
    
    // int success = addProcess(newProcess,LOW);
    // if (!success)
    // {
    //     freeProcess(newProcess);
    //     return NULL;
    // }

    return newProcess;
}

/*
void 
processWrapper(int argc, char * argv[], void * startingPoint)
{
    ((int (*)(int, void**))(startingPoint))(argc, argv);
    //int currentPid = getpid();
    //killProcess(currentPid);
}

*/

void initializeStack(t_stack * stackFrame, int argc, char * argv[], void * startingPoint,void * rip) {
    //stackFrame->gs = 0x000;
    //stackFrame->fs = 0x000;
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
    stackFrame->rdx = startingPoint;
    stackFrame->rbp = 0x000;
    stackFrame->rcx = 0x000;
    stackFrame->rbx = 0x000;
    stackFrame->rax = 0x000;
    stackFrame->rip = rip;
    //stackFrame->cs = 0x008;
    stackFrame->rflags = 0x202;
    //stackFrame->rsp = (uint64_t)&(stackFrame->base);
    //stackFrame->ss = 0x000;
    //stackFrame->base = 0x000;
}


void freeProcess(t_process * process)
{
    pfree(process->processMemoryLowerAddress, process->pid);
    pfree(process, process->pid);
}

int getPid(t_process * process){
    return process->pid;
}
#include "process.h"
#include "memManager.h"
//#include "scheduler.h"

#define NULL ((void *)0)
#define SYSTEM_PID 0

void initializeStack(t_stack * stackFrame, int(* wrapper)(int argc, char** argv, int(* startingPoint)(int argc, char** argv)), int argc, char * argv[], int(* startingPoint)(int argc, char** argv));

t_process * createProcess(char * name, int(* wrapper)(int argc, char** argv, int(* startingPoint)(int argc, char** argv)), int pid, int pPid, int argc, char * argv[], int(* startingPoint)(int argc, char** argv))
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
    newProcess->stackPointer = processMemoryUpperAddress - sizeof(t_stack) ;
    initializeStack((t_stack *)(newProcess->stackPointer), wrapper, argc, argv, startingPoint);
    return newProcess;}


void initializeStack(t_stack * stackFrame, int(* wrapper)(int argc, char** argv, int(* startingPoint)(int argc, char** argv)), int argc, char * argv[], int(* startingPoint)(int argc, char** argv)) {
    stackFrame->r15 = 15;
    stackFrame->r14 = 14;
    stackFrame->r13 = 13;
    stackFrame->r12 = 12;
    stackFrame->r11 = 11;
    stackFrame->r10 = 10;
    stackFrame->r9 =  9;
    stackFrame->r8 = 8;
    
    stackFrame->rsi = (uint64_t)argv;
    stackFrame->rdi = (uint64_t)argc;
    stackFrame->rbp = (uint64_t)(stackFrame);
    stackFrame->rsp = (uint64_t)(stackFrame);

    stackFrame->rdx = (uint64_t)startingPoint;
    stackFrame->rcx = 7;
    stackFrame->rbx = 6;
    stackFrame->rax = 5;

    stackFrame->rip = (uint64_t)wrapper;
    stackFrame->rflags = 0x202;
    
    stackFrame->gs = 0x000;
    stackFrame->fs = 0x000;
    stackFrame->cs = 0x008;
    stackFrame->ss = 0x000;
}


void freeProcess(t_process * process)
{
    pfree(process->processMemoryLowerAddress, process->pid);
    pfree(process, process->pid);
}

int getPid(t_process * process){
    return process->pid;
}

void updateStack(t_stack *dst, t_stack *src) {
    dst->r15 = src->r15;
    dst->r14 = src->r14;
    dst->r13 = src->r13;
    dst->r12 = src->r12;
    dst->r10 = src->r11;
    dst->r11 = src->r10;
    dst->r9 =  src->r9;
    dst->r8 = src->r8;
    
    dst->rsi = src->rsi;
    dst->rdi = src->rdi;
    dst->rbp = src->rbp;
    dst->rsp = src->rsp;

    dst->rdx = src->rdx;
    dst->rcx = src->rcx;
    dst->rbx = src->rbx;
    dst->rax = src->rax;

    dst->rip = src->rip;
    dst->rflags = src->rflags;
    
    dst->gs = src->gs;
    dst->fs = src->fs;
    dst->cs = src->cs;
    dst->ss = src->ss;
}

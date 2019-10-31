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
    
    // int success = addProcess(newProcess,LOW);
    // if (!success)
    // {
    //     freeProcess(newProcess);
    //     return NULL;
    // }

    return newProcess;
}

// void 
// processWrapper(int argc, char * argv[], void * startingPoint)
// {
//     ((int (*)(int, void**))(startingPoint))(argc, argv);
//     //int currentPid = getpid();
//     //killProcess(currentPid);
// }


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
//     printf("ORIG\n");
//     printf("r15: %l\n", src->r15);
//     printf("r14: %l\n", src->r14);
//     printf("r13: %l\n", src->r13);
//     printf("r12: %l\n", src->r12);
//     printf("r11: %l\n", src->r11);
//     printf("r10: %l\n", src->r10);
//     printf("r9: %l\n", src->r9);
//     printf("r8: %l\n", src->r8);

//     printf("rsi: %l\n", src->rsi);
//     printf("rdi: %l\n", src->rdi);
//     printf("rbp: %l\n", src->rbp);
//     printf("rdx: %l\n", src->rdx);
//     printf("rcx: %l\n", src->rcx);
//     printf("rbx: %l\n", src->rbx);
//     printf("rax: %l\n", src->rax);

//     printf("gs: %l\n", src->gs);
//     printf("fs: %l\n", src->fs);
//     printf("ss: %l\n", src->ss);
//     printf("cs: %l\n", src->cs);

//     printf("rip?: %l\n", src->rip);
//     printf("rfl?: %l\n", src->rflags);
//     printf("rsp: %l\n", src->rsp);
//     printf(" --------------------- ");

    // printf("DST\n");
    // printf("r15: %l\n", dst->r15);
    // printf("r14: %l\n", dst->r14);
    // printf("r13: %l\n", dst->r13);
    // printf("r12: %l\n", dst->r12);
    // printf("r11: %l\n", dst->r11);
    // printf("r10: %l\n", dst->r10);
    // printf("r9: %l\n", dst->r9);
    // printf("r8: %l\n", dst->r8);

    // printf("rsi: %l\n", dst->rsi);
    // printf("rdi: %l\n", dst->rdi);
    // printf("rbp: %l\n", dst->rbp);
    // printf("rdx: %l\n", dst->rdx);
    // printf("rcx: %l\n", dst->rcx);
    // printf("rbx: %l\n", dst->rbx);
    // printf("rax: %l\n", dst->rax);

    // printf("gs: %l\n", dst->gs);
    // printf("fs: %l\n", dst->fs);
    // printf("ss: %l\n", dst->ss);
    // printf("cs: %l\n", dst->cs);

    // printf("rip?: %l\n", dst->rip);
    // printf("rfl?: %l\n", dst->rflags);
    // printf("rsp: %l\n", dst->rsp);
// printf("                                                      ");
// return;

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

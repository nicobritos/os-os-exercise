#include "scheduler.h"
#include "process.h"

#define STARTING_PID 1

void idleFunction();

static int nextPid = STARTING_PID; 
static t_process processes[MAX_PROC];
static t_process *idleProcess = NULL;

t_process *
createProcess(char * name, void* startingPoint,int ppid, int argc, char * argv[]) {
    t_process *newProcess = processes + (nextPid - STARTING_PID);

    newProcess->pid = nextPid;
    newProcess->pPid = ppid;
    newProcess->name = name;
    newProcess->processMemoryLowerAddress = pmalloc(PROC_SIZE, nextPid);
    if (newProcess->processMemoryLowerAddress == NULL)
    {
        return NULL;
    }
    void * processMemoryUpperAddress = newProcess->processMemoryLowerAddress + PROC_SIZE - 1;
    newProcess->state = READY;
    newProcess->stackPointer = processMemoryUpperAddress - sizeof(t_stack) + 1;
    initializeStack(newProcess->stackPointer,argc, argv, startingPoint);
    
    if (!addProcess(newProcess, LOW)) {
        freeProcess(newProcess->processMemoryLowerAddress);
        return NULL;
    }

    nextPid++;
    return newProcess;
}

t_process *getIdleProcess() {
    if (idleProcess == NULL) {
        idleProcess = processes + SYSTEM_PID;

        idleProcess->pid = SYSTEM_PID;
        idleProcess->pPid = SYSTEM_PID;
        idleProcess->name = IDLE_PROCESS_NAME;
        idleProcess->processMemoryLowerAddress = pmalloc(PROC_SIZE, SYSTEM_PID);
        if (idleProcess->processMemoryLowerAddress == NULL)
        {
            return NULL;
        }
        void * processMemoryUpperAddress = idleProcess->processMemoryLowerAddress + PROC_SIZE - 1;
        idleProcess->state = READY;
        idleProcess->stackPointer = processMemoryUpperAddress - sizeof(t_stack) + 1;
        initializeStack(idleProcess->stackPointer, 0, NULL, &idleFunction);
    }

    return idleProcess;
}

t_state getProcessState(int pid) {
    if (pid >= nextPid) return INVALID;
    return processes[pid].state;
}

void 
processWrapper(int argc, char * argv[], void * startingPoint)
{
    ((int (*)(int, char**))(startingPoint))(argc, argv);
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
    stackFrame->rdx = (uint64_t)startingPoint;
    stackFrame->rbp = 0x000;
    stackFrame->rcx = 0x000;
    stackFrame->rbx = 0x000;
    stackFrame->rax = 0x000;
    stackFrame->rip = (uint64_t)&processWrapper;
    stackFrame->cs = 0x008;
    stackFrame->eflags = 0x202;
    stackFrame->rsp = (uint64_t)&(stackFrame->base);
    stackFrame->ss = 0x000;
    stackFrame->base = 0x000;
}


void 
freeProcess(t_process * process)
{
    pfree(process->stackPointer, process->pid);
}

void updateStack(t_stack *dst, t_stack *src) {
    dst->gs = src->gs;
    dst->fs = src->fs;

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
    dst->rdx = src->rdx;
    dst->rbp = src->rbp;
    dst->rcx = src->rcx;
    dst->rbx = src->rbx;
    dst->rax = src->rax;
    dst->rip = src->rip;
    dst->cs = src->cs;

    dst->eflags = src->eflags;
    dst->rsp = src->rsp;

    dst->ss = src->ss;
    dst->base = src->base;
}

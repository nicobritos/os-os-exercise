#include "process.h"
//#include "scheduler.h"

static int nextPid = 0; 
static t_process processes[MAX_PROC];

t_process *
createProcess(char * name, int (*entryPoint)(int, char**),int ppid, int argc, char * argv[])
{
    t_process *  newProcess = malloc(sizeof(t_process));
    // VALIDAR EL MALLOC

    newProcess->pid = nextPid;
    newProcess->pPid = ppid;
    newProcess->name = name;
    newProcess->entryPoint = entryPoint;
    newProcess->processMemoryLowerAddress = malloc(PROC_SIZE);
    // VALIDAR EL MALLOC

    newProcess->processMemoryUpperAddress = newProcess->processMemoryLowerAddress + PROC_SIZE - 1;
    newProcess->state = READY;

    initializeStack(newProcess->stackPointer,newProcess->entryPoint,newProcess->processMemoryLowerAddress, argc, argv);
    
    processes[nextPid++] = * newProcess;
    int success = addProcess(newProcess /* , LOW  */ );
    if (!success)
    {
        //HACER EL FREE
    }

    return newProcess;
}

void 
initializeStack(t_stack * stackFrame, int (*entryPoint)(int, char**), void * startingPoint, int argc, char * argv[]) {
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
    stackFrame->rbp = 0x000;
    stackFrame->rdx = startingPoint;
    stackFrame->rcx = 0x000;
    stackFrame->rbx = 0x000;
    stackFrame->rax = 0x000;
    stackFrame->rip = entryPoint;
    stackFrame->cs = 0x008;
    stackFrame->eflags = 0x202;
    stackFrame->rsp = startingPoint;
    stackFrame->ss = 0x000;
}


void
deleteProcess(t_process * process)
{
    //free del processMemoryLowerAddress
    //free del process
}


void 
freeProcess(t_process process)
{
    // FRESS
}
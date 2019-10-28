#include "scheduler.h"
#include "process.h"


#define STARTING_PID 1

void idleFunction();

static pid_t nextPid = STARTING_PID; 
static t_process processes[MAX_PROC];
static t_process *idleProcess = NULL;

void initializeProcesses() {
    idleProcess = processes + SYSTEM_PID;
    printf("asdas\n");

    idleProcess->pid = SYSTEM_PID;
    idleProcess->pPid = SYSTEM_PID;
    idleProcess->name = IDLE_PROCESS_NAME;
    idleProcess->processMemoryLowerAddress = pmalloc(PROC_SIZE, SYSTEM_PID);
    printf("asdas\n");
    if (idleProcess->processMemoryLowerAddress == NULL)
    {
        return NULL;
    }
    void * processMemoryUpperAddress = idleProcess->processMemoryLowerAddress + PROC_SIZE - 1;
    idleProcess->state = READY;
    idleProcess->stackPointer = processMemoryUpperAddress - sizeof(t_stack) + 1;
    printf("asdas\n");
    initializeStack(idleProcess->stackPointer, 0, NULL, &idleFunction);
}

t_process *
createProcess(char * name, void* startingPoint,int ppid, int argc, char * argv[]) {
    if (nextPid == MAX_PROC) return NULL;
    t_process *newProcess = processes + (nextPid - STARTING_PID);
    printf("asdas\n");

    newProcess->pid = nextPid;
    newProcess->pPid = ppid;
    newProcess->name = name;
    printf("asdas\n");
    newProcess->processMemoryLowerAddress = pmalloc(PROC_SIZE, nextPid);
    printf("asdas\n");
    if (newProcess->processMemoryLowerAddress == NULL)
    {
        return NULL;
    }
    void * processMemoryUpperAddress = newProcess->processMemoryLowerAddress + PROC_SIZE - 1;
    newProcess->state = READY;
    newProcess->stackPointer = processMemoryUpperAddress - sizeof(t_stack) + 1;
    printf("asdas\n");

    initializeStack(newProcess->stackPointer, argc, argv, startingPoint);
    printf("asdas\n");
    
    if (!addProcess(newProcess, LOW)) {
        freeProcess(newProcess->processMemoryLowerAddress);
        return NULL;
    }

    nextPid++;
    return newProcess;
}

t_process *getIdleProcess() {
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
    int currentPid = getCurrentProcessPid();
    killProcess(currentPid);
}

void
initializeStack(t_stack * stackFrame, int argc, char * argv[], void * startingPoint) {
    stackFrame->gs = 0x1;
    stackFrame->fs = 0x1;
    stackFrame->r15 = 0x0;
    stackFrame->r14 = 0x0;
    stackFrame->r13 = 0x0;
    stackFrame->r12 = 0x0;
    stackFrame->r11 = 0x0;
    stackFrame->r10 = 0x0;
    stackFrame->r9 =  0x0;
    stackFrame->r8 = 0x0;
    stackFrame->rsi = (uint64_t)argv;
    stackFrame->rdi = (uint64_t)argc;
    stackFrame->rdx = (uint64_t)startingPoint;
    stackFrame->rbp = (uint64_t)(stackFrame);
    stackFrame->rcx = 0x0;
    stackFrame->rbx = 0x0;
    stackFrame->rax = 0x0;
    stackFrame->rip = (uint64_t)processWrapper;
    stackFrame->cs = 0x8;
    stackFrame->rflags = 0x202;
    stackFrame->rsp = (uint64_t)(stackFrame) ;
    stackFrame->ss = 0x0;
    // stackFrame->base = (uint64_t)(stackFrame) ;
    //updateStack(stackFrame, stackFrame);
}

void 
freeProcess(t_process * process)
{
    pfree(process->stackPointer, process->pid);
}

void updateStack(t_stack *dst, t_stack *src) {
    // printf("ORIG\n");
    // printf("r15: %l\n", src->r15);
    // printf("r14: %l\n", src->r14);
    // printf("r13: %l\n", src->r13);
    // printf("r12: %l\n", src->r12);
    // printf("r11: %l\n", src->r11);
    // printf("r10: %l\n", src->r10);
    // printf("r9: %l\n", src->r9);
    // printf("r8: %l\n", src->r8);

    // printf("rsi: %l\n", src->rsi);
    // printf("rdi: %l\n", src->rdi);
    // printf("rbp: %l\n", src->rbp);
    // printf("rdx: %l\n", src->rdx);
    // printf("rcx: %l\n", src->rcx);
    // printf("rbx: %l\n", src->rbx);
    // printf("rax: %l\n", src->rax);
    // printf("rip: %l\n", src->rip);
    // printf("rfl: %l\n", src->rflags);
    // printf("rsp: %l\n", src->rsp);
    // printf(" --------------------- ");

    printf("DST\n");
    printf("r15: %l\n", dst->r15);
    printf("r14: %l\n", dst->r14);
    printf("r13: %l\n", dst->r13);
    printf("r12: %l\n", dst->r12);
    printf("r11: %l\n", dst->r11);
    printf("r10: %l\n", dst->r10);
    printf("r9: %l\n", dst->r9);
    printf("r8: %l\n", dst->r8);

    printf("rsi: %l\n", dst->rsi);
    printf("rdi: %l\n", dst->rdi);
    printf("rbp: %l\n", dst->rbp);
    printf("rdx: %l\n", dst->rdx);
    printf("rcx: %l\n", dst->rcx);
    printf("rbx: %l\n", dst->rbx);
    printf("rax: %l\n", dst->rax);
    printf("gs: %l\n", dst->gs);
    printf("fs: %l\n", dst->fs);

    printf("rip?: %l\n", dst + (17 * 8));
    printf("rfl?: %l\n", dst->rflags);
    printf("rsp: %l\n", dst->rsp);
    printf("ss: %l\n", dst->rsp);
    printf("rsp: %l\n", dst->rsp);
    printf("                                                      ");

    dst->gs = src->gs;
    dst->fs = src->fs;
    //return;

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
    dst->rdx = src->rdx;
    dst->rcx = src->rcx;
    dst->rbx = src->rbx;
    dst->rax = src->rax;
    dst->rip = src->rip;
    dst->cs = src->cs;

    dst->rflags = src->rflags;
    dst->rsp = src->rsp;
    dst->ss = src->ss;
    // dst->base = src->base;
}

t_process *forkProcess(t_process *process) {
    //t_process *newProcess = createProcess(process->name, process->rip, process->pid, 0, NULL);
    //updateStack(newProcess->stackFrame, process->stackFrame);
}

int8_t processExecve(t_process *process, const char *pathname) {

}

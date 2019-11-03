#include "videoDriver.h"
#include "memManager.h"
#include "process.h"

typedef struct t_processCDT {
    pid_t pid;
    pid_t pPid;
    char * name;
    t_state state; 
    t_stack stackPointer;
    int(* processMemoryLowerAddress)(int argc, char** argv);
} t_processCDT;

typedef struct t_stackCDT {
    uint64_t r15;
    uint64_t r14;
    uint64_t r13;
    uint64_t r12;
    uint64_t r11;
    uint64_t r10;
    uint64_t r9;
    uint64_t r8;

    uint64_t rsi;
    uint64_t rdi;
    uint64_t rbp;

    uint64_t rdx;
    uint64_t rcx;
    uint64_t rbx;
    uint64_t rax;

    uint64_t gs;
    uint64_t fs;

// iret 
    uint64_t rip;
    uint64_t cs;
    uint64_t rflags;
    uint64_t rsp;
    uint64_t ss;
} t_stackCDT;

void initializeStack(t_stack stackFrame, int(* wrapper)(int argc, char** argv, int(* startingPoint)(int argc, char** argv)), int argc, char * argv[], int(* startingPoint)(int argc, char** argv));

t_process createProcess(char * name, int(* wrapper)(int argc, char** argv, int(* startingPoint)(int argc, char** argv)), pid_t pid, pid_t pPid, int argc, char * argv[], int(* startingPoint)(int argc, char** argv)) {
    t_process newProcess = pmalloc(sizeof(t_processCDT), pid);
    if(newProcess == NULL) {
        return NULL;
    }
    newProcess->pid = pid;
    newProcess->pPid = pPid;
    newProcess->name = name;
    newProcess->processMemoryLowerAddress = pmalloc(PROC_SIZE, pid);
    if (newProcess->processMemoryLowerAddress == NULL) {
        pfree(newProcess, pid);
        return NULL;
    }
    void * processMemoryUpperAddress = newProcess->processMemoryLowerAddress + PROC_SIZE - 1;
    newProcess->state = P_READY;
    newProcess->stackPointer = processMemoryUpperAddress - sizeof(t_stackCDT);
    initializeStack((t_stack)(newProcess->stackPointer), wrapper, argc, argv, startingPoint);

    return newProcess;
}


void initializeStack(t_stack stackFrame, int(* wrapper)(int argc, char** argv, int(* startingPoint)(int argc, char** argv)), int argc, char * argv[], int(* startingPoint)(int argc, char** argv)) {
    stackFrame->r15 = 0;
    stackFrame->r14 = 0;
    stackFrame->r13 = 0;
    stackFrame->r12 = 0;
    stackFrame->r11 = 0;
    stackFrame->r10 = 0;
    stackFrame->r9 =  0;
    stackFrame->r8 = 0;
    
    stackFrame->rsi = (uint64_t)argv;
    stackFrame->rdi = (uint64_t)argc;
    stackFrame->rbp = (uint64_t)(stackFrame);
    stackFrame->rsp = (uint64_t)(stackFrame);

    stackFrame->rdx = (uint64_t)startingPoint;
    stackFrame->rcx = 0;
    stackFrame->rbx = 0;
    stackFrame->rax = 0;

    stackFrame->rip = (uint64_t)wrapper;
    stackFrame->rflags = 0x202;
    
    stackFrame->gs = 0;
    stackFrame->fs = 0;
    stackFrame->cs = 8;
    stackFrame->ss = 0;
}

void freeProcess(t_process process) {
    pfree(process->processMemoryLowerAddress, process->pid);
    pfree(process, process->pid);
}

void updateProcessStack(t_stack dst, t_stack src) {
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

void updateProcessStackRegister(t_stack stackFrame, uint64_t value, t_process_register processRegister) {
    switch (processRegister) {
        case REGISTER_RAX:
            stackFrame->rax = value;
            break;
        case REGISTER_RBX:
            stackFrame->rbx = value;
            break;
        case REGISTER_RCX:
            stackFrame->rcx = value;
            break;
        case REGISTER_RDX:
            stackFrame->rdx = value;
            break;

        case REGISTER_RSI:
            stackFrame->rsi = value;
            break;
        case REGISTER_RDI:
            stackFrame->rdi = value;
            break;

        case REGISTER_R8:
            stackFrame->r8 = value;
            break;
        case REGISTER_R9:
            stackFrame->r9 = value;
            break;
        case REGISTER_R10:
            stackFrame->r10 = value;
            break;
        case REGISTER_R11:
            stackFrame->r11 = value;
            break;
        case REGISTER_R12:
            stackFrame->r12 = value;
            break;
        case REGISTER_R13:
            stackFrame->r13 = value;
            break;
        case REGISTER_R14:
            stackFrame->r14 = value;
            break;
        case REGISTER_R15:
            stackFrame->r15 = value;
            break;

        default: break;
    }
}

void setProcessState(t_process process, t_state state) {
    process->state = state;
}

t_state getProcessState(t_process process) {
    return process->state;
}

t_stack getProcessStackFrame(t_process process) {
    return process->stackPointer;
}

pid_t getProcessPid(t_process process) {
    return process->pid;
}

pid_t getProcessPPid(t_process process) {
    return process->pPid;
}

void execve(t_process process, int(* wrapper)(int argc, char** argv, int(* startingPoint)(int argc, char** argv)), int argc, char * argv[], int(* startingPoint)(int argc, char** argv)) {
    initializeStack(process->stackPointer, wrapper, argc, argv, startingPoint);
}

t_process duplicateProcess(t_process source, pid_t pid) {
    t_process process = createProcess(source->name, (int (*)(int,  char **, int (*)(int,  char **))) source->stackPointer->rip, pid, source->pid, 0, NULL, NULL);
    process->state = source->state;
    updateProcessStack(process->stackPointer, source->stackPointer);
    return process;
}

t_process duplicateProcessReadOnly(t_process source) {
    t_process process = pmalloc(sizeof(t_processCDT), SYSTEM_PID);
    process->pid = source->pid;
    process->pPid = source->pPid;
    process->name = source->name;
    process->state = source->state;
    process->processMemoryLowerAddress = source->processMemoryLowerAddress;

    process->stackPointer = pmalloc(sizeof(t_stackCDT), SYSTEM_PID);
    memcpy(process->stackPointer, source->stackPointer, sizeof(t_stackCDT));

    return process;
}

void freeProcessReadOnly(t_process process) {
    pfree(process->stackPointer, SYSTEM_PID);
    pfree(process, SYSTEM_PID);
}

void printStackFrame(t_stack stackFrame) {
    char* regs[]= {"R15 ","R14 ","R13 ","R12 ","R11 ","R10 ","R9 ","R8 ","RSI ","RDI ","RBP ","RDX ","RCX ","RBX ","RAX ", "GS ", "FS ", "RIP ", "CS ", "RFLAGS ", "RSP ", "SS "};

    for (int i = 0; i < sizeof(*stackFrame) / sizeof(uint64_t); i++){
        newLine();
        printString(regs[i],255,255,255);
        printHexa(((uint64_t*)stackFrame)[i]);
    }
    newLine();
}

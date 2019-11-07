//This is a personal academic project. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "fileManager.h"
#include "videoDriver.h"
#include "memManager.h"
#include "process.h"

typedef struct t_processCDT {
    pid_t pid;
    pid_t pPid;
    char * name;
    t_state state;
    t_stack stackPointer;
    t_lock_reason lockReason;
    fd_t fds[MAX_FILES_PER_PROCESS];
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
char *getProcessStateString(t_state state);
char *getProcessLockReasonString(t_lock_reason lockReason);

t_process createProcess(char * name, int(* wrapper)(int argc, char** argv, int(* startingPoint)(int argc, char** argv)), pid_t pid, pid_t pPid, int argc, char * argv[], int(* startingPoint)(int argc, char** argv)) {
    t_process newProcess = pmalloc(sizeof(t_processCDT), SYSTEM_PID);
    if(newProcess == NULL) {
        return NULL;
    }
    newProcess->pid = pid;
    newProcess->pPid = pPid;
    newProcess->name = pmalloc(strlen(name) + 1, pid);
    strcpy(newProcess->name, name);
    newProcess->processMemoryLowerAddress = pmalloc(PROC_SIZE, pid);
    if (newProcess->processMemoryLowerAddress == NULL) {
        pfree(newProcess->name, pid);
        pfree(newProcess, pid);
        return NULL;
    }
    void * processMemoryUpperAddress = newProcess->processMemoryLowerAddress + PROC_SIZE - 1;
    newProcess->state = P_READY;
    newProcess->stackPointer = (void *)((char *)processMemoryUpperAddress - sizeof(t_stackCDT));
    initializeStack((t_stack)(newProcess->stackPointer), wrapper, argc, argv, startingPoint);
    newProcess->fds[STDIN] = STDIN;
    newProcess->fds[STDOUT] = STDOUT;
    newProcess->lockReason = L_INVALID;

    return newProcess;
}

fd_t getProcessFd(t_process process, fd_t from) {
    if (from < MAX_FILES_PER_PROCESS)
        return process->fds[from];
    return 0;
}

void redirectProcessFd(t_process process, fd_t from, fd_t to) {
    if (from < MAX_FILES_PER_PROCESS)
        process->fds[from] = to;
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

void freeProcess(t_process process) {
    pfree(process->processMemoryLowerAddress, process->pid);
    pfree(process->name, process->pid);
    pfree(process, SYSTEM_PID);
}

void updateProcessStackRegister(t_stack stackFrame, t_process_register processRegister, uint64_t value) {
    switch (processRegister) {
        case REGISTER_R15:
            stackFrame->r15 = value;
            break;
        case REGISTER_R14:
            stackFrame->r14 = value;
            break;
        case REGISTER_R13:
            stackFrame->r13 = value;
            break;
        case REGISTER_R12:
            stackFrame->r12 = value;
            break;
        case REGISTER_R11:
            stackFrame->r11 = value;
            break;
        case REGISTER_R10:
            stackFrame->r10 = value;
            break;
        case REGISTER_R9:
            stackFrame->r9 = value;
            break;
        case REGISTER_R8:
            stackFrame->r8 = value;
            break;

        case REGISTER_RSI:
            stackFrame->rsi = value;
            break;
        case REGISTER_RDI:
            stackFrame->rdi = value;
            break;
        case REGISTER_RBP:
            stackFrame->rbp = value;
            break;

        case REGISTER_RDX:
            stackFrame->rdx = value;
            break;
        case REGISTER_RCX:
            stackFrame->rcx = value;
            break;
        case REGISTER_RBX:
            stackFrame->rbx = value;
            break;
        case REGISTER_RAX:
            stackFrame->rax = value;
            break;

        case REGISTER_GS:
            stackFrame->gs = value;
            break;
        case REGISTER_FS:
            stackFrame->fs = value;
            break;

        case REGISTER_RIP:
            stackFrame->rip = value;
            break;
        case REGISTER_CS:
            stackFrame->cs = value;
            break;
        case REGISTER_RFLAGS:
            stackFrame->rflags = value;
            break;
        case REGISTER_RSP:
            stackFrame->rsp = value;
            break;
        case REGISTER_SS:
            stackFrame->ss = value;
            break;
        default: break;
    }
}

void setProcessState(t_process process, t_state state, t_lock_reason lockReason) {
    process->state = state;
    if (state == P_LOCKED)
        process->lockReason = lockReason;
}

t_state getProcessState(t_process process) {
    if (process != NULL) return process->state;
    return P_INVALID;
}

t_lock_reason getProcessLockReason(t_process process) {
    if (process != NULL) return process->lockReason;
    return L_INVALID;
}

t_stack getProcessStackFrame(t_process process) {
    if (process == NULL) return NULL;
    return process->stackPointer;
}

uint64_t getProcessStackFrameRegister(t_process process, t_process_register processRegister) {
    if (process == NULL) return 0;
    t_stack stackFrame = process->stackPointer;
    switch (processRegister) {
        case REGISTER_R15:
            return stackFrame->r15;
        case REGISTER_R14:
            return stackFrame->r14;
        case REGISTER_R13:
            return stackFrame->r13;
        case REGISTER_R12:
            return stackFrame->r12;
        case REGISTER_R11:
            return stackFrame->r11;
        case REGISTER_R10:
            return stackFrame->r10;
        case REGISTER_R9:
            return stackFrame->r9;
        case REGISTER_R8:
            return stackFrame->r8;

        case REGISTER_RSI:
            return stackFrame->rsi;
        case REGISTER_RDI:
            return stackFrame->rdi;
        case REGISTER_RBP:
            return stackFrame->rbp;

        case REGISTER_RDX:
            return stackFrame->rdx;
        case REGISTER_RCX:
            return stackFrame->rcx;
        case REGISTER_RBX:
            return stackFrame->rbx;
        case REGISTER_RAX:
            return stackFrame->rax;

        case REGISTER_GS:
            return stackFrame->gs;
        case REGISTER_FS:
            return stackFrame->fs;

        case REGISTER_RIP:
            return stackFrame->rip;
        case REGISTER_CS:
            return stackFrame->cs;
        case REGISTER_RFLAGS:
            return stackFrame->rflags;
        case REGISTER_RSP:
            return stackFrame->rsp;
        case REGISTER_SS:
            return stackFrame->ss;
        default: return 0;
    }
}

pid_t getProcessPid(t_process process) {
    if (process == NULL) return -1;
    return process->pid;
}

pid_t getProcessPPid(t_process process) {
    if (process == NULL) return -1;
    return process->pPid;
}

int8_t execve(t_process process, int(* wrapper)(int argc, char** argv, int(* startingPoint)(int argc, char** argv)), int argc, char * argv[], int(* startingPoint)(int argc, char** argv)) {
    initializeStack(process->stackPointer, wrapper, argc, argv, startingPoint);
    return 1;
}

void hello() {
    printString("HGO", 255, 0 ,0);
    while(1);
}

void printStackFrame(t_stack stackFrame) {
    char* regs[]= {"R15 ","R14 ","R13 ","R12 ","R11 ","R10 ","R9 ","R8 ","RSI ","RDI ","RBP ","RDX ","RCX ","RBX ","RAX ", "GS ", "FS ", "RIP ", "CS ", "RFLAGS ", "RSP ", "SS "};

    for (int i = 0; i < sizeof(*stackFrame) / sizeof(uint64_t); i++){
        newLine();
        printString(regs[i],255,255,255);
        printHexa(((uint64_t*)stackFrame)[i], 0, 255, 0);
    }
    newLine();
}

void printProcess(t_process process) {
    printString(process->name, 0, 255, 0);
    printString(" | ", 0, 255, 0);
    printDec(process->pid, 0, 255, 0);
    printString(" | ", 0, 255, 0);
    printDec(process->pPid, 0, 255, 0);
    printString(" | ", 0, 255, 0);
    printString(getProcessStateString(process->state), 0, 255, 0);
    printString(" | ", 0, 255, 0);
    if (process->state != P_LOCKED) {
        printString(getProcessLockReasonString(L_INVALID), 0, 255, 0);
    } else {
        printString(getProcessLockReasonString(process->lockReason), 0, 255, 0);
    }
}

void printProcessHeader() {
    printString("NAME | PID | PPID | STATE | LOCK REASON", 0, 255, 0);
}

char *getProcessStateString(t_state state) {
    switch (state) {
        case P_RUNNING: return "RUNNING";
        case P_READY: return "READY";
        case P_DEAD: return "DEAD";
        case P_LOCKED: return "LOCKED";
        default: return "INVALID";
    }
}

char *getProcessLockReasonString(t_lock_reason lockReason) {
    switch (lockReason) {
        case L_IO: return "I/O";
        case L_FOREGROUND: return "FOREGROUND STACK";
        case L_TIME: return "TIME";
        case L_ARBITRARY: return "ARBITRARY";
        default: return "---";
    }
}

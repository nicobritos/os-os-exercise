#ifndef PROCESS_H
#define PROCESS_H

#include "stdint.h"
#include "lib.h"

#define PROC_SIZE 4096
#define MAX_PROC 20

typedef int64_t pid_t;

typedef enum {RUNNING, READY, WAITING, DEAD, LOCKED, INVALID} t_state;

typedef struct
    {
    int pid;
    int pPid;
    char * name;
    t_state state; 
    void * stackPointer;
    int(* processMemoryLowerAddress)(int argc, char** argv);
    }t_process;

typedef struct 
    {
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
    } __attribute__((packed)) t_stack;

t_process * createProcess(char * name, int(* wrapper)(int argc, char** argv, int(* startingPoint)(int argc, char** argv)), int pid, int pPid, int argc, char * argv[], int(* startingPoint)(int argc, char** argv));
void freeProcess(t_process * process);
int getPid(t_process * process);

#endif

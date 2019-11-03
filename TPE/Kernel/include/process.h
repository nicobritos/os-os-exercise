#ifndef PROCESS_H
#define PROCESS_H

#include "stdint.h"
#include "lib.h"

#define PROC_SIZE 4096
#define SYSTEM_PID 0
#define MAX_PROC 20

typedef int64_t pid_t;

typedef enum {P_RUNNING, P_READY, P_DEAD, P_LOCKED, P_INVALID} t_state;

typedef enum {
	REGISTER_R15,
	REGISTER_R14,
	REGISTER_R13,
	REGISTER_R12,
	REGISTER_R11,
	REGISTER_R10,
	REGISTER_R9, 
	REGISTER_R8,
	
	REGISTER_RSI,
	REGISTER_RDI,
	REGISTER_RBP,

	REGISTER_RDX,
	REGISTER_RCX,
	REGISTER_RBX,
	REGISTER_RAX,
	
	REGISTER_GS,
	REGISTER_FS,

	REGISTER_RIP,
	REGISTER_CS,
	REGISTER_RFLAGS,
	REGISTER_RSP,
	REGISTER_SS
} t_process_register;

typedef struct t_processCDT *t_process;
typedef struct t_stackCDT *t_stack;

t_process createProcess(char * name, int(* wrapper)(int argc, char** argv, int(* startingPoint)(int argc, char** argv)), pid_t pid, pid_t pPid, int argc, char * argv[], int(* startingPoint)(int argc, char** argv));

void freeProcess(t_process process);

void setProcessState(t_process process, t_state state);

void updateProcessStack(t_stack dst, t_stack src);

void updateProcessStackRegister(t_stack stackFrame, t_process_register processRegister, uint64_t value);

t_state getProcessState(t_process process);

t_stack getProcessStackFrame(t_process process);

pid_t getProcessPid(t_process process);

pid_t getProcessPPid(t_process process);

void execve(t_process process, int(* wrapper)(int argc, char** argv, int(* startingPoint)(int argc, char** argv)), int argc, char * argv[], int(* startingPoint)(int argc, char** argv));

t_process duplicateProcess(t_process source, pid_t pid);

t_process duplicateProcessReadOnly(t_process source);

void freeProcessReadOnly(t_process process);

void printStackFrame(t_stack stackFrame);

#endif

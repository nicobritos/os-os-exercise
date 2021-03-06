#ifndef PROCESS_H
#define PROCESS_H

#include "stdint.h"
#include "files.h"
#include "lib.h"

#define PROC_SIZE 4096
#define SYSTEM_PID 0
#define MAX_FILES_PER_PROCESS 20

typedef int64_t pid_t;

typedef enum {P_RUNNING, P_READY, P_DEAD, P_LOCKED, P_INVALID} t_state;
typedef enum {L_IO, L_FOREGROUND, L_TIME, L_ARBITRARY, L_INVALID} t_lock_reason;

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

void setProcessState(t_process process, t_state state, t_lock_reason lockReason);

t_lock_reason getProcessLockReason(t_process process);

fd_t getProcessFd(t_process process, fd_t from);

void redirectProcessFd(t_process process, fd_t from, fd_t to);

void updateProcessStack(t_stack dst, t_stack src);

void updateProcessStackRegister(t_stack stackFrame, t_process_register processRegister, uint64_t value);

uint64_t getProcessStackFrameRegister(t_process process, t_process_register processRegister);

t_state getProcessState(t_process process);

t_stack getProcessStackFrame(t_process process);

pid_t getProcessPid(t_process process);

pid_t getProcessPPid(t_process process);

int8_t execve(t_process process, int(* wrapper)(int argc, char** argv, int(* startingPoint)(int argc, char** argv)), int argc, char * argv[], int(* startingPoint)(int argc, char** argv));

void printStackFrame(t_stack stackFrame);

void printProcess(t_process process);

void printProcessHeader();

#endif

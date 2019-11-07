#ifndef PROCESS_HANDLER_H_
#define PROCESS_HANDLER_H_

#include "interruptHelper.h"
#include "scheduler.h"
#include "process.h"

#define MAX_PROC 200
#define SYSTEM_PID 0

void initializeProcessHandler();
t_process newProcess(char * name, int(* foo)(int argc, char** argv), int ppid, int argc, char * argv[], t_priority priority, t_mode mode, t_stack stackFrame);
int processWrapper(int argc, char * argv[], int(* startingPoint)(int argc, char** argv));
int8_t execveProcessHandler(t_process process, int argc, char * argv[], int(* startingPoint)(int argc, char** argv));
int8_t killProcessHandler(pid_t pid, t_stack currentProcessStackFrame);
t_process duplicateProcessHandler(t_process source, t_stack stackFrame);
t_process getProcess(pid_t pid);
t_state getProcessStatePid(pid_t pid);

#endif
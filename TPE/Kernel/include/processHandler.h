#ifndef PROCESS_HANDLER_H_
#define PROCESS_HANDLER_H_

#include "interruptHelper.h"
#include "scheduler.h"
#include "process.h"

#define SYSTEM_PID 0

t_process newProcess(char * name, int(* foo)(int argc, char** argv), int ppid, int argc, char * argv[], t_priority priority, t_mode mode);
int processWrapper(int argc, char * argv[], int(* startingPoint)(int argc, char** argv), pid_t pid);
void freeProcessHandler(t_process process);

#endif
#ifndef PROCESS_HANDLER_H_
#define PROCESS_HANDLER_H_

#include "process.h"

#define SYSTEM_PID 0

t_process newProcess(char * name, int(* foo)(int argc, char** argv), int ppid, int argc, char * argv[]);
int exec(t_process process);
int free(t_process process);
#endif
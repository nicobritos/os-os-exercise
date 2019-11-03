#ifndef UNISTD_H_
#define UNISTD_H_

#include "process.h"

void * newProcess(char * name, int(* foo)(int argc, char** argv), int argc, char * argv[]);
void freeProcess(pid_t pid);
int getPid();
int execute(void * process);

#endif

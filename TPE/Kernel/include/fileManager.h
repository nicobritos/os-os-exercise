#ifndef __FILE_MANAGER_H
#define __FILE_MANAGER_H
#include "process.h"

#define STDIN 0
#define STDOUT 1

typedef int64_t fd_t;

void initializeFileManager();
uint64_t readFile(fd_t fd, char *buffer, uint64_t size, t_stack currentProcessStackFrame);
uint64_t writeFile(fd_t fd, char *buffer, uint64_t size, t_stack currentProcessStackFrame);
void keyWasPressed();

#endif

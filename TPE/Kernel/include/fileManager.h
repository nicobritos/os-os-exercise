#ifndef __FILE_MANAGER_H
#define __FILE_MANAGER_H
#include "process.h"
#include "files.h"

void initializeFileManager();
uint64_t readFile(fd_t fd, char *buffer, uint64_t size, t_stack currentProcessStackFrame);
uint64_t writeFile(fd_t fd, char *buffer, uint64_t size, t_stack currentProcessStackFrame);
void keyWasPressed();

#endif

#ifndef __FILE_MANAGER_H
#define __FILE_MANAGER_H
#include "process.h"
#include "files.h"

void initializeFileManager();
fd_t openPipe(const char *name, uint64_t mode, t_process process);
void closePipe(fd_t fd, t_process process);
uint64_t readFile(fd_t fd, char *buffer, uint64_t size, t_stack currentProcessStackFrame);
uint64_t writeFile(fd_t fd, char *buffer, uint64_t size, t_stack currentProcessStackFrame);
void keyWasPressed();

#endif

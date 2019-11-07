#ifndef MUTEX_H_
#define MUTEX_H_

#include "process.h"
#include "list.h"

typedef struct t_mutexCDT *t_mutexADT;

t_mutexADT createMutex();
void closeMutex(t_mutexADT mutex);

void lockMutex(t_mutexADT mutex);
void waitMutex(t_mutexADT mutex, t_process process, t_stack currentProcessStackFrame);
void postMutex(t_mutexADT mutex, uint64_t returnValue);
uint8_t isMutexLocked(t_mutexADT mutex);

#endif

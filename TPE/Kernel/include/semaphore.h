#ifndef SEMAPHORE_H_
#define SEMAPHORE_H_

#include "process.h"
#include "list.h"

typedef struct t_sem{
    int64_t value;
    listADT processes;
    char * name;
}t_sem;

t_sem * createSem(char * name);
t_sem * openSem(char * name);
void closeSem(t_sem * sem);

void waitSemaphore(t_sem * sem, uint64_t pid, t_stack currentProcessStackFrame);
void postSemaphore(t_sem * sem);

char * semListString();

void prepareSemListIterator();
uint8_t hasNextSemListIterator();
t_sem * getNextSemIterator();

#endif
#ifndef SEMAPHORE_H_
#define SEMAPHORE_H_

#include "list.h"

typedef struct t_sem{
    int64_t value;
    listADT processes;
    char * name;
}t_sem;

t_sem * createSem(char * name);
t_sem * openSem(char * name);
void closeSem(t_sem * sem);

void wait(t_sem * sem, uint64_t pid);
void post(t_sem * sem);

void prepareSemListIterator();
uint8_t hasNextSemListIterator();
t_sem * getNextSemIterator();

#endif
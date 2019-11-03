#include "include/memManager.h"
#include "include/scheduler.h"
#include "include/lib.h"
#include "mutex.h"

typedef struct t_mutexCDT {
    uint8_t locked;
    listADT processes;
} t_mutexCDT;

t_mutexADT createMutex(){
    t_mutexADT mutex = pmalloc(sizeof(*mutex), 0);
    mutex->locked = 0;
    mutex->processes = createList();
    return mutex;
}

void closeMutex(t_mutexADT mutex) {
    postMutex(mutex);
    freeList(mutex->processes, NULL);
    pfree(mutex, SYSTEM_PID);
}

void lockMutex(t_mutexADT mutex) {
    mutex->locked = 1;
}

void waitMutex(t_mutexADT mutex, uint64_t pid, t_stack currentProcessStackFrame){
    if (!mutex->locked) mutex->locked = 1;

    addElementToIndexList(mutex->processes, (void *)pid, getSizeList(mutex->processes));
    lockProcess(pid, currentProcessStackFrame);
}

void postMutex(t_mutexADT mutex) {
    if (mutex->locked) {
        mutex->locked = 0;

        if (!isEmptyList(mutex->processes)) {
            nodeListADT node = getNodeAtIndexList(mutex->processes, 0);

            for (uint64_t i = 0; i < getSizeList(mutex->processes) - 1; i++) {
                unlockProcess((pid_t) getElementList(node));
                node = getNextNodeList(node);
            }
            unlockProcess((pid_t) getElementList(node));    
        }
    }
}

uint8_t isMutexLocked(t_mutexADT mutex) {
    return mutex->locked;
}

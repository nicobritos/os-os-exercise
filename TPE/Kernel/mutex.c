//This is a personal academic project. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
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
    postMutex(mutex, 0);
    freeList(mutex->processes, NULL);
    pfree(mutex, SYSTEM_PID);
}

void lockMutex(t_mutexADT mutex) {
    mutex->locked = 1;
}

void waitMutex(t_mutexADT mutex, t_process process, t_stack currentProcessStackFrame){
    if (!mutex->locked) mutex->locked = 1;

    addElementToIndexList(mutex->processes, (void *)process, getSizeList(mutex->processes));
    lockProcess(getProcessPid(process), currentProcessStackFrame, L_IO);
}

void postMutex(t_mutexADT mutex, uint64_t returnValue) {
    if (mutex->locked) {
        mutex->locked = 0;

        if (!isEmptyList(mutex->processes)) {
            nodeListADT node = getNodeAtIndexList(mutex->processes, 0);

            for (uint64_t i = 0; i < getSizeList(mutex->processes); i++) {
                t_process process = (t_process) getElementList(node);
                updateProcessStackRegister(getProcessStackFrame(process), REGISTER_RAX, returnValue);
                unlockProcess(getProcessPid(process), L_IO);
                node = getNextNodeList(node);
            }
        }
    }
}

uint8_t isMutexLocked(t_mutexADT mutex) {
    return mutex->locked;
}

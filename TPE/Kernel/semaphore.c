#include "include/semaphore.h"
#include "include/memManager.h"
#include "include/lib.h"
#include "include/scheduler.h"

listADT semList = NULL;

t_sem * createSem(char * name){
    t_sem * newSem = pmalloc(sizeof(t_sem), 0);
    strcpy(newSem->name, name);
    newSem->value = 0;
    newSem->processes = createList();

    if(semList == NULL){
        semList = createList();
    }
    addElementToIndexList(semList, newSem, getSizeList(semList));
    return newSem;
}

t_sem * openSem(char * name){
    prepareListIterator(semList);
    while (hasNextListIterator(semList))
    {
        t_sem * sem = (t_sem *)getElementList(getNextNodeListIterator(semList));
        if(strcmp(sem->name, name) == 0){
            return sem;
        }
    }
    return NULL;
}

void closeSem(t_sem * sem){
    if(!isEmptyList(semList)){
        removeNodeList(semList, sem);
        pfree(sem, 0);
    }
}

void wait(t_sem * sem, uint64_t pid){
    (sem->value)--;
    if(sem->value < 0){
        addElementToIndexList(sem->processes, pid, getSizeList(sem->processes));
        lockProcess(pid);
    }
}

void post(t_sem * sem){
    (sem->value)++;
    if(!isEmptyList(sem->processes)){
        uint64_t pid = (uint64_t) getElementList(getNodeAtIndexList(sem->processes, 0));
        removeNodeAtIndexList(sem->processes, 0);
        unlockProcess(pid);
    }
}

void prepareSemListIterator(){
    prepareListIterator(semList);
}

uint8_t hasNextSemListIterator(){
    return hasNextListIterator(semList);
}

t_sem * getNextSemIterator(){
    return getElementList(getNextNodeListIterator(semList));
}
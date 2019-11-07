//This is a personal academic project. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "include/semaphore.h"
#include "include/memManager.h"
#include "include/lib.h"
#include "include/scheduler.h"
#include "include/process.h"

#define MAX_STR_SIZE 500

listADT semList = NULL;

int equals(t_sem * elem, t_sem * other){
    return !strcmp(elem->name, other->name);
}

t_sem * createSem(char * name){
    t_sem * newSem = pmalloc(sizeof(t_sem), SYSTEM_PID);
    newSem->name = pmalloc(strlen(name)+1, SYSTEM_PID);
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
    if(!isEmptyList(semList) && sem != NULL){
        removeNodeList(semList, searchNodeList(semList, sem, (int (*)(void *, void *))equals));
        freeList(sem->processes, NULL);
        pfree(sem->name, SYSTEM_PID);
        pfree(sem, SYSTEM_PID);
    }
}

void waitSemaphore(t_sem * sem, uint64_t pid, t_stack currentProcessStackFrame){
    (sem->value)--;
    if(sem->value < 0){
        addElementToIndexList(sem->processes, (void *)pid, getSizeList(sem->processes));
        lockProcess(pid, currentProcessStackFrame, L_IO);
    }
}

void postSemaphore(t_sem * sem){
    (sem->value)++;
    if(!isEmptyList(sem->processes)){
        uint64_t pid = (uint64_t) getElementList(getNodeAtIndexList(sem->processes, 0));
        removeNodeAtIndexList(sem->processes, 0);
        unlockProcess(pid, L_IO);
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

char * semListString(){
    char * buffer = pmalloc(MAX_STR_SIZE, getProcessPid(getCurrentProcess()));
    if(isEmptyList(semList)){
        strncpy(buffer, "No hay semaforos", MAX_STR_SIZE);
    } else {
        uint64_t i = 0;
        prepareSemListIterator();
        while (hasNextSemListIterator())
        {
            t_sem * sem = getNextSemIterator();
            strncpy(buffer + i, sem->name, MAX_STR_SIZE - i);
            i += strlen(sem->name);
            if(i < MAX_STR_SIZE){
                buffer[i++] = ':';
                if(i < MAX_STR_SIZE){
                    buffer[i++] = ' ';
                    if(i < MAX_STR_SIZE){
                        char aux[10];
                        itoa(sem->value, aux, 10);
                        strncpy(buffer + i, aux, MAX_STR_SIZE - i);
                        i += strlen(aux);
                        if(i < MAX_STR_SIZE){
                            buffer[i++] = '\n';
                        }
                        else{
                            buffer[MAX_STR_SIZE - 1] = 0;
                            return buffer;
                        }
                    }
                    else{
                        buffer[MAX_STR_SIZE - 1] = 0;
                        return buffer;
                    }
                }
                else{
                    buffer[MAX_STR_SIZE - 1] = 0;
                    return buffer;
                }
            }
            else{
                buffer[MAX_STR_SIZE - 1] = 0;
                return buffer;
            }
            
        }
        if( i < MAX_STR_SIZE)
            buffer[i] = 0;
        else{
            buffer[MAX_STR_SIZE - 1] = 0;
        }
    }
    return buffer;
}

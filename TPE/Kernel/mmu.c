#include "include/mmu.h"
#include <stdlib.h>

#define CHUNK 10

int64_t lookPidIndex(uint64_t pid);


typedef struct
{
    uint64_t pid;
    uint64_t size;
    void * address;
} mmuRegister;

mmuRegister * table = NULL;
uint32_t tableSize = 0;
void * giveMemory(uint64_t pid, uint64_t bytes){
    if((tableSize % CHUNK) == 0){
        table = realloc(table, tableSize + sizeof(*table) * CHUNK);
    }

    mmuRegister row;
    row.pid = pid;
    row.size = bytes;
    row.address = malloc(bytes);

    table[tableSize++] = row;

    return row.address;
}

void * modifyMemory(uint64_t pid, uint64_t bytes){
    int64_t index = lookPidIndex(pid);
    if(index == -1){
        return giveMemory(pid, bytes);
    }
    else{
        table[index].size = bytes;
        table[index].address = realloc(table[index].address, bytes);
        return table[index].address;
    }
}

int64_t lookPidIndex(uint64_t pid){
    for(uint32_t i = 0; i<tableSize; i++){
        if(table[i].pid == pid)
            return i;
    }
    return -1;
}
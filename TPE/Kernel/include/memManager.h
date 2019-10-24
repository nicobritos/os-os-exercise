#ifndef _MEM_MANAGER_H_
#define _MEM_MANAGER_H_

#include <stdint.h>
#include "modoMemManager.h"

#define MEM_STARTING_ADDRESS ((void *)0x0000000000100000) // Tiene que haber 1MB continuo libre desde aca

void initializeMemoryManager();
void * pmalloc(uint64_t size, uint64_t pid);
void * prealloc(void * ptr, uint64_t newSize, uint64_t pid);
void pfree(uint64_t pid, void * address);

// void printTree();
// void printTable();
// void printList();

#endif

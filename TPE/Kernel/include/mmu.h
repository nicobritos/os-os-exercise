#ifndef MMU_H
#define MMU_H

#include <stdint.h>

void * giveMemory(uint64_t pid, uint64_t bytes);
void * modifyMemory(uint64_t pid, uint64_t bytes);

#endif
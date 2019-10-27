#ifndef LIB_H
#define LIB_H

#define NULL ((void*) 0)
#include <stdint.h>

void * memset(void * destination, int32_t character, uint64_t length);
void * memcpy(void * destination, const void * source, uint64_t length);

char *cpuVendor(char *result);

#endif
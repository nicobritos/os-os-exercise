#ifndef _STRING_H
	#define _STRING_H
	#include <stdint.h>

	int8_t strcmp(const char *cmp, const char *to);
	uint64_t strcpy(char *dst, const char *src);
	uint64_t strlen(const char *s);

#endif
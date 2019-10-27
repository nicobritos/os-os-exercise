#include "string.h"

// PUBLIC
int8_t strcmp(const char *s1, const char *s2) {
	int16_t difference = 0;
	uint64_t i = 0;
	while ((difference = s1[i] - s2[i]) && s1[i] != '\0' && s2[i] != '\0') {
		i++;
	}
	return difference;
}

uint64_t strcpy(char *dst, const char *src) {
	uint64_t length = 0;
	
	while (*src != '\0') {
		*dst = *src;
		src++;
		dst++;
		length++;
	}
	*dst = '\0';

	return length;
}

uint64_t strlen(const char *s) {
	uint64_t length = 0;
	
	while (*s != '\0') {
		s++;
		length++;
	}

	return length;
}

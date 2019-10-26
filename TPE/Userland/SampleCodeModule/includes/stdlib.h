#ifndef STDLIB_H_
#define STDLIB_H_
#include <stdint.h>

int strlen(char* str);

int strcmp(char* str1, char* str2);

int strncmp(char* str1, char* str2, int n);

int itoa(int num, char* string, int base);

int atoi(char c);

void * malloc(uint64_t size);

void free(void * address);

unsigned int lineCount(char * input);

char * filterVowels(char * dest, char * src);

#endif /* STDLIB_H_ */
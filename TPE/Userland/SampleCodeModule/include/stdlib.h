#ifndef STDLIB_H_
#define STDLIB_H_
#include <stdint.h>

unsigned int strlen(char* str);

int strcmp(char* str1, char* str2);

int strncmp(char* str1, char* str2, int n);

int itoa(int num, char* string, int base);

int atoi(char * s);

int atox(char * s);

void * malloc(uint64_t size);

void free(void * address);

unsigned int lineCount(char * input);

char * filterVowels(char * dest, char * src, int maxLength);

char *trim(char *input);

uint64_t replaceChars(char *input, char target, char newChar);

uint64_t tokenArgs(char ** argv, char * output, char * input, uint64_t max);

#endif /* STDLIB_H_ */
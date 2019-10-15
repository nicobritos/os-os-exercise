#ifndef STDLIB_H_
#define STDLIB_H_

int strlen(char* str);

int strcmp(char* str1, char* str2);

int strncmp(char* str1, char* str2, int n);

int itoa(int num, char* string, int base);

int atoi(char c);

#endif /* STDLIB_H_ */
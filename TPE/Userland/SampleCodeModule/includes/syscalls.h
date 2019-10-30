#ifndef SYSCALLS_H
#define SYSCALLS_H

#include <stdint.h>

int os_ticks(void);
int os_sec(void);
uint64_t read(uint64_t fd, char *buffer, uint64_t size);
uint64_t write(uint64_t fd, char *buffer, uint64_t size);
uint64_t * os_time(void);
uint64_t os_draw(uint64_t x, uint64_t y, uint64_t red,uint64_t green,uint64_t blue);
void os_clear(void);
uint64_t os_used_mem(void);
uint64_t os_free_mem(void);
void * os_malloc(uint64_t size, uint64_t pid);
void os_free(void * address, uint64_t size);
void * os_new_process(char * name, int(* foo)(int argc, char** argv), int ppid, int argc, char * argv[], void * returnPosition);
void os_free_process(void * process);
int os_get_pid(void * process);

#endif

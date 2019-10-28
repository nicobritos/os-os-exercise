#ifndef SYSTEMCALLS_H
#define SYSTEMCALLS_H

#include <stdint.h>
#include "ipc.h"
#include "process.h"

int sys_total_ticks(int * ticks);
int sys_ticks_per_second(int * ticks);
void sys_clear();
uint64_t sys_read(uint64_t fd, char *buffer, uint64_t size);
uint64_t sys_write(uint64_t fd, char *buffer, uint64_t size);
void sys_pixel(uint64_t x, uint64_t y, unsigned char r, unsigned char g, unsigned char b);
uint64_t * sys_time(uint64_t * time); 
uint64_t sys_used_mem();
uint64_t sys_free_mem();
void * sys_malloc(uint64_t size, uint64_t pid);
void sys_free(void * address, uint64_t pid);
uint64_t sys_read_pipe(t_pipeADT pipe, char *buffer, uint64_t size);
uint64_t sys_write_pipe(t_pipeADT pipe, char *buffer, uint64_t size);
pid_t sys_getpid();
pid_t sys_fork();
int8_t sys_execve(const char *pathname, char *const argv[]);
int8_t sys_kill(pid_t pid);

#endif /* SYSTEMCALLS_H */
#ifndef NEW_SYS_CALL_C
#define NEW_SYS_CALL_C

#include <stdint.h>

int sys_ticks(int * ticks);
int sys_ticksPerSecond(int * ticks);
int sys_clear();
int sys_read(uint64_t fd, char *buffer, uint64_t size);
int sys_write(uint64_t fd, char *buffer, uint64_t size);
int sys_draw(uint64_t x, uint64_t y, unsigned char r, unsigned char g, unsigned char b);
int * sys_time(int * time);
uint64_t sys_usedMem();
uint64_t sys_freeMem(void);
void * sys_malloc(uint64_t size, uint64_t pid);
void sys_free(void * address, uint64_t pid);
void * sys_newProcess(char * name, int(* foo)(int argc, char** argv), int ppid, int argc, char * argv[], void * returnPosition);
void sys_freeProcess(void * process);
int sys_getPid(void * process);
int sys_readPipe(void * pipe, char *buffer, uint64_t size);
int sys_writePipe(void * pipe, char *buffer, uint64_t size);
void * sys_createSem(char *name);
void * sys_openSem(char *name);
void sys_closeSem(void * sem);
void sys_wait(void * sem, uint64_t pid);
void sys_post(void * sem);
void sys_printSems();

#endif
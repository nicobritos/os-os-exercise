#ifndef NEW_SYS_CALL_C
#define NEW_SYS_CALL_C

#include <stdint.h>

int sys_read( int fileDescriptor, void * buff, int length);
int sys_write(int fileDescriptor, void * buff, int length);
int sys_clear();
int sys_draw( int x, int y, int red, int green, int blue);
int * sys_time();
int sys_exec(void * process);
int sys_getPid(void * process);
void * sys_newProcess(char * name, int(* foo)(int argc, char** argv), int ppid, int argc, char * argv[], void * returnPosition);
void sys_freeProcess(void * process);
void sys_free(void * address, uint64_t size);
int sys_ticks(int * ticks);
int sys_ticksPerSecond(int * ticks);
uint64_t sys_usedMem(void);
uint64_t sys_freeMem(void);
void * sys_malloc(uint64_t size, uint64_t pid);

#endif
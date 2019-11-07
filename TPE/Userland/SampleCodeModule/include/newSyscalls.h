#ifndef NEW_SYS_CALL_C
#define NEW_SYS_CALL_C

#include "process.h"
#include <stdint.h>
#include "files.h"

typedef enum {
	__SYSTEM_CALL_READ = 0,
	__SYSTEM_CALL_WRITE = 1,
	__SYSTEM_CALL_CLEAR = 2,
	__SYSTEM_CALL_DRAW = 3,
	__SYSTEM_CALL_TIME = 4,
	__SYSTEM_CALL_GET_PID = 5,
	__SYSTEM_CALL_NEW_PROCESS = 6,
	__SYSTEM_CALL_FREE_PROCESS = 7,
	__SYSTEM_CALL_FREE = 8,
	__SYSTEM_CALL_TICKS = 9,
	__SYSTEM_CALL_TICKS_PER_SECOND = 10,
	__SYSTEM_CALL_USED_MEM = 11,
	__SYSTEM_CALL_FREE_MEM = 12,
	__SYSTEM_CALL_MALLOC = 13,
	__SYSTEM_CALL_YIELD = 14,
	__SYSTEM_CALL_GET_PROCESS_MODE = 15,
	__SYSTEM_CALL_SET_PROCESS_MODE = 16,
	__SYSTEM_CALL_GET_PROCESS_PRIORITY = 17,
	__SYSTEM_CALL_SET_PROCESS_PRIORITY = 18,
	__SYSTEM_CALL_GET_PROCESS_STATE = 19,
	__SYSTEM_CALL_CREATE_SEM = 20,
	__SYSTEM_CALL_OPEN_SEM = 21,
	__SYSTEM_CALL_CLOSE_SEM = 22,
	__SYSTEM_CALL_WAIT = 23,
	__SYSTEM_CALL_POST = 24,
	__SYSTEM_CALL_PRINT_SEMS = 25,
	__SYSTEM_CALL_WAIT_PID = 26,
	__SYSTEM_CALL_PRINT_PROCESSES = 27,
	__SYSTEM_CALL_TOGGLE_PROCESS_LOCK = 28,
	__SYSTEM_CALL_SLEEP = 29,
	__SYSTEM_CALL_REDIRECT_FD = 30,
	__SYSTEM_CALL_OPEN_PIPE = 31,
	__SYSTEM_CALL_CLOSE_PIPE = 32,
	__SYSTEM_CALL_PRINT_PIPES = 33
} t_system_call;

uint64_t sys_read(int fileDescriptor, void * buff, int length);

uint64_t sys_write(int fileDescriptor, void * buff, int length);

uint64_t sys_clear();

uint64_t sys_draw(int x, int y, int red, int green, int blue);

int * sys_time(int * dest);

pid_t sys_getPid();

pid_t sys_newProcess(char * name, int(* foo)(int argc, char** argv), int argc, char * argv[], t_mode mode);

int8_t sys_freeProcess(pid_t pid);

void sys_free(void * address);

uint64_t sys_ticks(uint64_t * ticks);

uint64_t sys_ticksPerSecond(uint64_t * ticks);

uint64_t sys_usedMem();

uint64_t sys_freeMem();

void *sys_malloc(uint64_t size);

void sys_yield();

t_mode sys_get_process_mode(pid_t pid);

void sys_set_process_mode(pid_t pid, t_mode mode);

t_priority sys_get_process_priority(pid_t pid);

void sys_set_process_priority(pid_t pid, t_priority priority);

t_state sys_get_process_state(pid_t pid);

t_state sys_toggle_process_lock(pid_t pid);

int sys_readPipe(void * pipe, char *buffer, uint64_t size);

int sys_writePipe(void * pipe, char *buffer, uint64_t size);

void * sys_createSem(char *name);

void * sys_openSem(char *name);

void sys_closeSem(void * sem);

void sys_wait_semaphore(void * sem);

void sys_post_semaphore(void * sem);

char * sys_printSems();

int sys_wait_pid(pid_t pid);

void sys_printProcesses();

void sys_sleep(uint64_t ms);

uint8_t sys_redirect_fd(fd_t from, fd_t to);

fd_t sys_openPipe(const char *name, uint64_t mode);

void sys_closePipe(fd_t fd);

char * sys_printPipes();

#endif

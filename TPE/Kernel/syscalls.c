#include <stdint.h>
#include "time.h"
#include "include/memManager.h"
#include "include/processHandler.h"
#include "include/interrupts.h"
#include "scheduler.h"
#include "process.h"
#include "include/ipc.h"
#include "include/fileManager.h"
#include "include/semaphore.h"

typedef uint64_t(*systemCall)();

uint64_t sys_not_implemented();

uint64_t sys_ticks(int * ticks);

uint64_t sys_ticksPerSecond(int * ticks);

uint64_t sys_clear();

uint64_t sys_read(uint64_t fd, char *buffer, uint64_t size, uint64_t rcx, uint64_t r8, t_stack currentProcessStackFrame);

uint64_t sys_write(uint64_t fd, char *buffer, uint64_t size, uint64_t rcx, uint64_t r8, t_stack currentProcessStackFrame);

uint64_t sys_draw(uint64_t x, uint64_t y, unsigned char r, unsigned char g, unsigned char b);

uint64_t *sys_time(uint64_t * time);

uint64_t sys_usedMem();

uint64_t sys_freeMem();

void *sys_malloc(uint64_t size);

void sys_free(void * address);

pid_t sys_new_process(char * name, int(* foo)(int argc, char** argv), int argc, char * argv[], t_mode mode);

void sys_free_process(pid_t pid, uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, t_stack stackFrame);

pid_t sys_get_pid();

void sys_yield(uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, t_stack stackFrame);

t_mode sys_get_process_mode(pid_t pid);

void sys_set_process_mode(pid_t pid, t_mode mode);

t_priority sys_get_process_priority(pid_t pid);

void sys_set_process_priority(pid_t pid, t_priority priority);

t_state sys_get_process_state(pid_t pid);

t_sem * sys_createSem(char *name);

t_sem * sys_openSem(char *name);

void sys_closeSem(t_sem * sem);

void sys_wait_semaphore(t_sem * sem, uint64_t pid, uint64_t rdx, uint64_t rcx, uint64_t r8, t_stack currentProcessStackFrame);

void sys_post_semaphore(t_sem * sem);

void sys_printSems();

void sys_wait_pid(pid_t pid, uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, t_stack currentProcessStackFrame);

void sys_printProcesses();

t_state sys_toggle_process_lock(pid_t pid, uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, t_stack currentProcessStackFrame);

void sys_sleep(uint64_t ms, uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, t_stack currentProcessStackFrame);

systemCall sysCalls[] = { 
	(systemCall) sys_read,
	(systemCall) sys_write,
	(systemCall) sys_clear,
	(systemCall) sys_draw,
	(systemCall) sys_time,
	(systemCall) sys_get_pid,
	(systemCall) sys_new_process,
	(systemCall) sys_free_process,
	(systemCall) sys_free,
	(systemCall) sys_ticks,
	(systemCall) sys_ticksPerSecond,
	(systemCall) sys_usedMem,
	(systemCall) sys_freeMem,
	(systemCall) sys_malloc,
	(systemCall) sys_yield,
	(systemCall) sys_get_process_mode,
	(systemCall) sys_set_process_mode,
	(systemCall) sys_get_process_priority,
	(systemCall) sys_set_process_priority,
	(systemCall) sys_get_process_state,
	(systemCall) NULL,
	(systemCall) NULL,
	(systemCall) sys_createSem,
	(systemCall) sys_openSem,
	(systemCall) sys_closeSem,
	(systemCall) sys_wait_semaphore,
	(systemCall) sys_post_semaphore,
	(systemCall) sys_printSems,
	(systemCall) sys_wait_pid,
	(systemCall) sys_printProcesses,
	(systemCall) sys_toggle_process_lock,
	(systemCall) sys_sleep
};

void syscallHandler(uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9, t_stack stackFrame){
	uint64_t returnValue;

	pid_t pid = getProcessPid(getCurrentProcess());
	if (rdi < sizeof(sysCalls) / sizeof(*sysCalls)) returnValue = sysCalls[rdi](rsi, rdx, rcx, r8, r9, stackFrame);
	else returnValue = sys_not_implemented();

	if (pid == getProcessPid(getCurrentProcess()))
		updateProcessStackRegister(stackFrame, REGISTER_RAX, returnValue);
}

uint64_t sys_not_implemented() {
	return 0;
}

uint64_t sys_ticks(int * ticks) {
	*ticks = ticks_elapsed();
	return *ticks;
}

uint64_t sys_ticksPerSecond(int * ticks) {
	*ticks = seconds_elapsed();
	return *ticks;
}

uint64_t sys_clear() {
	clearAll();
	return 0;
}

uint64_t sys_read(uint64_t fd, char *buffer, uint64_t size, uint64_t rcx, uint64_t r8, t_stack currentProcessStackFrame){
	return readFile(fd, buffer, size, currentProcessStackFrame);
}

uint64_t sys_write(uint64_t fd, char *buffer, uint64_t size, uint64_t rcx, uint64_t r8, t_stack currentProcessStackFrame){
	return writeFile(fd, buffer, size, currentProcessStackFrame);
}

uint64_t sys_draw(uint64_t x, uint64_t y, unsigned char r, unsigned char g, unsigned char b) {
	putPixel(x,y,r,g,b);
	return 0;
}

uint64_t *sys_time(uint64_t * time) {
	uint64_t hour = getHour();
	uint64_t min = getMin();
	uint64_t sec = getSec(); 

	switch(hour){
		case 0: hour = 21;
				break;
		case 1: hour = 22;
				break;
		case 2: hour = 23;
				break;
		default: hour -= 3;
	}

	time[0] = hour/10;
	time[1] = hour%10;
	time[2] = min/10;
	time[3] = min%10;
	time[4] = sec/10;
	time[5] = sec%10;;
	return time;
}

uint64_t sys_usedMem(){
	return usedMemory();
}

uint64_t sys_freeMem(){
	return freeMemoryLeft();
}

void *sys_malloc(uint64_t size){
	return pmalloc(size, getProcessPid(getCurrentProcess()));
}
void sys_free(void * address){
	pfree(address, getProcessPid(getCurrentProcess()));
}

pid_t sys_new_process(char * name, int(* foo)(int argc, char** argv), int argc, char * argv[], t_mode mode){
	return getProcessPid(newProcess(name, foo, getProcessPPid(getCurrentProcess()), argc, argv, S_P_LOW, mode));
}

void sys_free_process(pid_t pid, uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, t_stack stackFrame) {
	killProcessHandler(pid, stackFrame);
}

pid_t sys_get_pid(){
	return getProcessPid(getCurrentProcess());
}

void sys_yield(uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, t_stack stackFrame) {
	yieldScheduler(stackFrame);
}

t_mode sys_get_process_mode(pid_t pid) {
	return getProcessMode(pid);
}

void sys_set_process_mode(pid_t pid, t_mode mode) {
	setProcessMode(pid, mode);
}

t_priority sys_get_process_priority(pid_t pid) {
	return getProcessPriority(pid);
}

void sys_set_process_priority(pid_t pid, t_priority priority) {
	setProcessPriority(pid, priority);
}

t_state sys_get_process_state(pid_t pid) {
	return getProcessStatePid(pid);
}

t_sem * sys_createSem(char *name){
	return createSem(name);
}

t_sem * sys_openSem(char *name){
	return openSem(name);
}

void sys_closeSem(t_sem * sem){
	return closeSem(sem);
}

void sys_wait_semaphore(t_sem * sem, uint64_t pid, uint64_t rdx, uint64_t rcx, uint64_t r8, t_stack currentProcessStackFrame) {
	waitSemaphore(sem, getProcessPid(getCurrentProcess()), currentProcessStackFrame);
}

void sys_post_semaphore(t_sem * sem){
	postSemaphore(sem);
}

void sys_printSems(){
	char * str = semListString();
	printString(str, 0, 255, 0);
	pfree(str, SYSTEM_PID);
}

void sys_wait_pid(pid_t pid, uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, t_stack currentProcessStackFrame) {
	waitpid(pid, currentProcessStackFrame);
}

void sys_printProcesses() {
	printProcessesScheduler();
}

t_state sys_toggle_process_lock(pid_t pid, uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, t_stack currentProcessStackFrame) {
	toggleProcessLock(pid, currentProcessStackFrame);
}


void sys_sleep(uint64_t ms, uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, t_stack currentProcessStackFrame) {
	sleepScheduler(ms, currentProcessStackFrame);
}

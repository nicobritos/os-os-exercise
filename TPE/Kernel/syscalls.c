#include <stdint.h>
#include "include/keyboard-Driver.h"
#include "include/videoDriver.h"
#include "time.h"
#include "include/memManager.h"
#include "include/processHandler.h"
#include "include/interrupts.h"
#include "scheduler.h"
#include "process.h"

#define AMOUNT_SYSCALLS 14

typedef uint64_t(*systemCall)();

uint64_t sys_not_implemented();

uint64_t sys_ticks(int * ticks);

uint64_t sys_ticksPerSecond(int * ticks);

uint64_t sys_clear();

uint64_t sys_read(uint64_t fd, char *buffer, uint64_t size);

uint64_t sys_write(uint64_t fd, char *buffer, uint64_t size);

uint64_t sys_draw(uint64_t x, uint64_t y, unsigned char r, unsigned char g, unsigned char b);

uint64_t *sys_time(uint64_t * time);

uint64_t sys_usedMem();

uint64_t sys_freeMem();

void *sys_malloc(uint64_t size);

void sys_free(void * address);

void *sys_new_process(char * name, int(* foo)(int argc, char** argv), int argc, char * argv[]);

void sys_free_process(pid_t pid, t_stack stackFrame);

pid_t sys_get_pid();

static int first = 0;

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
		(systemCall) sys_malloc
};

void syscallHandler(uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, t_stack stackFrame){
	uint64_t returnValue;

	if (rdi < AMOUNT_SYSCALLS)	returnValue = sysCalls[rdi](rsi, rdx, rcx, r8, stackFrame);
	else returnValue = sys_not_implemented();
	updateProcessStackRegister(stackFrame, returnValue, REGISTER_RAX);
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

/*
 * https://jameshfisher.com/2018/02/19/how-to-syscall-in-c/
 * fd = 0 (stdin)
 */
uint64_t sys_read(uint64_t fd, char *buffer, uint64_t size){
	uint64_t i = 0;
	char c;
	if (fd == 0){
		while(size > 0 && (c = get_key_input())) {	    //get_key_input devuelvo 0 si el buffer esta vacio
			buffer[i++] = c;
			size--;
		}
	}
	return i;
}

//fd = 1 (stdout)
uint64_t sys_write(uint64_t fd, char *buffer, uint64_t size){
	uint64_t i = 0;

	if (fd == 1) {
		while(size--) {
			char c = *buffer;
			if (c == '\n') {
				newLine();
			} else if (c == '\b') {
				backspace();
			} else {
				printChar(c,0,255,0);
			}
			buffer++;
			i++;
		}
	}

	return i;
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

void *sys_new_process(char * name, int(* foo)(int argc, char** argv), int argc, char * argv[]){
	return newProcess(name, foo, getProcessPPid(getCurrentProcess()), argc, argv, S_P_LOW, S_M_FOREGROUND);
}

void sys_free_process(pid_t pid, t_stack stackFrame){
	killProcess(pid, stackFrame);
}

pid_t sys_get_pid(){
	return getProcessPid(getCurrentProcess());
}

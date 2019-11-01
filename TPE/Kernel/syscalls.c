#include <stdint.h>
#include "include/keyboard-Driver.h"
#include "include/videoDriver.h"
#include "time.h"
#include "include/memManager.h"
#include "include/processHandler.h"
#include "include/interrupts.h"

typedef uint64_t(*systemCall)();

int sys_ticks(int * ticks);
int sys_ticksPerSecond(int * ticks);
int sys_clear();
int sys_read(uint64_t fd, char *buffer, uint64_t size);
int sys_write(uint64_t fd, char *buffer, uint64_t size);
int sys_draw(uint64_t x, uint64_t y, unsigned char r, unsigned char g, unsigned char b);
int * sys_time(uint64_t * time);
uint64_t sys_usedMem();
uint64_t sys_freeMem(void);
void * sys_malloc(uint64_t size, uint64_t pid);
void sys_free(void * address, uint64_t pid);
void * sys_newProcess(char * name, int(* foo)(int argc, char** argv), int ppid, int argc, char * argv[], void * returnPosition);
void sys_freeProcess(void * process);
int sys_getPid(void * process);
int sys_exec(void * process);

systemCall sysCalls[] = { 0, 0, 0,
        (systemCall) sys_read,
		(systemCall) sys_write,
        (systemCall) sys_clear,
		(systemCall) sys_draw,
		(systemCall) sys_time,
		(systemCall) sys_exec,
		(systemCall) sys_getPid,
		(systemCall) sys_newProcess,
		(systemCall) sys_freeProcess,
		(systemCall) sys_free,
		(systemCall) sys_ticks,
		(systemCall) sys_ticksPerSecond,
		(systemCall) sys_usedMem,
		(systemCall) sys_freeMem,
		(systemCall) sys_malloc,
};

int syscallHandler(unsigned long rdi, unsigned long rsi, unsigned long rdx, unsigned long rcx, unsigned long r8, unsigned long r9, unsigned long r10){
	return sysCalls[rdi](rsi, rdx, rcx, r8, r9, r10);
}

int sys_ticks(int * ticks) {
	*ticks = ticks_elapsed();
	return *ticks;
}

int sys_ticksPerSecond(int * ticks) {
	*ticks = seconds_elapsed();
	return *ticks;
}

int sys_clear() {
	clearAll();
}

/*
 * https://jameshfisher.com/2018/02/19/how-to-syscall-in-c/
 * fd = 0 (stdin)
 */
int sys_read(uint64_t fd, char *buffer, uint64_t size){
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
int sys_write(uint64_t fd, char *buffer, uint64_t size){
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


int sys_draw(uint64_t x, uint64_t y, unsigned char r, unsigned char g, unsigned char b) {
	putPixel(x,y,r,g,b);
}

int * sys_time(uint64_t * time) {
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

uint64_t sys_freeMem(void){
	return freeMemoryLeft();
}

void * sys_malloc(uint64_t size, uint64_t pid){
	return pmalloc(size, pid);
}
void sys_free(void * address, uint64_t pid){
	pfree(address, pid);
}

void * sys_newProcess(char * name, int(* foo)(int argc, char** argv), int ppid, int argc, char * argv[], void * returnPosition){
	return newProcess(name, foo, ppid, argc, argv, returnPosition);
}

void sys_freeProcess(void * process){
	free(process);
}

int sys_getPid(void * process){
	return getPid(process);
}

int sys_exec(void * process){
	return exec(process);
}





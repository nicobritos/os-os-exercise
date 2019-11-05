//This is a personal academic project. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "stdio.h"
//#include "syscalls.h"
#include "newSyscalls.h"
#include "exceptions.h"

void invalidOpCode();
void div0exc();


void clearScreen(){
	sys_clear();
    /*os_clear();          os_clear() definida en syscalls.asm --> entra en interrupts.asm (kernel -> asm -> interrupts.asm) -->
                                sys_clear() (syscalls.c) --> clear()  */
}


void time(){
	int currTime[6];
	sys_time(currTime);

	char time[9];					//pass the array to a string to print
	time[0] = currTime[0] + '0';
	time[1] = currTime[1] + '0';
	time[2] = ':';
	time[3] = currTime[2] + '0';
	time[4] = currTime[3] + '0';
	time[5] = ':';
	time[6] = currTime[4] + '0';
	time[7] = currTime[5] + '0';
	time[8] = 0;

	printf("\n%s", time);
}

void divisionExc(){
	div0exc();
}
void invalidOpCodeException() {
	invalidOpCode();
}

uint64_t usedMem(){
	return sys_usedMem();
}

uint64_t freeMem(){
	return sys_freeMem();
}
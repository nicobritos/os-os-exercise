#include "stdio.h"
#include "includes/syscalls.h"


void printHelp() {
    printf("\nhelp - display available commands \n");
    printf("snake\n");
    printf("getTime - Prints the current time in Argentina \n");
    printf("echo (message) - Prints out the message \n");
    printf("zero - Makes a divition by cero exception \n");
    printf("invalidOpCode - Makes a invalid operation exception \n");
    printf("clear - Clears the screen \n");
	printf("mem - Prints the memory state\n");
    printf("exit - Exits the terminal");
}


void clearScreen(){
    os_clear();         /* os_clear() definida en syscalls.asm --> entra en interrupts.asm (kernel -> asm -> interrupts.asm) -->
                                sys_clear() (syscalls.c) --> clear()  */
}


void time(){
	uint64_t * currTime = os_time();		//returns an array with the current hour, minutes, and seconds

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

	printf(time);
}

int division(int n){
  return 666/n;
}
void divisionExc(){
  division(0);
}
void invalidOpCodeException() {
	invalidOpCode();
}

uint64_t usedMem(){
	return os_used_mem();
}

uint64_t freeMem(){
	return os_free_mem();
}
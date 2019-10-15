#include <stdint.h>
#include "include/keyboard-Driver.h"
#include "include/videoDriver.h"
#include "time.h"

		/* PROTOTIPOS */
int sys_total_ticks(int * ticks);
int sys_ticks_per_second(int * ticks);
void sys_clear();
uint64_t sys_read(uint64_t fd, char *buffer, uint64_t size);
uint64_t sys_write(uint64_t fd, char *buffer, uint64_t size);
void sys_pixel(uint64_t x, uint64_t y, unsigned char r, unsigned char g, unsigned char b);
uint64_t * sys_time(uint64_t * time);




int sys_total_ticks(int * ticks) {
	*ticks = ticks_elapsed();
	return *ticks;
}

int sys_ticks_per_second(int * ticks) {
	*ticks = seconds_elapsed();
	return *ticks;
}

void sys_clear() {
	clearAll();
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


void sys_pixel(uint64_t x, uint64_t y, unsigned char r, unsigned char g, unsigned char b) {
	putPixel(x,y,r,g,b);
}

uint64_t * sys_time(uint64_t * time) {
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



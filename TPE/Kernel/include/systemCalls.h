#ifndef SYSTEMCALLS_H
#define SYSTEMCALLS_H

#include <stdint.h>

int sys_total_ticks(int * ticks);
int sys_ticks_per_second(int * ticks);
void sys_clear();
uint64_t sys_read(uint64_t fd, char *buffer, uint64_t size);
uint64_t sys_write(uint64_t fd, char *buffer, uint64_t size);
void sys_pixel(uint64_t x, uint64_t y, unsigned char r, unsigned char g, unsigned char b);
uint64_t * sys_time(uint64_t * time); 


#endif /* SYSTEMCALLS_H */
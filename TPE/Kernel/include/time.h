#ifndef _TIME_H_
#define _TIME_H_

#include <inttypes.h>

void timer_handler();
int ticks_elapsed();
int seconds_elapsed();
uint64_t getHour();
uint64_t getMin();
uint64_t getSec();

#endif

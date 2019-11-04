#ifndef _TIME_H_
#define _TIME_H_

#include <inttypes.h>

void timer_handler();
uint64_t ticks_elapsed();
uint64_t seconds_elapsed();
uint64_t getHour();
uint64_t getMin();
uint64_t getSec();
uint64_t msToTicks(uint64_t ms);

#endif

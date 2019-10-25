#ifndef _TIME_H_
#define _TIME_H_

#include "process.h"

void timer_handler(t_stack *currentProcessStack);
uint64_t ticks_elapsed();
uint64_t seconds_elapsed();

#endif

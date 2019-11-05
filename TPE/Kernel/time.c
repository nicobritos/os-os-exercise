//This is a personal academic project. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include <time.h>

#define TICK_MS 55.0
#define TICK_SECONDS 18.1818181818 

static uint64_t ticks = 0;

void timer_handler() {
	ticks++;
}

uint64_t ticks_elapsed() {
	return ticks;
}

uint64_t seconds_elapsed() {
	return (uint64_t)(ticks / TICK_SECONDS);
}

uint64_t msToTicks(uint64_t ms) {
	return (uint64_t) (ms / TICK_MS);
}

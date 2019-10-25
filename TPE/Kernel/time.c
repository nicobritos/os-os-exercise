#include <time.h>
#include <scheduler.h>
#include <process.h>

static uint64_t ticks = 0;

void timer_handler(t_stack *currentProcessStack) {
	ticks++;
	runScheduler(currentProcessStack);
}

uint64_t ticks_elapsed() {
	return ticks;
}

uint64_t seconds_elapsed() {
	return ticks / 18;
}

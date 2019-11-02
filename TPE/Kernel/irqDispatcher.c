#include <time.h>
#include <stdint.h>
#include "keyboard-Driver.h"
#include <process.h>
#include "scheduler.h"

static void int_20();
static void int_21();

void irqDispatcher(uint64_t irq, t_stack currentProcessStack) {
	switch (irq) {
		case 0:
			int_20();
			runScheduler(currentProcessStack);
			break;
		case 1:
			int_21();
			break;
	}
	return;
}

void int_20() {
	timer_handler();
}

void int_21(){
	keyboard_controller();
}

#include <time.h>
#include <stdint.h>
#include "keyboard-Driver.h"
#include <process.h>

static void int_20();
static void int_21();

void irqDispatcher(uint64_t irq, t_stack *currentProcessStack) {
	switch (irq) {
		case 0:
			int_20(currentProcessStack);
			break;
		case 1:
			int_21();
			break;
	}
	return;
}

void int_20(t_stack *currentProcessStack) {
	timer_handler(currentProcessStack);
}

void int_21(){
	keyboard_controller();
}

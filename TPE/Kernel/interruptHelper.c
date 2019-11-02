#include "interruptHelper.h"
#include <stdlib.h>

static uint64_t cliQueue = 0; // If 0 then interrupts should be enabled.

void _cli();
void _sti();

void pushcli() {
	if (cliQueue == 0)
		_cli();

	cliQueue++;
}

void pushsti() {
	if (cliQueue > 0) {
		cliQueue--;
		if (cliQueue == 0)
			_sti(); // Should be run at the end to avoid entering an interruption
	}
}

//This is a personal academic project. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "videoDriver.h"
#include <stdint.h>
#include "naiveConsole.h"
#include "process.h"

#define ZERO_EXCEPTION_ID 0
#define INVALIDOPCODE_EXCEPTION_ID 1

static void zero_division(t_stack stackPointer);
static void invalid_opcode(t_stack stackPointer);

void _killProcessSyscallKernel();

void exceptionDispatcher(uint64_t exception, t_stack stackPointer) {
	switch(exception){
		case ZERO_EXCEPTION_ID:
			zero_division(stackPointer);
		break;
		case INVALIDOPCODE_EXCEPTION_ID:
			invalid_opcode(stackPointer);
		break;
	}
	updateProcessStackRegister(stackPointer, REGISTER_RIP, (uint64_t) _killProcessSyscallKernel);
}

static void zero_division(t_stack stackPointer) {
	newLine();
	
	printExceptions("ERROR: DIVISION POR CERO");
	printStackFrame(stackPointer);
}

static void invalid_opcode(t_stack stackPointer){
	newLine();

	printExceptions("ERROR: CODIGO DE OPERACION INVALIDO\n");
	printStackFrame(stackPointer);
}

#include "videoDriver.h"
#include <stdint.h>
#include "naiveConsole.h"
#include "process.h"

#define ZERO_EXCEPTION_ID 0
#define INVALIDOPCODE_EXCEPTION_ID 1

static void zero_division(t_stack stackPointer);
static void invalid_opcode(t_stack stackPointer);

void exceptionDispatcher(uint64_t exception, t_stack stackPointer) {
	switch(exception){
		case ZERO_EXCEPTION_ID:
			zero_division(stackPointer);
			//como hice pushstate antes de llamar a la handler, tengo todos los registros
			//a partir de donde empieza el stackPointer
		break;
		case INVALIDOPCODE_EXCEPTION_ID:
			invalid_opcode(stackPointer);
		break;
	}

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

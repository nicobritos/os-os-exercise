#include <stdint.h>
#include <string.h>
#include <lib.h>
#include <moduleLoader.h>
#include <naiveConsole.h>
#include "idtLoader.h"
#include "videoDriver.h"
#include "memManager.h"
#include "processHandler.h"


extern uint8_t text;
extern uint8_t rodata;
extern uint8_t data;
extern uint8_t bss;
extern uint8_t endOfKernelBinary;
extern uint8_t endOfKernel;

static const uint64_t PageSize = 0x1000;

static void * const sampleCodeModuleAddress = (void*)0x400000;
static void * const sampleDataModuleAddress = (void*)0x500000;

typedef int (*EntryPoint)();


void clearBSS(void * bssAddress, uint64_t bssSize)
{
	memset(bssAddress, 0, bssSize);
}

void * getStackBase()
{
	return (void*)(
		(uint64_t)&endOfKernel
		+ PageSize * 16				//The size of the stack itself, 32KiB
		- sizeof(uint64_t)			//Begin at the top of the stack
	);
}

void * initializeKernelBinary(){	
	void * moduleAddresses[] = {
		sampleCodeModuleAddress,
		sampleDataModuleAddress
	};

	loadModules(&endOfKernelBinary, moduleAddresses);

	clearBSS(&bss, &endOfKernel - &bss);

	return getStackBase();
}

void hola(char *s) {
	while(1) {
		printf("A");
	}
}


void chau(char *s) {
	while(1) {
		printf("B");
	}
}

void *enterUserSpace(int argc, void **argv) {
	printf("asdas\n");
	((EntryPoint)sampleCodeModuleAddress)();
}

int main(){	
	_cli();
	initializeMemoryManager();
	initializeScheduler();
	load_idt();

	char *argsA = {"A"};
	char *argsB = {"B"};
	// newProcess("hola", &enterUserSpace, SYSTEM_PID, 0, NULL);
	// newProcess("hola", &enterUserSpace, SYSTEM_PID, 0, NULL);
	// newProcess("chau", sampleCodeModuleAddress, SYSTEM_PID, 0, NULL);
	// newProcess("hola", hola, SYSTEM_PID, 1, argsA);
	// newProcess("chau", chau, SYSTEM_PID, 1, argsB);
	newProcess("hola", hola, SYSTEM_PID, 0, NULL);
	newProcess("chau", chau, SYSTEM_PID, 0, NULL);
	_sti();
	idleKernel();
	return 0;
}


void reboot(){
	main();
}
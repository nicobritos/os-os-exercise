#include "include/keyboard-Driver.h"
#include "include/videoDriver.h"
#include "fileManager.h"
#include "list.h"

// static listADT 

uint64_t readFile(uint64_t fd, char *buffer, uint64_t size) {
	uint64_t i = 0;
	char c;
	if (fd == 0){
		while(size > 0 && (c = get_key_input())) {	    //get_key_input devuelvo 0 si el buffer esta vacio
			buffer[i++] = c;
			size--;
		}
	}
	return i;
}

uint64_t writeFile(uint64_t fd, char *buffer, uint64_t size) {
	uint64_t i = 0;

	if (fd == 1) {
		while(size--) {
			char c = *buffer;
			if (c == '\n') {
				newLine();
			} else if (c == '\b') {
				backspace();
			} else {
				printChar(c,0,255,0);
			}
			buffer++;
			i++;
		}
	}

	return i;
}

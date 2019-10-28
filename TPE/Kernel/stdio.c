#include "stdlib.h"
#include "string.h"
#include "videoDriver.h"
#include <stdarg.h> 			/* incluyo esta libreria para usar va_list va_arg va_start en printf y scanf */


void printChars(const char* s, uint64_t length) {
	while (*s && length) {
		printChar(*s, 255, 255, 255);
		s++;
		length--;
	}
}

void putchar(char letter){
	printChars(&letter, 1);     		/* write -- recibe char * y la longitud (siempre 1) */
}

void printf(const char* format, ...) {
	va_list args; 					/* Lista de argumentos los cuales no se la cantidad */
	va_start(args, format); 		/* La lista de argumentos comienza luego del formato */

	const char *index = format;
	char buffer[200];
	char *str;
	int length, num;
	long long unsigned llunum;

	while(*(index) != 0){
								/* No hay mas argumentos */
		if(*(index) == '%'){						/* Si es % es que luego viene el tipo de dato a imprimir */
			switch(*(index+1)){
				case 'd':
					num = (int) va_arg(args, int);   /* Guarda en num el siguiente argumento 'int' */
					length = itoa(num, buffer, 10);  /* Convierte el int guardado en num en string, (el 10 es la base de num) y guarda en length la longitud */
					printChars(buffer, length);	
					index++;
					break;

				case 'c':
					putchar((char) va_arg(args, int));
					index++;
					break;

				case 's': 
					str = (char*) va_arg(args, char*); 		/* Guarda en str el siguiente argumento 'char *' */
					printChars(str, strlen(str));
					index++;
					break;

				case 'x':
					num = (int) va_arg(args, int);
					length = itoa(num, buffer, 16);
					printChars(buffer, length);
					index ++;
					break;
				case 'l':
					llunum = (long long unsigned) va_arg(args, long long unsigned);
					length = itoa(llunum, buffer, 10);
					printChars(buffer, length);
					index++;
					break;
					

			}
		}else{
			putchar(*(index));
		}
		
		index++;
	}
}

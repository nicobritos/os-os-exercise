#include "includes/stdlib.h"
#include <stdarg.h> 			/* incluyo esta libreria para usar va_list va_arg va_start en printf y scanf */
#include "includes/syscalls.h"

int printf(const char* format, ...);

void putchar(char letter){
	write(1,&letter, 1);     		/* write -- recibe char * y la longitud (siempre 1) */
}

char getchar(){
	char letter = 0;
	while(1){
		read(0,&letter, 1); 	/* read -- recibe char * y la longitud (siempre 1) */
		if(letter == -1 || (letter > 0 && letter < 128 )){
			return letter;
		}
	}
}

char getCharWithZero() {
	char c = 0;
	while(1) {
		read(0, &c, 1);	
		if (c >= -1 && c < 128) {
			return c;
		}
	}
}


int printf(const char* format, ...){
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
					write(1,buffer, length);	
					index++;
					break;

				case 'c':
					putchar((char) va_arg(args, int));
					index++;
					break;

				case 's': 
					str = (char*) va_arg(args, char*); 		/* Guarda en str el siguiente argumento 'char *' */
					write(1,str, strlen(str));
					index++;
					break;

				case 'x':
					num = (int) va_arg(args, int);
					length = itoa(num, buffer, 16);
					write(1,buffer, length);
					index ++;
					break;
				case 'l':
					llunum = (long long unsigned) va_arg(args, long long unsigned);
					length = itoa(llunum, buffer, 10);
					write(1, buffer, length);
					index++;
					break;
					

			}
		}else{
			putchar(*(index));
		}
		
		index++;
	}
	
	return 0;
}


// void readline(char* buff){ 							/* La uso en scanf */
// 	int j;
// 	for(j=0; (buff[j-1] != '\n') ; j++){
// 		do{
// 			buff[j] = getchar();
// 			printf("%c", buff[j]);
// 			if(buffer[j] == '\b'){
// 				buff[j] = 0;
// 				buff[j-1] = 0;
// 				j -= 2;
// 			}

// 		} while(buff[j] == -1);
// 	}
// }


int scanf(char* string, int bytes){
	char c;
	int i = 0;
	while ((c = getchar()) != '\n' && i < bytes - 1) {
		if (c == '\b') {
			if (i > 0) {
				putchar(c);
				i--;
			}
		} else {
			putchar(c);
			string[i++] = c;
		}
	}

	string[i] = 0; //To mark the end of the string
}



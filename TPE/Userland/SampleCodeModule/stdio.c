//This is a personal academic project. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "stdlib.h"
#include <stdarg.h> 			/* incluyo esta libreria para usar va_list va_arg va_start en printf y scanf */
#include "newSyscalls.h"

int printf(const char* format, ...);

void putchar(char letter){
	if(letter == -1){
		char * ctrld = "^D";
		sys_write(1, ctrld, 2);
	}
	else if(letter == 0x03){
		char * ctrlc = "^C";
		sys_write(1, ctrlc, 2);
	}
	else{
		sys_write(1,&letter, 1);     		/* write -- recibe char * y la longitud (siempre 1) */
	}
}

int getchar(){
	char letter = 0;
	while(1){
		sys_read(0,&letter, 1); 	/* read -- recibe char * y la longitud (siempre 1) */
		if(letter == -1 || (letter > 0)){
			return letter;
		}
	}
}

char getCharWithZero() {
	char c = 0;
	while(1) {
		sys_read(0, &c, 1);	
		if (c >= -1) {
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
					sys_write(1,buffer, length);	
					index++;
					break;

				case 'c':
					putchar((char) va_arg(args, int));
					index++;
					break;

				case 's': 
					str = (char*) va_arg(args, char*); 		/* Guarda en str el siguiente argumento 'char *' */
					sys_write(1,str, strlen(str));
					index++;
					break;

				case 'x':
					num = (int) va_arg(args, int);
					length = itoa(num, buffer, 16);
					sys_write(1,buffer, length);
					index ++;
					break;
				case 'l':
					llunum = (long long unsigned) va_arg(args, long long unsigned);
					length = itoa(llunum, buffer, 10);
					sys_write(1, buffer, length);
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


int scanf(char* string, int bytes, int separator){
	int c;
	int i = 0;
	while (((c = getchar()) != separator) && (i < bytes - 1)) {
		if (c == '\b') {
			if (i > 0) {
				if(string[i-1]== -1 || string[i-1]== 0x03)
				putchar(c);
				putchar(c);
				i--;
			}
		} else {
			putchar(c);
			string[i++] = c;
		}
	}
	string[i] = 0; //To mark the end of the string
	return i;
}



#include <stdint.h>


/* 
 * Calcula la longitud del string
 */

/* 
 * Convierte de int a string y devuelve la longitud 
 */
uint64_t itoa(uint64_t value, char* buffer, int base){			
	
	char *p = buffer;
	char *p1;
	char *p2;
	int digits = 0;

	if(value < 0 && base == 10){
		value =- value;
		*p = '-';
		digits++;
	}

	//Calculate characters for each digit
	do{
		int remainder = value % base;
		*p++ = (remainder < 10) ? remainder + '0' : remainder + 'A' - 10;
		digits++;
	
	} while (value /= base);


	*p = 0;  			/* Cero de fin de string */

	//Reverse string in buffer.
	if (*buffer == '-'){
		p1 = buffer + 1;
	}else{
		p1 = buffer;
	}

	p2 = p - 1;
	while (p1 < p2)
	{
		char tmp = *p1;
		*p1 = *p2;
		*p2 = tmp;
		p1++;
		p2--;
	}

	return digits;
}

/*
 * Convierte  string a int 
 */
int atoi(char c){ 		
	int a = 0;
	if(c >= '0' && c >= '9'){
		a =(int) (c - '0');
		return a;
	}
	return -1;		//si retorno -1 es que el argumento pasado no era un numero.
}


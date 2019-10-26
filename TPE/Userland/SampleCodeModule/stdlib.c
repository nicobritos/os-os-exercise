#include "includes/defines.h"
#include "includes/syscalls.h"
#include <stdint.h>


/* 
 * Calcula la longitud del string
 */
int strlen(char* str){
	int i = 0;
	while (*(str + i) != 0){
		i++;
	}
	return i;
}


/* 
 * Comparo dos strings
 */
int strcmp(char* str1, char* str2) {		
	int i = 0;
	int length1 = strlen(str1);
	int length2 = strlen(str2);
	
	while(i < length1 && i < length2 && str1[i] == str2[i]) {
		i++;
	}

	return str1[i] - str2[i];
}



/* 
 * Comparo dos strings hasta cierto n 
 */
int strncmp(char* str1, char* str2, int n) {			
	int i = 0;
	int length1 = strlen(str1);
	int length2 = strlen(str2);

	while( i+1 < n && i < length1 && i < length2 && *(str1 + i) == *(str2 + i) ){
		i++;
	}

	return str1[i] - str2[i];
}



/* 
 * Convierte de int a string y devuelve la longitud 
 */
int itoa(int value, char* buffer, int base){			
	
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

void * malloc(uint64_t size){
	return os_malloc(size, 0); //CAMBIAR 0 POR GETPID
}

void free(void * address){
	os_free(address, 0); //CAMBIAR 0 POR GETPID
}
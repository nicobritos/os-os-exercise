#include "defines.h"
#include "newSyscalls.h"
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
int atoi(char * s){ 		
	int i = 0;
	int num = 0;
	while(s[i]){
		if(s[i] >= '0' && s[i] <= '9'){
			num *= 10;
			num += s[i] - '0';
			i++;
		}
		else{
			return -1;
		}
	}
	return num;
}

int atox(char * s){
	int i = 0;
	int num = 0;
	while(s[i]){
		if(s[i] >= '0' && s[i] <= '9'){
			num *= 16;
			num += s[i] - '0';
			i++;
		}
		else if(s[i] >= 'a' && s[i] <= 'f'){
			num *= 16;
			num += s[i] - 'a' + 10;
			i++;
		}
		else{
			return -1;
		}
	}
	return num;
}

void * malloc(uint64_t size){
	return sys_malloc(size);
}

void free(void * address){
	sys_free(address);
}

unsigned int lineCount(char * input){
	unsigned int count = 1;
	unsigned int i = 0;
	while(input[i] != 0){
		if(input[i] == '\n')
			count++;
		i++;
	}
	return count;
}

char * filterVowels(char * buffer, char * input){
	unsigned int i = 0;
	unsigned int bufferI = 0;
	while((input[i] != 0) && (i<200)){
		if((input[i] != 'a') && (input[i] != 'e') && (input[i] != 'i') && (input[i] != 'o') && (input[i] != 'u') && (input[i] != 'A') && (input[i] != 'E') && (input[i] != 'I') && (input[i] != 'O') && (input[i] != 'U') ){
			buffer[bufferI] = input[i];
			bufferI++;
		}
		i++;
	}
	buffer[bufferI] = 0;
	return buffer;
}

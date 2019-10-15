#ifndef VIDEODRIVER_H_
#define VIDEODRIVER_H_

#include <stdint.h>
void putPixel(uint64_t x,uint64_t y, unsigned char r, unsigned char g, unsigned char b);

void clearAll();
void clearFromCoords(int x, int y);

void newLine();

void fillRect(unsigned char x, unsigned char y, uint16_t width, uint16_t height, unsigned char r, unsigned char g, unsigned char b);

void printChar(unsigned char myChar, unsigned char r, unsigned char g, unsigned char b);

void printString(char *str, unsigned char r, unsigned char g, unsigned char b);

void printExceptions(char * str);

void printHexa(uint64_t value);

void backspace();

#endif /*.VIDEODRIVER_H_ */

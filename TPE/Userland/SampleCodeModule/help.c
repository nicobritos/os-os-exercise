#include "apps.h"
#include "stdio.h"

int help(int argc, char **argv) {
    printf("\nhelp - display available commands \n");
    printf("snake\n");
    printf("getTime - Prints the current time in Argentina \n");
    printf("cat (message) - Prints out the message \n");
    printf("zero - Makes a divition by cero exception \n");
    printf("invalidOpCode - Makes a invalid operation exception \n");
    printf("clear - Clears the screen \n");
	printf("mem - Prints the memory state\n");
	printf("wc - Print the number of lines\n");
	printf("filter (message) - Filters the vowels from the message\n");
    printf("exit - Exits the terminal");
    return 1;
}

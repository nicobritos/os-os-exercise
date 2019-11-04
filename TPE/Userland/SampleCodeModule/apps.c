#include "apps.h"
#include "stdio.h"
#include "unistd.h"
#include "stdlib.h"
#include "process.h"


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

int kill(int argc, char **argv){
    printf("\n");
    pid_t pid = atoi(argv[0]);
    if(pid == -1){
        printf("Please enter a number");
        return 0;
        }
    else{
        killProcess(pid);
        printf("Process killed\n");
    }
    return 1;
}
int nice(int argc, char ** input){
    printf("\n");
    char ** argv = malloc(100 * sizeof(char*));
    uint64_t cant_argc = tokenArgs(argv, input[0], 100);
    if (cant_argc == (uint64_t)argc)
    {
        t_priority priority;
        pid_t pid = atoi(argv[0]);
        if(pid == -1){
            printf("Please enter a number\n");
            return 0;
            }
        else{
            if(strcmp(argv[1], "high") == 0) {
                priority = S_P_HIGH;
                //printf("high\n");

            }
            else if(strcmp(argv[1], "low") == 0){
                priority = S_P_LOW;
                //printf("low\n");
            }
            else{
                printf("Please enter a valid priority\n");
                return 0;
            }
        }
        setProcessPriority(pid,priority);
        printf("Priority set\n");
        return 1;
    }
    else
    {
        printf("Missing arguments\n");
        return 0;
    }
    
    
    
}
int block(int argc, char **argv){
    printf("\n");
    pid_t pid = atoi(argv[0]);

    if(pid == -1){
        printf("Please enter a number");
        return 0;
        }
    else{
        int state = (int)toogleProcessLock(pid);
        if (state == 1)
        {
            printf("Process Ready\n");
        }
        else if( state == 3)
        {
            printf("Process Locked\n");
        }
        else
        {
            printf("Proceso no lockeado ni listo");
        }
    }
    return 1;
}

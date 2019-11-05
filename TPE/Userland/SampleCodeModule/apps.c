//This is a personal academic project. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "apps.h"
#include "stdio.h"
#include "unistd.h"
#include "stdlib.h"
#include "process.h"
#include "commands.h"
#include "newSyscalls.h"


int help(int argc, char **argv) {
    printf("\nhelp - display available commands \n");
	printf("mem - Prints the memory state\n");
    printf("ps - Prints all the running processes basic information\n");
    printf("loop - Prints a salute and his pid every 5 seconds\n");
    printf("kill (pid) - Kills the process with the pid received\n");
    printf("nice (pid) (priority) - Set the process with the matching pid with the corresponding priority (\"high\" or \"low\")\n");
    printf("block (pid) - Blocks the process with the matching pid\n");
    printf("cat (message) - Prints out the message \n");
	printf("wc - Print the number of lines\n");
	printf("filter (message) - Filters the vowels from the message\n");
    printf("phylo - Simulates the philosopher's problem\n");
    printf("sem - Prints the current open semaphores and basic information\n");
    printf("clear - Clears the screen \n");
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
            printf("Please enter a number (for the pid)\n");
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
                printf("Please enter a valid priority (\"high\" or \"low\")\n");
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


int mem(int argc, char ** argv){
    printf("\n%l / %l bytes utilizados", usedMem(), usedMem() + freeMem());
    return 1;
}

int ps(int argc, char ** argv){
    sys_printProcesses();
    return 1;
}

int loop(int argc, char **argv){
    while(1){
        printf("\nHola soy %l", sys_getPid());
        sleep(5000);
    }   
    return 1;
}

int cat(int argc, char **argv){
    printf("\n%s", argv[0]);
    return 1;
}

int wc(int argc, char **argv){
    printf("\n");
    char buffer[1000];
    int separator = -1;
    scanf(buffer, 1000, separator);
    printf("\n%d", lineCount(buffer));
    return 1;
}

int filter(int argc, char **argv){
    char * s = argv[0];
    char * dest = malloc(strlen(s));
	filterVowels(dest, s);
    printf("\n");
    printf(dest);
    free(dest);
	return 1;
}

int clear(int argc, char** argv){
    clearScreen();
    return 1;
}

int sem(int argc, char** argv){
    sys_printSems();
    return 1;
}
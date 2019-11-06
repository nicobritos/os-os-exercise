//This is a personal academic project. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "apps.h"
#include "stdio.h"
#include "unistd.h"
#include "stdlib.h"
#include "newSyscalls.h"
#include "commands.h"
#include "defines.h"
#include "process.h"


int help(int argc, char **argv) {
    printf("help - display available commands \n");
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
    sleep(3000);
    return 1;
}

int kill(int argc, char **argv){
    pid_t pid = atoi(argv[0]);
    if(pid == -1 || argv[0] == '\0'){
        printf("Please enter a valid PID\n");
        return 0;
    } else {
        if (killProcess(pid))
            printf("Process killed\n");
        else
            printf("Error killing process (invalid PID?)\n");
    }
    return 1;
}
int nice(int argc, char ** input){
    char ** argv = malloc(100 * sizeof(char*));
    if(argv == NULL)
        return 0;
    char output[100];
    uint64_t cant_argc = tokenArgs(argv, output, input[0], 100);
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
    pid_t pid = atoi(argv[0]);

    if(pid == -1){
        printf("Please enter a number\n");
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
            printf("Proceso no lockeado ni listo\n");
        }
    }
    return 1;
}


int mem(int argc, char ** argv){
    printf("%llu / %llu bytes utilizados\n", usedMem(), usedMem() + freeMem());
    return 1;
}

int ps(int argc, char ** argv){
    sys_printProcesses();
    return 1;
}

int loop(int argc, char **argv){
    while(1){
        printf("Hola soy PID: %lld\n", sys_getPid());
        sleep(5000);
    }   
    return 1;
}

int cat(int argc, char **argv){
    printf("%s", argv[0]);
    return 1;
}

int wc(int argc, char **argv){
    char buffer[1000];
    int separator = -1;
    scanf(buffer, 1000, separator);
    printf("\n%u\n", lineCount(buffer));
    return 1;
}

int filter(int argc, char **argv){
    char * s = argv[0];
    int size = strlen(s) + 1;
    char * dest = malloc(size);
	filterVowels(dest, s, size);
    if(dest == NULL) return 0;
    printf("\n%s", dest);
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
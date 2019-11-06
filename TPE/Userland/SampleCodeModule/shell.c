//This is a personal academic project. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "stdlib.h"
#include "stdio.h"
#include "include/unistd.h"
#include "exceptions.h"
#include "commands.h"
#include "snake.h"
#include "defines.h"
#include "apps.h"
#include "phylo.h"
#include "process.h"

#define MAX_ARGS 10

// int parse(char *input, t_mode mode);
int parse(char *input);
void parseWithPipe(char *p1, char *p2);
// void parseCommands(char *buffer);

void shell(){
    char *buffer = malloc(BUFFER_LENGTH);

    while (1) {
        printf("User $> ");
        scanf(buffer, BUFFER_LENGTH - 1, '\n');
        printf("\n");
        // parseCommands(buffer);
        // parse(buffer, S_M_FOREGROUND);
        parse(buffer);
    }
    free(buffer);
    printf("\nGoodbye");
    return;
}

// void parseCommands(char *buffer) {
//     char *start = buffer = trim(buffer);
//     char *firstWord = NULL, *secondWord = NULL;

//     while (*buffer) {
//         if (*buffer == '|') {
//             if (firstWord == NULL) {
//                 firstWord = start;
//                 start = buffer + 1;
//             } else {
//                 secondWord = start;
//                 parseWithPipe(firstWord, secondWord);
//                 return;
//             }
//         }
//         buffer++;
//     }

//     t_mode mode = *(buffer - 1) == '&' ? S_M_BACKGROUND : S_M_FOREGROUND;
//     if (mode == S_M_BACKGROUND) {
//         *(buffer - 1) = '\0';
//     }
//     parse(start, mode);
// }

void parseWithPipe(char *p1, char *p2) {

}

// int parse(char* input, t_mode mode) {
int parse(char* input) {
    char * argv[MAX_ARGS] = {0};
    pid_t pid = 0;

    t_mode mode = S_M_INVALID;
    if (strcmp(input, "help") == 0) {
        pid = newProcess("help", help, mode = S_M_FOREGROUND);
    } else if (strcmp(input, "mem") == 0) {
        pid = newProcess("mem", mem, mode = S_M_FOREGROUND);
    } else if (strcmp(input, "ps") == 0) {
        pid = newProcess("ps", ps, mode = S_M_FOREGROUND);
    } else if (strcmp(input, "loop") == 0) {
        pid = newProcess("loop", loop, mode = S_M_BACKGROUND);
    } else if (strncmp(input, "kill ", 5) == 0) {
        char * argv[MAX_ARGS] = {0};
        argv[0] = input+5;
        // pid = newProcessArgs("kill", kill,1, argv, mode = S_M_FOREGROUND);
        kill(1, argv);
    } else if (strncmp(input, "nice ", 5) == 0) {
        char * argv[MAX_ARGS] = {0};
        argv[0] = input+5;
        pid = newProcessArgs("nice", nice, 2, argv, mode = S_M_FOREGROUND);
    } else if (strncmp(input, "block ", 6) == 0) {
        char * argv[MAX_ARGS] = {0};
        argv[0] = input+6;
        pid = newProcessArgs("block", block, 1, argv, mode = S_M_FOREGROUND);
    } else if (strncmp(input, "cat ", 4) == 0) {
        argv[0] = input + 4;
        pid = newProcessArgs("cat", cat, 1, argv, mode = S_M_FOREGROUND);
    } else if(strcmp(input, "wc") == 0){
        pid = newProcess("wc", wc, mode = S_M_FOREGROUND);
    } else if(strncmp(input, "filter ", 7) == 0){
        argv[0] = input + 7;
        pid = newProcessArgs("filter", filter, 1, argv, mode = S_M_FOREGROUND);
    } else if (strcmp(input, "sem") == 0) {
        pid = newProcess("sem", sem, mode = S_M_FOREGROUND);
    // } else if (strcmp(input, "pipe") == 0) {
    //     pid = newProcess("pipe", pipe, mode);
    } else if (strcmp(input, "phylo") == 0) {
        argv[0] = (char *)3;
        pid = newProcessArgs("phylo", phyloProblem, 1, argv, mode = S_M_FOREGROUND);
    } else if(strcmp(input, "") == 0){
        return 0;
    } else if(strcmp(input, "clear") == 0) {
        pid = newProcess("clear", clear, mode = S_M_FOREGROUND);
    } else {
        printf("Wrong command\n");
        return 0;
    }

    if (pid == -1) {
        printf("Error creating process\n");
    } else if (mode == S_M_FOREGROUND) {
        waitpid(pid);
    } 
    return 0;
}

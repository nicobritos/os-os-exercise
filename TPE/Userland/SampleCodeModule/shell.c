#include "stdlib.h"
#include "stdio.h"
#include "unistd.h"
#include "exceptions.h"
#include "commands.h"
#include "snake.h"
#include "defines.h"
#include "apps.h"
#include "phylo.h"


#define MAX_ARGS 10

int parse(char *input, t_mode mode);
void parseWithPipe(char *p1, char *p2);
void parseCommands(char *buffer);

void shell(){
    char *buffer = malloc(BUFFER_LENGTH);
    int flag = 0;

    while (!flag) {
        printf("\nUser $> ");
        scanf(buffer, BUFFER_LENGTH - 1, '\n');
        // flag = parseCommands(buffer);
        parseCommands(buffer);
    }

    printf("\nGoodbye");
    return;
}

void parseCommands(char *buffer) {
    char *start = buffer = trim(buffer);
    char *firstWord = NULL, *secondWord = NULL;

    while (*buffer) {
        if (*buffer == '|') {
            if (firstWord == NULL) {
                firstWord = start;
                start = buffer + 1;
            } else {
                secondWord = start;
                parseWithPipe(firstWord, secondWord);
                return;
            }
        }
        buffer++;
    }

    t_mode mode = *(buffer - 1) == '&' ? S_M_BACKGROUND : S_M_FOREGROUND;
    if (mode == S_M_BACKGROUND) {
        *(buffer - 1) = '\0';
    }
    parse(start, mode);
}

void parseWithPipe(char *p1, char *p2) {

}

int parse(char* input, t_mode mode) {
    //char * argv[MAX_ARGS] = {0};
    pid_t pid = 0;

    if (strcmp(input, "help") == 0) {
        pid = newProcess("help", help);
    } else if(strcmp(input, "phylo") == 0){
        argv[0] = 2;
        pid = newProcessArgs("help", phyloProblem, 1, argv, mode);
    } else if(strcmp(input, "s") == 0){
        printf("Hola");
        sleep(2000);
        printf("Chau");
    // } else if (strcmp(input, "mem") == 0) {
    //     pid = newProcess("mem", mem, mode);
    // } else if (strcmp(input, "ps") == 0) {
    //     pid = newProcess("ps", ps, mode);
    // // } else if (strncmp(input, "loop ", 5) == 0) {
    //     // argv[0] = {input + 5};
    //     // pid = newProcessArgs("loop", loop, mode, 1, argv);
    } else if (strncmp(input, "kill ", 5) == 0) {
        char * argv[MAX_ARGS] = {0};
        argv[0] = input+5;
        pid = newProcessArgs("kill", kill,1, argv);
    } else if (strncmp(input, "nice ", 5) == 0) {
        char * argv[MAX_ARGS] = {0};
        argv[0] = input+5;
        pid = newProcessArgs("nice", nice, 2, argv);
    } else if (strncmp(input, "block ", 6) == 0) {
        char * argv[MAX_ARGS] = {0};
        argv[0] = input+6;
        pid = newProcessArgs("block", block, 1, argv);
    // } else if (strncmp(input, "cat ", 4) == 0) {
    //     argv[0] = {input + 4};
    //     pid = newProcessArgs("cat", cat, mode, 1, argv);
    // } else if (strcmp(input, "wc") == 0) {
    //     pid = newProcess("wc", wc, mode);
    // } else if (strcmp(input, "filter") == 0) {
    //     pid = newProcess("filter", filter, mode);
    // } else if (strcmp(input, "sem") == 0) {
    //     pid = newProcess("sem", sem, mode);
    // } else if (strcmp(input, "pipe") == 0) {
    //     pid = newProcess("pipe", pipe, mode);
    // } else if (strcmp(input, "phylo") == 0) {
    //     pid = newProcess("phylo", phylo, mode);
    } else if(strcmp(input, "") == 0){
        return 0;
    } else {
        printf("\nWrong command");
        return 0;
    }







    // if(strncmp(input, "cat ", 4) == 0) {
    // char* phrase = &(input[4]);
    // printf("\n%s", phrase);
    // return 0;
    // } else if(strcmp(input,"snake") == 0){
    // pid_t snakeProcessPid = newProcess("Snake", snake_game);
    // // Set foreground
    // waitpid(snakeProcessPid);
    // return 0;
    // } else if(strcmp(input, "getTime") == 0) {
    // printf("\n");
    // time();
    // return 0;
    // } else if(strcmp(input, "clear") == 0) {
    // clearScreen();
    // printf("\n");
    // return 0;
    // } else if(strcmp(input, "help") == 0) {
    // printHelp();
    // return 0;
    // } else if(strcmp(input, "exit") == 0) {
    // return 1;
    // }
    // else if(strcmp(input, "zero") == 0) {
    // divisionExc();    
    // return 0;
    // } else if(strcmp(input, "invalidOpCode") == 0) {
    // invalidOpCodeException();
    // return 0;
    // }
    // else if(strcmp(input, "mem") == 0){
    // printf("\n%l / %l bytes utilizados", usedMem(), freeMem());
    // return 0;
    // }
    // else if(strcmp(input, "wc") == 0){
    // printf("\n");
    // char buffer[1000];
    // int separator = -1;
    // scanf(buffer, 1000, separator);
    // printf("\n%d", lineCount(buffer));
    // return 0;
    // }
    // else if(strncmp(input, "filter ", 7) == 0){
    // char phrase[1000];
    // printf("\n%s", filterVowels(phrase, &(input[7])));
    // return 0;
    // }
    // // else if(strcmp(input, "new") == 0){
    // //   void * proceso = newProcess("Hola", 0, 0, 0, 0, 0);
    // //   printf("\n%x", proceso);
    // //   return 0;
    // // }
    // else if(strncmp(input, "free ", 5) == 0){
    // char* phrase = &(input[5]);
    // pid_t i = atox(phrase);
    // killProcess(i);
    // return 0;
    // }
    // // else if(strncmp(input, "get ", 4) == 0){
    // //   char* phrase = &(input[4]);
    // //   int i = atox(phrase);
    // //   printf("\n%d", getPid(i));
    // //   return 0;
    // // }
    // else if(strcmp(input, "") == 0){
    // return 0;
    // }



    if (pid > 0) {
        if (mode == S_M_FOREGROUND) {
            setProcessMode(pid, S_M_FOREGROUND);
            waitpid(pid);
        } else {
            setProcessMode(pid, S_M_BACKGROUND);
        }
    }
    return 0;
}

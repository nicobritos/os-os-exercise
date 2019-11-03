#include "includes/defines.h"
#include "includes/stdlib.h"
#include "includes/stdio.h"
#include "includes/unistd.h"
#include "includes/commands.h"
#include "includes/snake.h"
#include "includes/exceptions.h"
#define NULL ((void *) 0)


int parse(char* input){
    if(strncmp(input, "cat ", 4) == 0) {
      char* phrase = &(input[4]);
      printf("\n%s", phrase);
      return 0;
    } else if(strcmp(input,"snake") == 0){
        // void * snakeProcess = newProcess("Snake", snake_game, 0, 0, NULL, NULL);
        // execute(snakeProcess);
        // freeProcess(snakeProcess);
        snake_game(0, NULL);
        return 0;
    } else if(strcmp(input, "getTime") == 0) {
      printf("\n");
      time();
      return 0;
    } else if(strcmp(input, "clear") == 0) {
      clearScreen();
      printf("\n");
      return 0;
    } else if(strcmp(input, "help") == 0) {
     printHelp();
     return 0;
    } else if(strcmp(input, "exit") == 0) {
      return 1;
    }
    else if(strcmp(input, "zero") == 0) {
      divisionExc();    
      return 0;
    } else if(strcmp(input, "invalidOpCode") == 0) {
      invalidOpCodeException();
      return 0;
    }
    else if(strcmp(input, "mem") == 0){
      printf("\n%l / %l bytes utilizados", usedMem(), freeMem());
      return 0;
    }
    else if(strcmp(input, "wc") == 0){
      printf("\n");
      char buffer[1000];
      int separator = -1;
      scanf(buffer, 1000, separator);
      printf("\n%d", lineCount(buffer));
      return 0;
    }
    else if(strncmp(input, "filter ", 7) == 0){
      char phrase[1000];
      printf("\n%s", filterVowels(phrase, &(input[7])));
      return 0;
    }
    // else if(strcmp(input, "new") == 0){
    //   void * proceso = newProcess("Hola", 0, 0, 0, 0, 0);
    //   printf("\n%x", proceso);
    //   return 0;
    // }
    // else if(strncmp(input, "free ", 5) == 0){
    //   char* phrase = &(input[5]);
    //   int i = atox(phrase);
    //   freeProcess((void *) atox(phrase));
    //   return 0;
    // }
    // else if(strncmp(input, "get ", 4) == 0){
    //   char* phrase = &(input[4]);
    //   int i = atox(phrase);
    //   printf("\n%d", getPid(i));
    //   return 0;
    // }
    else if(strcmp(input, "") == 0){
      return 0;
    }
    else{
      printf("\nWrong command");
      return 0;
    }
}


void shell(){
    char buffer[BUFFER_LENGTH];
    int flag = 0;
    printHelp();


    while (!flag) {
		  printf("\nUser $> ");
		  scanf(buffer, BUFFER_LENGTH, '\n');
		  flag = parse(buffer);
	  }

    printf("\nGoodbye");
    return;
}

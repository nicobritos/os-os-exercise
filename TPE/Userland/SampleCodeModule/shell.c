#include "includes/defines.h"
#include "includes/stdlib.h"
#include "includes/stdio.h"
#include "includes/commands.h"
#include "includes/snake.h"


int parse(char* input){
    if(strncmp(input, "echo ", 5) == 0) {
      char* phrase = &(input[5]);
      printf("\n%s", phrase);
      return 0;
    } else if(strcmp(input,"snake") == 0){
         snake_game();
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
    else{
      printf("\nWrong command");
      return 0;
    }

}


void shell(){
    char buffer[BUFFER_LENGTH] ;
    int flag = 0;

    printHelp();


    while (!flag) {
		  printf("\nUser $>");
		  scanf(buffer, BUFFER_LENGTH);
		  flag = parse(buffer);
	  }

    printf("\nGoodbye");
    return;
}

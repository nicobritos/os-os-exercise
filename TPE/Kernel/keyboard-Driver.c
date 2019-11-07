//This is a personal academic project. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "keyboard-Driver.h"
#include "fileManager.h"
#include "scan-Codes.h"
#include <stdint.h>
#include "videoDriver.h"


 /* PROTOTIPOS */
unsigned int get_key();   // esta en keyboard_Driver.asm
void keyboard_controller();
void add_to_buffer(int input_key);
char get_key_input();
void setActive(uint8_t * key, char value);

#define FALSE 0
#define TRUE 1
#define SIZE 1000

static int buffer[SIZE] = {0};

static int writeIndex = 0;
static int readIndex = 0;
static int size=0;

static uint8_t SHIFT_ACTIVE=FALSE;
static uint8_t CAPS_ACTIVE=FALSE;
static uint8_t CNTRL_ACTIVE=FALSE;

int buffer_empty = TRUE;
int read_index =0;
int write_index = 0;
 
void keyboard_controller(){
  unsigned int scan_code = get_key();

  if (scan_code < 0x80) {
      switch (scan_code) {
        case RSHIFT: case LSHIFT:
            SHIFT_ACTIVE=TRUE;
            break;
        case CAPS:
            CAPS_ACTIVE= !CAPS_ACTIVE;  // si esta mayus activada se desactiva y si esta desactivada, se activa.
            break;
        case CTRL:
            CNTRL_ACTIVE = TRUE;
            break;
      }
      char input_key;
      if (SHIFT_ACTIVE) {
        input_key = getShiftAsciiKey(scan_code);
        add_to_buffer(input_key);
      } else if(CAPS_ACTIVE){
        input_key = getAsciiKey(scan_code);
        if (input_key >= 'a' && input_key <= 'z') {
          input_key -= 32;
        }
        add_to_buffer(input_key);
      }
      else if(CNTRL_ACTIVE){
        input_key = getAsciiKey(scan_code);
        if( input_key == 'D' || input_key == 'd')
          add_to_buffer(EOF);
        else if( input_key == 'C' || input_key == 'c')
          add_to_buffer(CTRLC);
      }
      else{
        input_key = getAsciiKey(scan_code);
        add_to_buffer(input_key);
      }
  } 
  else { // Le agregue este switch por que sino quedaba trabada la mayuscula una vez que la apretaba 
		    switch(scan_code) {
		  	    case CTRL_R:
				        setActive(&CNTRL_ACTIVE, FALSE);	
				        break;
			      case LSHIFT_R: case RSHIFT_R:
				        setActive(&SHIFT_ACTIVE, FALSE);	
				        break;
		      }
  }
   
}

void setActive(uint8_t * key, char value){
  *key = value;
}

void add_to_buffer(int c) {
	buffer[writeIndex] = c;
	writeIndex = (writeIndex + 1)%SIZE;
	size++;

  keyWasPressed();
}

char get_key_input() {
	if (size <= 0) {
		return 0;
	}

	char c = buffer[readIndex];
	size--;
	readIndex = (readIndex + 1)%SIZE;

	return c;
}

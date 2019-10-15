#ifndef KEYBOARD_DRIVER_H
#define KEYBOARD_DRIVER_H

unsigned int get_key();

void keyboard_controller();

void add_to_buffer(char input_key);

char get_key_input();

#endif

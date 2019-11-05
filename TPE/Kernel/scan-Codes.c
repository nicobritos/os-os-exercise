//This is a personal academic project. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
// #include "Scan_Codes.h"
#include "scan-Codes.h"

// const char usakeyboard[128] =
// {
//    0, 27, '1', '2', '3', '4', '5', '6', '7', '8',
//   '9', '0','-','=', '\b','\t', 'q', 'w', 'e', 'r',
//   't', 'y','u', 'i', 'o', 'p', '[', ']', '\n', 0/*CTRL*/,
//   'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',
//   '\'','`',0/*Lshift*/,'\\','z','x','c','v','b','n',
//   'm',',','.',0/*Rshift*/,'*',0/*ALT*/,' '/*SpaceBar*/,0/*CapsLock*/,
//   0/*F1*/,0/*F2*/,0/*F3*/,0/*F4*/,0/*F5*/,0/*F6*/,0/*F7*/,0/*F8*/,0/*F9*/,0/*F10*/,
//   0/*NumLock*/,0/*ScrollLock*/,0/*Home*/,0/*Up*/,0/*PageUp*/,'-',0/*Left*/,0,
//   0/*Right*/,'+',0/*End*/,0/*Down*/,0/*PageDown*/,0/*Insert*/,0/*Delete*/,0,0,0,
//   0/*F11*/,0/*F12*/,0/*F13*/
// };

// const char usakeyboard_shift[0xFF] = {
//   '\x1B', 27, '!', '@', '#', '$', '%','^','&','*','(',')','_',
//   '+', '\x08', '\t', 'Q','W','E','R','T','Y','U','I','{','}','\n', 0,
//   'A','S','D','F','G','H','J','K','L',':','"', 0 ,0,'|', 'Z','X','C','V',
//   'B','N','M','<','>','?',0 , 0 , 0 , ' ', 0, '1','2','3','4','5','6','7',
//   '8','9', 0,0,0,0,'\x11',0,0,'\x12', 0, '\x12',0,0, '\x13'
// };


// los de arriba no andan en mi compu (nico), es cuestion de comentar y descomentar 
const unsigned char usakeyboard[128] = { 0, //Filler
    0x1B, //Escape
    '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=',
    0x08, //Backspace
    0x09, //Tab
    'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']',
    0x0A, //New line
    0, //Ctrl
    'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'',
    0x60, //Back tick
    0,  //Left Shift
    0x5C, //Back slash
    'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/',
    0, //Right Shift
    '*', //Only for keypads
    0,  //Alt
    ' ', //Space bar
    0,  //Caps
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //F1 to F10
    0,      //Num Lock
    0,      //Scroll Lock
    0,  //Home key
    0,  //Up Arrow
    0,  //Page up
    '-',
    0,  // Left Arrow
    0,  //Filler
    0,  //Right Arrow
    '+',
    0,  //End key
    0,  //Down Arrow
    0,  //Page Down
    0,  //Insert Key
    0,  //Delete Key
    0,   0,   0, //Fillers
    0,  //F11
    0,  //F12
    0,  //Fillers
};

//Looking for a more elegant solution (Stolen from some guys forum and edited to my keyboard razer blade US Layout)
const char usakeyboard_shift[255] = {0, 0x1B, '!', '@','#','$','%','^','&','*',
    '(',')','_','+',0x08,0x09,'Q','W','E','R','T','Y','U','I','O','P','{','}','\n'
    ,0,'A','S','D','F','G','H','J','K','L',':','"','~',0,'|','Z','X','C','V','B'
    ,'N','M','<','>','?',0,0,0,' ',0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,'-',0,0,0,'+',0,0,0};


char getAsciiKey(int scan){
  return usakeyboard[scan];
}

char getShiftAsciiKey(int scan){
  return usakeyboard_shift[scan];
}

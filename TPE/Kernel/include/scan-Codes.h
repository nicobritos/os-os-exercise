// #ifndef SCAN_CODES_H
// #define SCAN_CODES_H

// #define RSHIFT            (char)0x36
// #define RSHIFT_R          (char)0xB6
// #define LSHIFT            (char)0x2A
// #define LSHIFT_R          (char)0xAA
// #define CTRL              (char)0x1D
// #define CTRL_R            (char)0x9D
// #define ALT               (char)0x38
// #define ALT_R             (char)0xB8
// #define CAPS              (char)0x3A
// #define CAPS_R            (char)0xBA
// #define UP_ARROW	      (char)0x48
// #define UP_ARROW_R	      (char)0xC8
// #define	DOWN_ARROW	      (char)0x50
// #define DOWN_ARROW_R      (char)0xD0
// #define LEFT_ARROW	      (char)0x4B
// #define LEFT_ARROW_R      (char)0xCB
// #define RIGHT_ARROW	      (char)0x4D
// #define RIGHT_ARROW_R     (char)0xCD
// #define ESC			      (char)0x01
// #define ESC_R		      (char)0x81
// #define F1			      (char)0x3B
// #define F1_R		      (char)0xBB
// #define F2			      (char)0x3C
// #define F2_R		      (char)0xBC
// #define F3			      (char)0x3D
// #define F3_R		      (char)0xBD
// #define F4			      (char)0x3E
// #define F4_R	          (char)0xBE
// #define F5			      (char)0x3F
// #define F5_R		      (char)0xBF
// #define F6			      (char)0x40
// #define F6_R		      (char)0xC0
// #define F7			      (char)0x41
// #define F7_R		      (char)0xC1
// #define F8			      (char)0x42
// #define F8_R		      (char)0xC2
// #define F9			      (char)0x43
// #define F9_R		      (char)0xC3
// #define F10			      (char)0x44
// #define F10_R		      (char)0xC4
// #define F11			      (char)0x57
// #define F11_R		      (char)0xD7
// #define F12			      (char)0x58
// #define F12_R		      (char)0xD8
// #define TAB			      (char)0x0F
// #define TAB_R		      (char)0x8F
// #define BACKSPACE         (char)0x0E
  
// char getAsciiKey(int scan);

// char getShiftAsciiKey(int scan);

// #endif

#ifndef SCAN_CODES_H
#define SCAN_CODES_H


// Le saque los (char) por que fallaba en algunos casteos que daba negativo
#define EOF                 -1
#define CTRLC               0x03
#define RSHIFT        		0x36
#define RSHIFT_R      		0xB6
#define LSHIFT        		0x2A
#define LSHIFT_R      		0xAA
#define CTRL          		0x1D
#define CTRL_R        		0x9D
#define ALT         		0x38
#define ALT_R       		0xB8
#define CAPS       		    0x3A
#define CAPS_R     		    0xBA
#define UP_ARROW	     	0x48
#define UP_ARROW_R	 	  	0xC8
#define	DOWN_ARROW	   		0x50
#define DOWN_ARROW_R   		0xD0
#define LEFT_ARROW	   		0x4B
#define LEFT_ARROW_R  		0xCB
#define RIGHT_ARROW	  		0x4D
#define RIGHT_ARROW_R       0xCD
#define ESC			        0x01
#define ESC_R		        0x81
#define F1			        0x3B
#define F1_R		        0xBB
#define F2			        0x3C
#define F2_R		        0xBC
#define F3			        0x3D
#define F3_R		        0xBD
#define F4			        0x3E
#define F4_R	         	0xBE
#define F5			        0x3F
#define F5_R		        0xBF
#define F6			        0x40
#define F6_R		        0xC0
#define F7			        0x41
#define F7_R		        0xC1
#define F8			        0x42
#define F8_R		        0xC2
#define F9			        0x43
#define F9_R		        0xC3
#define F10			        0x44
#define F10_R		        0xC4
#define F11			        0x57
#define F11_R		        0xD7
#define F12			        0x58
#define F12_R		        0xD8
#define TAB			        0x0F
#define TAB_R		        0x8F
#define BACKSPACE           0x0E

char getAsciiKey(int scan);

char getShiftAsciiKey(int scan);

#endif

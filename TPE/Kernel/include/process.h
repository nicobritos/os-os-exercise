#ifndef _PROCESS_H
	#define _PROCESS_H
	#include <stdint.h>

	typedef enum t_state {READY = 0, RUNNING, KILLED, LOCKED} t_state;

	typedef struct t_stack {
		uint16_t gs;
		uint16_t fs;
	    uint64_t r15;
	    uint64_t r14;
	    uint64_t r13;
	    uint64_t r12;
	    uint64_t r11;
	    uint64_t r10;
	    uint64_t r9;
	    uint64_t r8;
	    uint64_t rsi;
	    uint64_t rdi;
	    uint64_t rbp;
	    uint64_t rdx;
	    uint64_t rcx;
	    uint64_t rbx;
	    uint64_t rax;
	    uint64_t rip;
	    uint16_t cs;
	    uint64_t rflags;
	    uint64_t rsp;
	    uint16_t ss;
	} t_stack;

	typedef struct t_process {
		int pid;
		t_state state;
		t_stack *stack;
	} t_process;
#endif


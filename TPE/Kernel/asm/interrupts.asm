GLOBAL _cli
GLOBAL _sti
GLOBAL picMasterMask
GLOBAL picSlaveMask
GLOBAL haltcpu
GLOBAL _hlt

EXTERN pushcli
EXTERN pushsti

GLOBAL _irq00Handler
GLOBAL _irq01Handler
GLOBAL _irq02Handler
GLOBAL _irq03Handler
GLOBAL _irq04Handler
GLOBAL _irq05Handler
GLOBAL _syscallHandler

EXTERN syscallHandler

GLOBAL _exception0Handler
GLOBAL _exceptionInvalidOpcodeHandler
GLOBAL _syscall
EXTERN irqDispatcher
EXTERN exceptionDispatcher


SECTION .text

%macro pushState 0
  push fs
  push gs

  push rax
  push rbx
  push rcx
  push rdx

  push rbp
  push rdi
  push rsi

  push r8
  push r9
  push r10
  push r11

  push r12
  push r13
  push r14
  push r15
%endmacro

%macro popState 0
  pop r15
  pop r14
  pop r13
  pop r12
  
  pop r11
  pop r10
  pop r9
  pop r8

  pop rsi
  pop rdi
  pop rbp

  pop rdx
  pop rcx
  pop rbx
  pop rax

  pop gs
  pop fs
%endmacro

%macro irqHandlerMaster 1
  pushState

  push rax
  call pushcli
  pop rax

  mov rdi, %1 ; pasaje de parametro
  mov rsi, rsp; pasaje de parametro del puntero a los registros
  
  push rbp 
  mov rbp, rsp

  call irqDispatcher
  
  mov rsp, rbp
  pop rbp
  
  ; signal pic EOI (End of Interrupt)
  mov al, 20h
  out 20h, al

  push rax
  call pushsti
  pop rax
  popState

  iretq
%endmacro

%macro exceptionHandler 1
cli
pushState

	mov rdi, %1 ; first parameter
	mov rsi, rsp ; second parameter

	call exceptionDispatcher

	popState
	mov qword [rsp],0x400000
  sti
	iretq
%endmacro


_hlt:
	sti
	hlt
	ret

_halt:
    hlt
    ret

_cli:
	cli
	ret


_sti:
	sti
	ret

picMasterMask:
	push rbp
    mov rbp, rsp
    mov ax, di
    out	21h,al
    pop rbp
    retn

picSlaveMask:
	push    rbp
    mov     rbp, rsp
    mov     ax, di  ; ax = mascara de 16 bits
    out	0A1h,al
    pop     rbp
    retn

;EOI
  mov al, 20h
  out 20h, al
  iretq

;8254 Timer (Timer Tick)
_irq00Handler:
  	irqHandlerMaster 0

;Keyboard
_irq01Handler:
  	irqHandlerMaster 1

;Cascade pic never called
_irq02Handler:
  	irqHandlerMaster 2

;Serial Port 2 and 4
_irq03Handler:
  irqHandlerMaster 3

;Serial Port 1 and 3
_irq04Handler:
  irqHandlerMaster 4

;USB
_irq05Handler:
  irqHandlerMaster 5



_syscallHandler:
  push rax
  call pushcli
	pop rax

  push rbp
	mov rbp, rsp

	call syscallHandler

	mov rsp, rbp
	pop rbp

  push rax
  call pushsti
  pop rax
	iretq

;Zero Division Exception
_exception0Handler:
	exceptionHandler 0

;Invalid Opcode handler
_exceptionInvalidOpcodeHandler:
	exceptionHandler 1

haltcpu:
	cli
	hlt
	ret

SECTION .bss
	aux resq 1
	rip resq 1
	stack resq 1

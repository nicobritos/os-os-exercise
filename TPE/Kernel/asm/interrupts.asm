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

GLOBAL _exception0Handler
GLOBAL _exceptionInvalidOpcodeHandler
GLOBAL _syscall
EXTERN irqDispatcher
EXTERN exceptionDispatcher
EXTERN sys_total_ticks
EXTERN sys_ticks_per_second
EXTERN sys_read
EXTERN sys_write
EXTERN sys_clear
EXTERN sys_pixel
EXTERN sys_time
EXTERN sys_used_mem
EXTERN sys_free_mem
EXTERN sys_malloc
EXTERN sys_free
EXTERN sys_new_process
EXTERN sys_free_process
EXTERN sys_get_pid
EXTERN sys_exec
EXTERN reboot

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
  pushState

  push rax
  call pushcli
  pop rax


  mov rdi, %1 ; first parameter
  mov rsi, rsp ; second parameter

  push rbp
  mov rbp, rsp
  
	call exceptionDispatcher

  mov rsp, rbp
  pop rbp

  push rax
  call pushsti
  pop rax

  popState

  ;mov qword [rsp],reboot
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



_syscall:
  push rax
  call pushcli
	pop rax

  push rbp
  mov rbp, rsp

  cmp rdi, 0x01     ; syscall de total ticks
  je .syscallTotalTicks

  cmp rdi, 0x02     ; syscall de ticks per sec
  je .syscallTicksPerSecond

  cmp rdi, 0x03 		; syscall del read
  je .syscallRead

  cmp rdi, 0x04		; syscall de write
  je .syscallWrite

  cmp rdi, 0x05		; syscall de time
  je .syscallTime

  cmp rdi, 0x06		; syscall de clear
  je .syscallClear

  cmp rdi, 0x07		; syscall de pixel
  je .syscallPixel

  cmp rdi, 0x08
  je .syscallUsedMem

  cmp rdi, 0x09
  je .syscallFreeMem

  cmp rdi, 0x0a
  je .syscallMalloc

  cmp rdi, 0x0b
  je .syscallFree

  cmp rdi, 0x0c
  je .syscallNewProcess

  cmp rdi, 0x0d
  je .syscallFreeProcess

  cmp rdi, 0x0e
  je .syscallGetPid

  cmp rdi, 0x0f
  je .syscallExec

.cont:
	mov rsp, rbp
  pop rbp

  push rax
  call pushsti
  pop rax
  iretq	;Dont use ret when returning from int call


.syscallRead:
  mov rdi, rsi 	; re-ordering the arguments to send to sys_read
  mov rsi, rdx
  mov rdx, rcx
  call sys_read
  jmp .cont

.syscallWrite:
  mov rdi, rsi 	; re-ordering the arguments to send to sys_write
  mov rsi, rdx
  mov rdx, rcx
  call sys_write
  jmp .cont

.syscallTime:
  mov rdi, rsi 	; re-ordering the arguments to send to sys_time
  call sys_time
  jmp .cont

.syscallClear:
  call sys_clear
  jmp .cont

.syscallPixel:
  mov rdi, rsi	; re-ordering the arguments to send to sys_pixel
  mov rsi, rdx
  mov rdx, rcx
  mov rcx, r8
  mov r8, r9
  call sys_pixel
  jmp .cont

.syscallTotalTicks:
  mov rdi, rsi
  call sys_total_ticks
  jmp .cont

.syscallTicksPerSecond:
  mov rdi, rsi
  call sys_ticks_per_second
  jmp .cont

.syscallUsedMem:
  call sys_used_mem
  jmp .cont

.syscallFreeMem:
  call sys_free_mem
  jmp .cont

.syscallMalloc:
  mov rdi, rsi	; re-ordering the arguments to send to sys_pixel
  mov rsi, rdx
  call sys_malloc
  jmp .cont

.syscallFree:
  mov rdi, rsi	; re-ordering the arguments to send to sys_pixel
  mov rsi, rdx
  call sys_free
  jmp .cont

.syscallNewProcess:
  mov rdi, rsi
  mov rsi, rdx
  mov rdx, rcx
  mov rcx, r8
  mov r8, r9
  mov r9, r10
  call sys_new_process
  jmp .cont

.syscallFreeProcess:
  mov rdi, rsi
  call sys_free_process
  jmp .cont

.syscallGetPid:
  mov rdi, rsi
  call sys_get_pid
  jmp .cont

.syscallExec:
  mov rdi, rsi
  call sys_exec
  jmp .cont

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

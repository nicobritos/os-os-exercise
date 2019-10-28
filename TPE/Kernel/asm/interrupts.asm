GLOBAL _cli
GLOBAL _sti
GLOBAL picMasterMask
GLOBAL picSlaveMask
GLOBAL haltcpu
GLOBAL _hlt


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

EXTERN sys_getpid
EXTERN sys_fork
EXTERN sys_execve
EXTERN sys_kill
EXTERN sys_getpriority
EXTERN sys_setpriority
EXTERN sys_ptrace

EXTERN sys_used_mem
EXTERN sys_free_mem
EXTERN sys_malloc
EXTERN sys_free

EXTERN sys_read_pipe
EXTERN sys_write_pipe


SECTION .text
%macro pushState 0
  ; Ya de por si tengo RIP y RFLAGS en ese orden
  push r15
  push r14
  push r13
  push r12
  push r11
  push r10
  push r9
  push r8

	push rsi
	push rdi
	push rbp
  push rsp

	push rdx
	push rcx
	push rbx
	push rax

  mov rax, [rsp + (16 * 8) + 8] ; 16 * 8 de los registros de recien, 8 del RFLAGS, (ahora apunta al RIP viejo)
  push rax ; RIP
%endmacro

%macro popState 0
  pop rax ; RIP
  mov [rsp + (16 * 8) + 8], rax ; 16 * 8 de los registros de recien, 8 del RFLAGS, (ahora apunta al RIP viejo)

  pop rax
  pop rbx
  pop rcx
  pop rdx

  pop rsp
  pop rbp
  pop rdi
  pop rsi

  pop r8
  pop r9
  pop r10
  pop r11
  pop r12
  pop r13
  pop r14
  pop r15
  ; Luego tengo RFLAGS y RIP en ese orden
%endmacro

%macro irqHandlerMaster 1
	pushState

  mov rdi, %1 ; pasaje de parametro
  lea rsi, [rsp + (17 * 8)]; pasaje de parametro del puntero a los registros (16 + RIP)
	call irqDispatcher

	; signal pic EOI (End of Interrupt)
	mov al, 20h
	out 20h, al

	popState
	iretq
%endmacro



%macro exceptionHandler 1
  pushState

	mov rdi, %1 ; first parameter
	mov rsi, rsp ; second parameter

	call exceptionDispatcher

	popState

	mov qword [rsp],0x400000
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
  cli
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
  
  cmp rdi, 0x0c 		; syscall del read pipe
  je .syscallReadPipe

  cmp rdi, 0x0d		; syscall de write pipe
  je .syscallWritePipe

  cmp rdi, 39     ; getpid
  je .syscallGetpid

  cmp rdi, 57     ; fork
  je .syscallFork

  cmp rdi, 59     ; execve
  je .syscallExecve

  cmp rdi, 62     ; kill
  je .syscallKill

  cmp rdi, 140    ; getpriority
  je .syscallGetpriority

  cmp rdi, 141    ; setpriority
  je .syscallSetpriority

  cmp rdi, 101    ; ptrace
  je .syscallPtrace
  
  
.cont:
	mov rsp, rbp
  pop rbp
  sti
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

.syscallGetpid:
  call sys_getpid
  jmp .cont

.syscallFork:
  call sys_fork
  jmp .cont

.syscallExecve:
  mov rdi, rsi
  mov rsi, rdx
  mov rdx, rcx
  call sys_execve
  jmp .cont

.syscallKill:
  mov rdi, rsi
  call sys_kill
  jmp .cont

.syscallGetpriority:
  mov rdi, rsi
  mov rsi, rdx
  ;call sys_getpriority
  jmp .cont

.syscallSetpriority:
  mov rdi, rsi
  mov rsi, rdx
  mov rdx, rcx
  ;call sys_setpriority
  jmp .cont

.syscallPtrace:
  mov rdi, rsi
  mov rsi, rdx
  mov rdx, rcx
  mov rcx, r8
  ;call sys_ptrace
  jmp .cont

.syscallUsedMem
  call sys_used_mem
  jmp .cont

.syscallFreeMem
  call sys_free_mem
  jmp .cont

.syscallMalloc
  mov rdi, rsi	; re-ordering the arguments to send to sys_pixel
  mov rsi, rdx
  call sys_malloc
  jmp .cont

.syscallFree
  mov rdi, rsi	; re-ordering the arguments to send to sys_pixel
  mov rsi, rdx
  call sys_free
  jmp .cont

.syscallReadPipe:
  mov rdi, rsi 	; re-ordering the arguments to send to sys_read
  mov rsi, rdx
  mov rdx, rcx
  call sys_read_pipe
  jmp .cont

.syscallWritePipe:
  mov rdi, rsi 	; re-ordering the arguments to send to sys_write
  mov rsi, rdx
  mov rdx, rcx
  call sys_write_pipe
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

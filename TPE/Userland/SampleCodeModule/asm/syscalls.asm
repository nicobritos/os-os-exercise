GLOBAL read
GLOBAL write
GLOBAL os_time
GLOBAL os_clear
GLOBAL os_draw
GLOBAL os_ticks
GLOBAL os_sec
GLOBAL os_beep
GLOBAL os_unbeep

section .text

%macro start 0
	push rbp
	mov rbp, rsp

	push rbx
	push rcx
	push r12
	push r13
	push r15
%endmacro

%macro finish 0
	pop r15
	pop r13
	pop r12
	pop rcx
	pop rbx

	mov rsp, rbp
	pop rbp
	ret
%endmacro


os_ticks:
	start			;armo stack frame y pusheo los registros 

	; rdi --> codigo de la syscall
 
	mov rdi, 0x01
	mov rsi, aux

	int 80h

	finish			;desarmo stack frame y popeo los registros

os_sec:
	start			;armo stack frame y pusheo los registros

	; rdi --> codigo de la syscall

	mov rdi, 0x02
	mov rsi, aux

	int 80h

	finish			;desarmo stack frame y popeo los registros

read:
	start			;armo stack frame y pusheo los registros

	
	; rdi --> file descriptor 
	; rsi --> buffer 
	; rdx --> bytes que tiene que leer
	
	mov rcx, rdx
	mov rdx, rsi
	mov rsi, rdi
	mov rdi, 0x03

	; rdi --> codigo de la syscall 
	; rsi --> file descriptor
	; rdx --> buffer
	; rcx --> bytes que tiene que leer

	int 80h

	; devuelve en rax la cantitad de bytes que leyo y en buffer estan los caracteres leidos

	finish			;desarmo stack frame y popeo los registros

write:
	start

	; rdi --> file descriptor
	; rsi --> buffer 
	; rdx --> bytes que va a escribir

	mov rcx, rdx
	mov rdx, rsi
	mov rsi, rdi
	mov rdi, 0x04

	; rdi --> codigo de la syscall 
	; rsi --> file descriptor 
	; rdx --> buffer 
	; rcx --> bytes que va a escribir

	int 80h

	; retorna en rax la cantidad de bytes que escribio

	finish			; desarmo stack frame y popeo los registros

os_time:
	start			; armo stack frame y pusheo los registros

	mov rdi, 0x05
	mov rsi, time		; 'time' reservado en .data

	; rdi --> codigo de la syscall 
	; rsi --> buffer para guardar le tiempo

	int 80h

	; retorna en rax un string con el tiempo 

	finish			; desarmo stack frame y popeo los registros

os_clear:
	start				; armo stack frame y pusheo los registros

	; rdi --> codigo de la syscall 
	mov rdi, 0x06

	int 80h

	finish				; desarmo stack frame y popeo los registros


os_draw:
	start				; armo stack frame y pusheo los registros

	; rdi --> coordenada x
	; rsi --> coordenada y
	; rdx --> rojo 
	; rcx --> verde 
	; r8  --> azul

	mov r9, r8
	mov r8, rcx
	mov rcx, rdx
	mov rdx, rsi
	mov rsi, rdi
	mov rdi, 0x07

	; rdi --> codigo de la syscall 
	; rsi --> coordenada x 
	; rdx --> coordenada y  
	; rcx --> rojo 
	; r8  --> verde 
	; r9  --> azul

	int 80h

	finish				;desarmo stack frame y popeo los registros
	
section .data
	time times 6 DW 0

section .bb
	aux resb 4	; para enteros
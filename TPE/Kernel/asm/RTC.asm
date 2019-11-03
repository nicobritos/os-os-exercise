section .text

GLOBAL getSec
GLOBAL getMin
GLOBAL getHour
GLOBAL getTime 

EXTERN pushcli
EXTERN pushsti

;
; INFO extraida de: 
; http://stanislavs.org/helppc/cmos_ram.html
;


;
; Seteo el formato con la informacion 
; extraida de la pagina mencionada anteriormente
; 

getTime:
	push rax
  	call pushcli
	pop rax
	out 70h, al
	in al, 71h
	push rax
  	call pushsti
	pop rax
	ret

getHour:
	push rax
  	call pushcli
	pop rax
    push rbp
    mov rbp, rsp
    call configStatusRegisterB
    mov rax, 0h
    mov al, 4h
    call getTime
    mov rsp, rbp
    pop rbp
	push rax
  	call pushsti
	pop rax
    ret

getMin:
	push rax
  	call pushcli
	pop rax
	push rbp
  	mov rbp, rsp
  	call configStatusRegisterB
	mov rax, 0h
    	mov al, 2h
	call getTime
	mov rsp, rbp
	pop rbp
	push rax
  	call pushsti
	pop rax
	ret

getSec:
	push rax
  	call pushcli
	pop rax
 	push rbp
  	mov rbp, rsp
  	call configStatusRegisterB
	mov rax, 0h
	call getTime
	mov rsp, rbp
  	pop rbp
	push rax
  	call pushsti
	pop rax
	ret

configStatusRegisterB:
	push rax
  	call pushcli
	pop rax
	push rbp
  	mov rbp, rsp
	mov al,0x0B ; RTC Status Register B
	out 70h,al
	in al, 71h
	or al, 0x04 ; Second bit = 1
	out 71h, al
	mov rsp, rbp
  	pop rbp
	push rax
  	call pushsti
	pop rax
	ret


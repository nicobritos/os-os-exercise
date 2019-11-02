GLOBAL idleFunction
GLOBAL idleKernel
	
EXTERN pushcli
EXTERN pushsti

section .text

idleFunction:
	push rax
	call pushsti
	pop rax
	_idleFunction:
	hlt
	jmp _idleFunction
	ret

idleKernel:
	push rax
	call pushsti
	pop rax
	hlt
	ret

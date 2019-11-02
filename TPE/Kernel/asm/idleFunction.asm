GLOBAL idleFunction
GLOBAL idleKernel
	
EXTERN pushcli
EXTERN pushsti

section .text

idleFunction:
	call pushsti
	_idleFunction:
	hlt
	jmp _idleFunction
	ret

idleKernel:
	call pushsti
	hlt
	ret

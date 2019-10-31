GLOBAL idleFunction
GLOBAL idleKernel

section .text

idleFunction:
	sti
	_idleFunction
	hlt
	jmp _idleFunction
	ret

idleKernel:
	sti
	hlt
	ret

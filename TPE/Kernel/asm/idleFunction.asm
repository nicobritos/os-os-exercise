GLOBAL idleFunction

section .text
	
idleFunction:
  	_start_idle:
	sti
	hlt
	jmp _start_idle
	ret

	.file	"apps.c"
	.intel_syntax noprefix
	.section	.rodata.str1.8,"aMS",@progbits,1
	.align 8
.LC0:
	.string	"\nhelp - display available commands \n"
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC1:
	.string	"snake\n"
	.section	.rodata.str1.8
	.align 8
.LC2:
	.string	"getTime - Prints the current time in Argentina \n"
	.align 8
.LC3:
	.string	"cat (message) - Prints out the message \n"
	.align 8
.LC4:
	.string	"zero - Makes a divition by cero exception \n"
	.align 8
.LC5:
	.string	"invalidOpCode - Makes a invalid operation exception \n"
	.section	.rodata.str1.1
.LC6:
	.string	"clear - Clears the screen \n"
	.section	.rodata.str1.8
	.align 8
.LC7:
	.string	"mem - Prints the memory state\n"
	.align 8
.LC8:
	.string	"wc - Print the number of lines\n"
	.align 8
.LC9:
	.string	"filter (message) - Filters the vowels from the message\n"
	.section	.rodata.str1.1
.LC10:
	.string	"exit - Exits the terminal"
	.section	.text.unlikely,"ax",@progbits
.LCOLDB11:
	.text
.LHOTB11:
	.p2align 4,,15
	.globl	help
	.type	help, @function
help:
.LFB0:
	.cfi_startproc
	sub	rsp, 8
	.cfi_def_cfa_offset 16
	mov	edi, OFFSET FLAT:.LC0
	xor	eax, eax
	call	printf
	mov	edi, OFFSET FLAT:.LC1
	xor	eax, eax
	call	printf
	mov	edi, OFFSET FLAT:.LC2
	xor	eax, eax
	call	printf
	mov	edi, OFFSET FLAT:.LC3
	xor	eax, eax
	call	printf
	mov	edi, OFFSET FLAT:.LC4
	xor	eax, eax
	call	printf
	mov	edi, OFFSET FLAT:.LC5
	xor	eax, eax
	call	printf
	mov	edi, OFFSET FLAT:.LC6
	xor	eax, eax
	call	printf
	mov	edi, OFFSET FLAT:.LC7
	xor	eax, eax
	call	printf
	mov	edi, OFFSET FLAT:.LC8
	xor	eax, eax
	call	printf
	mov	edi, OFFSET FLAT:.LC9
	xor	eax, eax
	call	printf
	mov	edi, OFFSET FLAT:.LC10
	xor	eax, eax
	call	printf
	mov	eax, 1
	add	rsp, 8
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE0:
	.size	help, .-help
	.section	.text.unlikely
.LCOLDE11:
	.text
.LHOTE11:
	.section	.rodata.str1.1
.LC12:
	.string	"\n"
.LC13:
	.string	"Please enter a number"
.LC14:
	.string	"Process killed\n"
	.section	.text.unlikely
.LCOLDB15:
	.text
.LHOTB15:
	.p2align 4,,15
	.globl	kill
	.type	kill, @function
kill:
.LFB1:
	.cfi_startproc
	push	rbx
	.cfi_def_cfa_offset 16
	.cfi_offset 3, -16
	mov	edi, OFFSET FLAT:.LC12
	mov	rbx, rsi
	xor	eax, eax
	call	printf
	mov	rdi, QWORD PTR [rbx]
	call	atoi
	movsx	rdi, eax
	cmp	rdi, -1
	je	.L8
	call	killProcess
	mov	edi, OFFSET FLAT:.LC14
	xor	eax, eax
	call	printf
	mov	eax, 1
	pop	rbx
	.cfi_remember_state
	.cfi_restore 3
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L8:
	.cfi_restore_state
	mov	edi, OFFSET FLAT:.LC13
	xor	eax, eax
	call	printf
	xor	eax, eax
	pop	rbx
	.cfi_restore 3
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE1:
	.size	kill, .-kill
	.section	.text.unlikely
.LCOLDE15:
	.text
.LHOTE15:
	.section	.rodata.str1.1
.LC16:
	.string	"Please enter a number\n"
.LC17:
	.string	"high"
.LC18:
	.string	"low"
	.section	.rodata.str1.8
	.align 8
.LC19:
	.string	"Please enter a valid priority\n"
	.section	.rodata.str1.1
.LC20:
	.string	"Priority set\n"
.LC21:
	.string	"Missing arguments\n"
	.section	.text.unlikely
.LCOLDB22:
	.text
.LHOTB22:
	.p2align 4,,15
	.globl	nice
	.type	nice, @function
nice:
.LFB2:
	.cfi_startproc
	push	r12
	.cfi_def_cfa_offset 16
	.cfi_offset 12, -16
	push	rbp
	.cfi_def_cfa_offset 24
	.cfi_offset 6, -24
	xor	eax, eax
	push	rbx
	.cfi_def_cfa_offset 32
	.cfi_offset 3, -32
	movsx	rbx, edi
	mov	edi, OFFSET FLAT:.LC12
	mov	r12, rsi
	call	printf
	mov	edi, 800
	call	malloc
	mov	rsi, QWORD PTR [r12]
	mov	edx, 100
	mov	rdi, rax
	mov	rbp, rax
	call	tokenArgs
	cmp	rbx, rax
	je	.L18
	mov	edi, OFFSET FLAT:.LC21
	xor	eax, eax
	call	printf
	xor	eax, eax
.L12:
	pop	rbx
	.cfi_remember_state
	.cfi_restore 3
	.cfi_def_cfa_offset 24
	pop	rbp
	.cfi_restore 6
	.cfi_def_cfa_offset 16
	pop	r12
	.cfi_restore 12
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L18:
	.cfi_restore_state
	mov	rdi, QWORD PTR [rbp+0]
	call	atoi
	movsx	rbx, eax
	cmp	rbx, -1
	je	.L19
	mov	rdi, QWORD PTR [rbp+8]
	mov	esi, OFFSET FLAT:.LC17
	call	strcmp
	test	eax, eax
	je	.L14
	mov	rdi, QWORD PTR [rbp+8]
	mov	esi, OFFSET FLAT:.LC18
	call	strcmp
	test	eax, eax
	mov	esi, 1
	jne	.L20
.L13:
	mov	rdi, rbx
	xor	eax, eax
	call	setProcessPriority
	mov	edi, OFFSET FLAT:.LC20
	xor	eax, eax
	call	printf
	pop	rbx
	.cfi_remember_state
	.cfi_restore 3
	.cfi_def_cfa_offset 24
	mov	eax, 1
	pop	rbp
	.cfi_restore 6
	.cfi_def_cfa_offset 16
	pop	r12
	.cfi_restore 12
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L14:
	.cfi_restore_state
	xor	esi, esi
	jmp	.L13
	.p2align 4,,10
	.p2align 3
.L19:
	mov	edi, OFFSET FLAT:.LC16
	xor	eax, eax
	call	printf
	xor	eax, eax
	jmp	.L12
	.p2align 4,,10
	.p2align 3
.L20:
	mov	edi, OFFSET FLAT:.LC19
	xor	eax, eax
	call	printf
	xor	eax, eax
	jmp	.L12
	.cfi_endproc
.LFE2:
	.size	nice, .-nice
	.section	.text.unlikely
.LCOLDE22:
	.text
.LHOTE22:
	.section	.rodata.str1.1
.LC23:
	.string	"Process Ready\n"
.LC24:
	.string	"Process Locked\n"
.LC25:
	.string	"Proceso no lockeado ni listo"
	.section	.text.unlikely
.LCOLDB26:
	.text
.LHOTB26:
	.p2align 4,,15
	.globl	block
	.type	block, @function
block:
.LFB3:
	.cfi_startproc
	push	rbx
	.cfi_def_cfa_offset 16
	.cfi_offset 3, -16
	mov	edi, OFFSET FLAT:.LC12
	mov	rbx, rsi
	xor	eax, eax
	call	printf
	mov	rdi, QWORD PTR [rbx]
	call	atoi
	movsx	rdi, eax
	cmp	rdi, -1
	je	.L27
	call	toogleProcessLock
	cmp	eax, 1
	je	.L28
	cmp	eax, 3
	je	.L29
	mov	edi, OFFSET FLAT:.LC25
	xor	eax, eax
	call	printf
	mov	eax, 1
	pop	rbx
	.cfi_remember_state
	.cfi_restore 3
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L27:
	.cfi_restore_state
	mov	edi, OFFSET FLAT:.LC13
	xor	eax, eax
	call	printf
	xor	eax, eax
	pop	rbx
	.cfi_remember_state
	.cfi_restore 3
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L29:
	.cfi_restore_state
	mov	edi, OFFSET FLAT:.LC24
	xor	eax, eax
	call	printf
	mov	eax, 1
	pop	rbx
	.cfi_remember_state
	.cfi_restore 3
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L28:
	.cfi_restore_state
	mov	edi, OFFSET FLAT:.LC23
	xor	eax, eax
	call	printf
	mov	eax, 1
	pop	rbx
	.cfi_restore 3
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE3:
	.size	block, .-block
	.section	.text.unlikely
.LCOLDE26:
	.text
.LHOTE26:
	.ident	"GCC: (Debian 4.9.2-10+deb8u1) 4.9.2"
	.section	.note.GNU-stack,"",@progbits

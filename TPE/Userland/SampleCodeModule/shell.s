	.file	"shell.c"
	.intel_syntax noprefix
	.section	.text.unlikely,"ax",@progbits
.LCOLDB0:
	.text
.LHOTB0:
	.p2align 4,,15
	.globl	parseWithPipe
	.type	parseWithPipe, @function
parseWithPipe:
.LFB2:
	.cfi_startproc
	rep ret
	.cfi_endproc
.LFE2:
	.size	parseWithPipe, .-parseWithPipe
	.section	.text.unlikely
.LCOLDE0:
	.text
.LHOTE0:
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC1:
	.string	"help"
.LC2:
	.string	"phylo"
.LC3:
	.string	"s"
.LC4:
	.string	"Hola"
.LC5:
	.string	"Chau"
.LC6:
	.string	"kill "
.LC7:
	.string	"kill"
.LC8:
	.string	"nice "
.LC9:
	.string	"nice"
.LC10:
	.string	"block "
.LC11:
	.string	"block"
.LC12:
	.string	""
.LC13:
	.string	"\nWrong command"
	.section	.text.unlikely
.LCOLDB14:
	.text
.LHOTB14:
	.p2align 4,,15
	.globl	parse
	.type	parse, @function
parse:
.LFB3:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	push	rbx
	.cfi_def_cfa_offset 24
	.cfi_offset 3, -24
	mov	ebp, esi
	mov	esi, OFFSET FLAT:.LC1
	mov	rbx, rdi
	sub	rsp, 88
	.cfi_def_cfa_offset 112
	call	strcmp
	test	eax, eax
	jne	.L3
	xor	edx, edx
	mov	esi, OFFSET FLAT:help
	mov	edi, OFFSET FLAT:.LC1
	call	newProcess
.L4:
	test	rax, rax
	jle	.L11
	test	ebp, ebp
	jne	.L11
	mov	rdi, rax
	xor	eax, eax
	call	waitpid
.L11:
	add	rsp, 88
	.cfi_remember_state
	.cfi_def_cfa_offset 24
	xor	eax, eax
	pop	rbx
	.cfi_restore 3
	.cfi_def_cfa_offset 16
	pop	rbp
	.cfi_restore 6
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L3:
	.cfi_restore_state
	mov	esi, OFFSET FLAT:.LC2
	mov	rdi, rbx
	call	strcmp
	test	eax, eax
	je	.L11
	mov	esi, OFFSET FLAT:.LC3
	mov	rdi, rbx
	call	strcmp
	test	eax, eax
	jne	.L6
	mov	edi, OFFSET FLAT:.LC4
	call	printf
	mov	edi, 2000
	call	sleep
	mov	edi, OFFSET FLAT:.LC5
	xor	eax, eax
	call	printf
	jmp	.L11
	.p2align 4,,10
	.p2align 3
.L6:
	mov	edx, 5
	mov	esi, OFFSET FLAT:.LC6
	mov	rdi, rbx
	call	strncmp
	test	eax, eax
	je	.L24
	mov	edx, 5
	mov	esi, OFFSET FLAT:.LC8
	mov	rdi, rbx
	call	strncmp
	test	eax, eax
	jne	.L8
	mov	rdi, rsp
	xor	eax, eax
	mov	ecx, 10
	rep stosq
	add	rbx, 5
	xor	r8d, r8d
	mov	rcx, rsp
	mov	edx, 2
	mov	esi, OFFSET FLAT:nice
	mov	edi, OFFSET FLAT:.LC9
	mov	QWORD PTR [rsp], rbx
	call	newProcessArgs
	jmp	.L4
	.p2align 4,,10
	.p2align 3
.L24:
	mov	rdi, rsp
	xor	eax, eax
	mov	ecx, 10
	rep stosq
	add	rbx, 5
	xor	r8d, r8d
	mov	rcx, rsp
	mov	edx, 1
	mov	esi, OFFSET FLAT:kill
	mov	edi, OFFSET FLAT:.LC7
	mov	QWORD PTR [rsp], rbx
	call	newProcessArgs
	jmp	.L4
	.p2align 4,,10
	.p2align 3
.L8:
	mov	edx, 6
	mov	esi, OFFSET FLAT:.LC10
	mov	rdi, rbx
	call	strncmp
	test	eax, eax
	jne	.L9
	mov	rdi, rsp
	xor	eax, eax
	mov	ecx, 10
	rep stosq
	add	rbx, 6
	xor	r8d, r8d
	mov	rcx, rsp
	mov	edx, 1
	mov	esi, OFFSET FLAT:block
	mov	edi, OFFSET FLAT:.LC11
	mov	QWORD PTR [rsp], rbx
	call	newProcessArgs
	jmp	.L4
.L9:
	mov	esi, OFFSET FLAT:.LC12
	mov	rdi, rbx
	call	strcmp
	test	eax, eax
	je	.L11
	mov	edi, OFFSET FLAT:.LC13
	xor	eax, eax
	call	printf
	jmp	.L11
	.cfi_endproc
.LFE3:
	.size	parse, .-parse
	.section	.text.unlikely
.LCOLDE14:
	.text
.LHOTE14:
	.section	.text.unlikely
.LCOLDB15:
	.text
.LHOTB15:
	.p2align 4,,15
	.globl	parseCommands
	.type	parseCommands, @function
parseCommands:
.LFB1:
	.cfi_startproc
	sub	rsp, 8
	.cfi_def_cfa_offset 16
	call	trim
	movzx	ecx, BYTE PTR [rax]
	test	cl, cl
	je	.L32
	lea	rdx, [rax+1]
	xor	esi, esi
	jmp	.L30
	.p2align 4,,10
	.p2align 3
.L28:
	movzx	ecx, BYTE PTR [rdx]
	add	rdx, 1
	test	cl, cl
	je	.L26
.L30:
	cmp	cl, 124
	mov	r8, rdx
	jne	.L28
	test	rsi, rsi
	jne	.L25
	movzx	ecx, BYTE PTR [rdx]
	mov	r8, rdx
	mov	rsi, rax
	mov	rax, rdx
	add	rdx, 1
	test	cl, cl
	jne	.L30
.L26:
	cmp	BYTE PTR [r8-1], 38
	sete	dl
	test	dl, dl
	movzx	esi, dl
	jne	.L38
	mov	rdi, rax
	add	rsp, 8
	.cfi_remember_state
	.cfi_def_cfa_offset 8
	jmp	parse
	.p2align 4,,10
	.p2align 3
.L38:
	.cfi_restore_state
	mov	BYTE PTR [r8-1], 0
	mov	rdi, rax
	add	rsp, 8
	.cfi_remember_state
	.cfi_def_cfa_offset 8
	jmp	parse
	.p2align 4,,10
	.p2align 3
.L25:
	.cfi_restore_state
	add	rsp, 8
	.cfi_remember_state
	.cfi_def_cfa_offset 8
	ret
.L32:
	.cfi_restore_state
	mov	r8, rax
	jmp	.L26
	.cfi_endproc
.LFE1:
	.size	parseCommands, .-parseCommands
	.section	.text.unlikely
.LCOLDE15:
	.text
.LHOTE15:
	.section	.rodata.str1.1
.LC16:
	.string	"\nUser $> "
	.section	.text.unlikely
.LCOLDB17:
	.text
.LHOTB17:
	.p2align 4,,15
	.globl	shell
	.type	shell, @function
shell:
.LFB0:
	.cfi_startproc
	push	rbx
	.cfi_def_cfa_offset 16
	.cfi_offset 3, -16
	mov	edi, 4096
	call	malloc
	mov	rbx, rax
	.p2align 4,,10
	.p2align 3
.L42:
	mov	edi, OFFSET FLAT:.LC16
	xor	eax, eax
	call	printf
	mov	rdi, rbx
	mov	edx, 10
	mov	esi, 4095
	call	scanf
	mov	rdi, rbx
	call	parseCommands
	jmp	.L42
	.cfi_endproc
.LFE0:
	.size	shell, .-shell
	.section	.text.unlikely
.LCOLDE17:
	.text
.LHOTE17:
	.ident	"GCC: (Debian 4.9.2-10+deb8u1) 4.9.2"
	.section	.note.GNU-stack,"",@progbits

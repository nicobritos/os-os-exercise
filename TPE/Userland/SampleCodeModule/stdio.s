	.file	"stdio.c"
	.intel_syntax noprefix
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"^D"
.LC1:
	.string	"^C"
	.section	.text.unlikely,"ax",@progbits
.LCOLDB2:
	.text
.LHOTB2:
	.p2align 4,,15
	.globl	putchar
	.type	putchar, @function
putchar:
.LFB0:
	.cfi_startproc
	sub	rsp, 24
	.cfi_def_cfa_offset 32
	cmp	dil, -1
	mov	BYTE PTR [rsp+12], dil
	je	.L7
	cmp	dil, 3
	je	.L8
	lea	rsi, [rsp+12]
	mov	edx, 1
	mov	edi, 1
	call	sys_write
.L1:
	add	rsp, 24
	.cfi_remember_state
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L8:
	.cfi_restore_state
	mov	edx, 2
	mov	esi, OFFSET FLAT:.LC1
	mov	edi, 1
	call	sys_write
	add	rsp, 24
	.cfi_remember_state
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L7:
	.cfi_restore_state
	mov	edx, 2
	mov	esi, OFFSET FLAT:.LC0
	mov	edi, 1
	call	sys_write
	jmp	.L1
	.cfi_endproc
.LFE0:
	.size	putchar, .-putchar
	.section	.text.unlikely
.LCOLDE2:
	.text
.LHOTE2:
	.section	.text.unlikely
.LCOLDB3:
	.text
.LHOTB3:
	.p2align 4,,15
	.globl	getchar
	.type	getchar, @function
getchar:
.LFB1:
	.cfi_startproc
	sub	rsp, 24
	.cfi_def_cfa_offset 32
	mov	BYTE PTR [rsp+15], 0
	jmp	.L10
	.p2align 4,,10
	.p2align 3
.L16:
	cmp	al, -1
	je	.L12
.L10:
	lea	rsi, [rsp+15]
	xor	edi, edi
	mov	edx, 1
	call	sys_read
	movsx	eax, BYTE PTR [rsp+15]
	test	al, al
	jle	.L16
.L12:
	add	rsp, 24
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE1:
	.size	getchar, .-getchar
	.section	.text.unlikely
.LCOLDE3:
	.text
.LHOTE3:
	.section	.text.unlikely
.LCOLDB4:
	.text
.LHOTB4:
	.p2align 4,,15
	.globl	getCharWithZero
	.type	getCharWithZero, @function
getCharWithZero:
.LFB2:
	.cfi_startproc
	sub	rsp, 24
	.cfi_def_cfa_offset 32
	mov	BYTE PTR [rsp+15], 0
	.p2align 4,,10
	.p2align 3
.L18:
	lea	rsi, [rsp+15]
	xor	edi, edi
	mov	edx, 1
	call	sys_read
	movzx	eax, BYTE PTR [rsp+15]
	cmp	al, -1
	jl	.L18
	add	rsp, 24
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE2:
	.size	getCharWithZero, .-getCharWithZero
	.section	.text.unlikely
.LCOLDE4:
	.text
.LHOTE4:
	.section	.text.unlikely
.LCOLDB5:
	.text
.LHOTB5:
	.p2align 4,,15
	.globl	printf
	.type	printf, @function
printf:
.LFB3:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	push	rbx
	.cfi_def_cfa_offset 24
	.cfi_offset 3, -24
	mov	rbx, rdi
	sub	rsp, 280
	.cfi_def_cfa_offset 304
	lea	rax, [rsp+304]
	mov	QWORD PTR [rsp+232], rsi
	mov	QWORD PTR [rsp+240], rdx
	mov	QWORD PTR [rsp+248], rcx
	mov	QWORD PTR [rsp+256], r8
	mov	QWORD PTR [rsp+8], rax
	lea	rax, [rsp+224]
	mov	QWORD PTR [rsp+264], r9
	mov	DWORD PTR [rsp], 8
	mov	QWORD PTR [rsp+16], rax
	movzx	eax, BYTE PTR [rdi]
	test	al, al
	je	.L46
	.p2align 4,,10
	.p2align 3
.L45:
	cmp	al, 37
	jne	.L23
	movzx	eax, BYTE PTR [rbx+1]
	lea	edx, [rax-99]
	cmp	dl, 21
	ja	.L24
	movzx	edx, dl
	jmp	[QWORD PTR .L26[0+rdx*8]]
	.section	.rodata
	.align 8
	.align 4
.L26:
	.quad	.L25
	.quad	.L27
	.quad	.L24
	.quad	.L24
	.quad	.L24
	.quad	.L24
	.quad	.L24
	.quad	.L24
	.quad	.L24
	.quad	.L28
	.quad	.L24
	.quad	.L24
	.quad	.L24
	.quad	.L24
	.quad	.L24
	.quad	.L24
	.quad	.L29
	.quad	.L24
	.quad	.L24
	.quad	.L24
	.quad	.L24
	.quad	.L30
	.text
	.p2align 4,,10
	.p2align 3
.L30:
	mov	eax, DWORD PTR [rsp]
	cmp	eax, 48
	jnb	.L37
	mov	ecx, eax
	add	rcx, QWORD PTR [rsp+16]
	add	eax, 8
	mov	DWORD PTR [rsp], eax
.L38:
	mov	edx, 16
	lea	rsi, [rsp+24]
	mov	edi, DWORD PTR [rcx]
	jmp	.L48
	.p2align 4,,10
	.p2align 3
.L29:
	mov	eax, DWORD PTR [rsp]
	cmp	eax, 48
	jnb	.L35
	mov	edx, eax
	add	rdx, QWORD PTR [rsp+16]
	add	eax, 8
	mov	DWORD PTR [rsp], eax
.L36:
	mov	rbp, QWORD PTR [rdx]
	add	rbx, 1
	mov	rdi, rbp
	call	strlen
	mov	rsi, rbp
	mov	edx, eax
	mov	edi, 1
	call	sys_write
	movzx	eax, BYTE PTR [rbx+1]
.L24:
	add	rbx, 1
	test	al, al
	jne	.L45
	.p2align 4,,10
	.p2align 3
.L46:
	add	rsp, 280
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
.L28:
	.cfi_restore_state
	mov	eax, DWORD PTR [rsp]
	cmp	eax, 48
	jnb	.L39
	mov	edx, eax
	add	rdx, QWORD PTR [rsp+16]
	add	eax, 8
	mov	DWORD PTR [rsp], eax
.L40:
	mov	rdi, QWORD PTR [rdx]
	lea	rsi, [rsp+24]
	mov	edx, 10
	jmp	.L48
	.p2align 4,,10
	.p2align 3
.L27:
	mov	eax, DWORD PTR [rsp]
	cmp	eax, 48
	jnb	.L31
	mov	ecx, eax
	add	rcx, QWORD PTR [rsp+16]
	add	eax, 8
	mov	DWORD PTR [rsp], eax
.L32:
	mov	edi, DWORD PTR [rcx]
	lea	rsi, [rsp+24]
	mov	edx, 10
.L48:
	call	itoa
	lea	rsi, [rsp+24]
	mov	edx, eax
	mov	edi, 1
	add	rbx, 1
	call	sys_write
	movzx	eax, BYTE PTR [rbx+1]
	add	rbx, 1
	test	al, al
	jne	.L45
	jmp	.L46
	.p2align 4,,10
	.p2align 3
.L25:
	mov	eax, DWORD PTR [rsp]
	cmp	eax, 48
	jnb	.L33
	mov	edx, eax
	add	rdx, QWORD PTR [rsp+16]
	add	eax, 8
	mov	DWORD PTR [rsp], eax
.L34:
	movsx	edi, BYTE PTR [rdx]
	add	rbx, 1
	call	putchar
	movzx	eax, BYTE PTR [rbx+1]
	add	rbx, 1
	test	al, al
	jne	.L45
	jmp	.L46
	.p2align 4,,10
	.p2align 3
.L23:
	movsx	edi, al
	add	rbx, 1
	call	putchar
	movzx	eax, BYTE PTR [rbx]
	test	al, al
	jne	.L45
	jmp	.L46
	.p2align 4,,10
	.p2align 3
.L33:
	mov	rdx, QWORD PTR [rsp+8]
	lea	rax, [rdx+8]
	mov	QWORD PTR [rsp+8], rax
	jmp	.L34
	.p2align 4,,10
	.p2align 3
.L31:
	mov	rcx, QWORD PTR [rsp+8]
	lea	rax, [rcx+8]
	mov	QWORD PTR [rsp+8], rax
	jmp	.L32
	.p2align 4,,10
	.p2align 3
.L39:
	mov	rdx, QWORD PTR [rsp+8]
	lea	rax, [rdx+8]
	mov	QWORD PTR [rsp+8], rax
	jmp	.L40
	.p2align 4,,10
	.p2align 3
.L35:
	mov	rdx, QWORD PTR [rsp+8]
	lea	rax, [rdx+8]
	mov	QWORD PTR [rsp+8], rax
	jmp	.L36
	.p2align 4,,10
	.p2align 3
.L37:
	mov	rcx, QWORD PTR [rsp+8]
	lea	rax, [rcx+8]
	mov	QWORD PTR [rsp+8], rax
	jmp	.L38
	.cfi_endproc
.LFE3:
	.size	printf, .-printf
	.section	.text.unlikely
.LCOLDE5:
	.text
.LHOTE5:
	.section	.text.unlikely
.LCOLDB6:
	.text
.LHOTB6:
	.p2align 4,,15
	.globl	scanf
	.type	scanf, @function
scanf:
.LFB4:
	.cfi_startproc
	push	r14
	.cfi_def_cfa_offset 16
	.cfi_offset 14, -16
	push	r13
	.cfi_def_cfa_offset 24
	.cfi_offset 13, -24
	mov	r14, rdi
	push	r12
	.cfi_def_cfa_offset 32
	.cfi_offset 12, -32
	lea	r12d, [rsi-1]
	push	rbp
	.cfi_def_cfa_offset 40
	.cfi_offset 6, -40
	mov	r13d, edx
	push	rbx
	.cfi_def_cfa_offset 48
	.cfi_offset 3, -48
	xor	ebx, ebx
	.p2align 4,,10
	.p2align 3
.L50:
	xor	eax, eax
	call	getchar
	cmp	eax, r13d
	mov	ebp, eax
	je	.L56
.L60:
	cmp	ebx, r12d
	jge	.L56
	cmp	ebp, 8
	jne	.L51
	test	ebx, ebx
	jle	.L50
	movsx	rax, ebx
	movzx	eax, BYTE PTR [r14-1+rax]
	add	eax, 1
	test	al, -5
	je	.L59
.L53:
	mov	edi, 8
	sub	ebx, 1
	call	putchar
	xor	eax, eax
	call	getchar
	cmp	eax, r13d
	mov	ebp, eax
	jne	.L60
	.p2align 4,,10
	.p2align 3
.L56:
	movsx	rax, ebx
	mov	BYTE PTR [r14+rax], 0
	mov	eax, ebx
	pop	rbx
	.cfi_remember_state
	.cfi_restore 3
	.cfi_def_cfa_offset 40
	pop	rbp
	.cfi_restore 6
	.cfi_def_cfa_offset 32
	pop	r12
	.cfi_restore 12
	.cfi_def_cfa_offset 24
	pop	r13
	.cfi_restore 13
	.cfi_def_cfa_offset 16
	pop	r14
	.cfi_restore 14
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L51:
	.cfi_restore_state
	movsx	edi, bpl
	call	putchar
	movsx	rax, ebx
	add	ebx, 1
	mov	BYTE PTR [r14+rax], bpl
	jmp	.L50
	.p2align 4,,10
	.p2align 3
.L59:
	mov	edi, 8
	call	putchar
	jmp	.L53
	.cfi_endproc
.LFE4:
	.size	scanf, .-scanf
	.section	.text.unlikely
.LCOLDE6:
	.text
.LHOTE6:
	.ident	"GCC: (Debian 4.9.2-10+deb8u1) 4.9.2"
	.section	.note.GNU-stack,"",@progbits

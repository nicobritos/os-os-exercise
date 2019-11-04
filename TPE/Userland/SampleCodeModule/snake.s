	.file	"snake.c"
	.intel_syntax noprefix
	.section	.text.unlikely,"ax",@progbits
.LCOLDB0:
	.text
.LHOTB0:
	.p2align 4,,15
	.type	incrementSize.part.0, @function
incrementSize.part.0:
.LFB17:
	.cfi_startproc
	mov	DWORD PTR count[rip], 0
	add	DWORD PTR snake_size[rip], 1
	add	DWORD PTR totalScore[rip], 1
	ret
	.cfi_endproc
.LFE17:
	.size	incrementSize.part.0, .-incrementSize.part.0
	.section	.text.unlikely
.LCOLDE0:
	.text
.LHOTE0:
	.section	.text.unlikely
.LCOLDB1:
	.text
.LHOTB1:
	.p2align 4,,15
	.globl	drawPixel
	.type	drawPixel, @function
drawPixel:
.LFB0:
	.cfi_startproc
	jmp	sys_draw
	.cfi_endproc
.LFE0:
	.size	drawPixel, .-drawPixel
	.section	.text.unlikely
.LCOLDE1:
	.text
.LHOTE1:
	.section	.text.unlikely
.LCOLDB2:
	.text
.LHOTB2:
	.p2align 4,,15
	.globl	drawWindow
	.type	drawWindow, @function
drawWindow:
.LFB1:
	.cfi_startproc
	push	r15
	.cfi_def_cfa_offset 16
	.cfi_offset 15, -16
	push	r14
	.cfi_def_cfa_offset 24
	.cfi_offset 14, -24
	lea	rax, [rdi+rdx]
	push	r13
	.cfi_def_cfa_offset 32
	.cfi_offset 13, -32
	push	r12
	.cfi_def_cfa_offset 40
	.cfi_offset 12, -40
	push	rbp
	.cfi_def_cfa_offset 48
	.cfi_offset 6, -48
	push	rbx
	.cfi_def_cfa_offset 56
	.cfi_offset 3, -56
	mov	rdx, rax
	lea	rbx, [rsi+rcx]
	sub	rsp, 56
	.cfi_def_cfa_offset 112
	mov	QWORD PTR [rsp+24], rax
	movsx	rax, esi
	mov	QWORD PTR [rsp+32], r8
	mov	r10, rax
	mov	QWORD PTR [rsp+16], rax
	movsx	rax, edi
	cmp	rax, rdx
	mov	QWORD PTR [rsp+8], rax
	jnb	.L3
	mov	ecx, edi
	mov	r15d, DWORD PTR [rsp+112]
	mov	r13d, esi
	sub	ecx, eax
	mov	DWORD PTR [rsp+40], r9d
	sub	r13d, r10d
	mov	DWORD PTR [rsp+44], ecx
	.p2align 4,,10
	.p2align 3
.L10:
	mov	rax, QWORD PTR [rsp+16]
	mov	r12d, DWORD PTR [rsp+44]
	add	r12d, DWORD PTR [rsp+8]
	mov	ebp, DWORD PTR [rsp+32]
	cmp	rbx, rax
	mov	r14, rax
	jbe	.L9
	.p2align 4,,10
	.p2align 3
.L8:
	mov	ecx, DWORD PTR [rsp+40]
	lea	esi, [r13+0+r14]
	mov	r8d, r15d
	mov	edx, ebp
	mov	edi, r12d
	add	r14, 1
	call	sys_draw
	cmp	rbx, r14
	ja	.L8
.L9:
	add	QWORD PTR [rsp+8], 1
	mov	rax, QWORD PTR [rsp+8]
	cmp	rax, QWORD PTR [rsp+24]
	jb	.L10
.L3:
	add	rsp, 56
	.cfi_def_cfa_offset 56
	pop	rbx
	.cfi_restore 3
	.cfi_def_cfa_offset 48
	pop	rbp
	.cfi_restore 6
	.cfi_def_cfa_offset 40
	pop	r12
	.cfi_restore 12
	.cfi_def_cfa_offset 32
	pop	r13
	.cfi_restore 13
	.cfi_def_cfa_offset 24
	pop	r14
	.cfi_restore 14
	.cfi_def_cfa_offset 16
	pop	r15
	.cfi_restore 15
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE1:
	.size	drawWindow, .-drawWindow
	.section	.text.unlikely
.LCOLDE2:
	.text
.LHOTE2:
	.section	.text.unlikely
.LCOLDB3:
	.text
.LHOTB3:
	.p2align 4,,15
	.globl	delete
	.type	delete, @function
delete:
.LFB2:
	.cfi_startproc
	push	r15
	.cfi_def_cfa_offset 16
	.cfi_offset 15, -16
	lea	rax, [rdi+rdx]
	push	r14
	.cfi_def_cfa_offset 24
	.cfi_offset 14, -24
	push	r13
	.cfi_def_cfa_offset 32
	.cfi_offset 13, -32
	push	r12
	.cfi_def_cfa_offset 40
	.cfi_offset 12, -40
	movsx	r12, edi
	push	rbp
	.cfi_def_cfa_offset 48
	.cfi_offset 6, -48
	push	rbx
	.cfi_def_cfa_offset 56
	.cfi_offset 3, -56
	sub	rsp, 24
	.cfi_def_cfa_offset 80
	cmp	r12, rax
	mov	QWORD PTR [rsp], rax
	jnb	.L16
	mov	eax, edi
	lea	rbx, [rsi+rcx]
	mov	DWORD PTR [rsp+8], esi
	sub	eax, r12d
	movsx	r13, esi
	mov	DWORD PTR [rsp+12], eax
	.p2align 4,,10
	.p2align 3
.L19:
	mov	eax, DWORD PTR [rsp+12]
	cmp	rbx, r13
	mov	r14, r13
	mov	r15d, DWORD PTR [rsp+8]
	lea	ebp, [rax+r12]
	jbe	.L21
	.p2align 4,,10
	.p2align 3
.L23:
	xor	r8d, r8d
	xor	ecx, ecx
	xor	edx, edx
	mov	esi, r15d
	mov	edi, ebp
	add	r14, 1
	call	sys_draw
	add	r15d, 1
	cmp	rbx, r14
	ja	.L23
.L21:
	add	r12, 1
	cmp	r12, QWORD PTR [rsp]
	jb	.L19
.L16:
	add	rsp, 24
	.cfi_def_cfa_offset 56
	pop	rbx
	.cfi_restore 3
	.cfi_def_cfa_offset 48
	pop	rbp
	.cfi_restore 6
	.cfi_def_cfa_offset 40
	pop	r12
	.cfi_restore 12
	.cfi_def_cfa_offset 32
	pop	r13
	.cfi_restore 13
	.cfi_def_cfa_offset 24
	pop	r14
	.cfi_restore 14
	.cfi_def_cfa_offset 16
	pop	r15
	.cfi_restore 15
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE2:
	.size	delete, .-delete
	.section	.text.unlikely
.LCOLDE3:
	.text
.LHOTE3:
	.section	.text.unlikely
.LCOLDB4:
	.text
.LHOTB4:
	.p2align 4,,15
	.globl	printSnake
	.type	printSnake, @function
printSnake:
.LFB3:
	.cfi_startproc
	mov	eax, DWORD PTR snake_size[rip]
	push	r12
	.cfi_def_cfa_offset 16
	.cfi_offset 12, -16
	push	rbp
	.cfi_def_cfa_offset 24
	.cfi_offset 6, -24
	push	rbx
	.cfi_def_cfa_offset 32
	.cfi_offset 3, -32
	sub	eax, 1
	cdqe
	sal	rax, 5
	mov	rdx, QWORD PTR snake[rax+24]
	mov	rsi, QWORD PTR snake[rax+8]
	lea	rcx, [rax+16]
	mov	rdi, QWORD PTR snake[rax]
	lea	rdx, [rdx+rdx*4]
	sal	rdx, 2
	sub	rsi, rdx
	mov	rdx, QWORD PTR snake[rcx]
	mov	ecx, 20
	lea	rdx, [rdx+rdx*4]
	sal	rdx, 2
	sub	rdi, rdx
	mov	edx, 20
	call	delete
	sub	rsp, 8
	.cfi_def_cfa_offset 40
	mov	rsi, QWORD PTR snake[rip+8]
	mov	rdi, QWORD PTR snake[rip]
	push	170
	.cfi_def_cfa_offset 48
	xor	r8d, r8d
	mov	ecx, 20
	mov	r9d, 170
	mov	edx, 20
	call	drawWindow
	cmp	DWORD PTR snake_size[rip], 1
	pop	rcx
	.cfi_def_cfa_offset 40
	pop	rsi
	.cfi_def_cfa_offset 32
	jle	.L27
	mov	ebp, OFFSET FLAT:snake+8
	mov	ebx, 40
	mov	r12d, 1
	.p2align 4,,10
	.p2align 3
.L29:
	movsx	rax, ebx
	mov	edx, ebx
	mov	rsi, QWORD PTR [rbp+0]
	imul	rax, rax, -2139062143
	sar	edx, 31
	mov	rdi, QWORD PTR [rbp-8]
	sub	rsp, 8
	.cfi_def_cfa_offset 40
	mov	r9d, ebx
	xor	r8d, r8d
	mov	ecx, 20
	add	r12d, 1
	add	rbp, 32
	shr	rax, 32
	add	eax, ebx
	add	ebx, 40
	sar	eax, 7
	sub	eax, edx
	mov	edx, eax
	sal	edx, 8
	sub	edx, eax
	mov	rax, QWORD PTR [rbp-16]
	sub	r9d, edx
	mov	edx, 20
	movsx	r9, r9d
	lea	rax, [rax+rax*4]
	sal	rax, 2
	sub	rsi, rax
	mov	rax, QWORD PTR [rbp-24]
	push	170
	.cfi_def_cfa_offset 48
	lea	rax, [rax+rax*4]
	sal	rax, 2
	sub	rdi, rax
	call	drawWindow
	cmp	DWORD PTR snake_size[rip], r12d
	pop	rax
	.cfi_def_cfa_offset 40
	pop	rdx
	.cfi_def_cfa_offset 32
	jg	.L29
.L27:
	pop	rbx
	.cfi_restore 3
	.cfi_def_cfa_offset 24
	pop	rbp
	.cfi_restore 6
	.cfi_def_cfa_offset 16
	pop	r12
	.cfi_restore 12
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE3:
	.size	printSnake, .-printSnake
	.section	.text.unlikely
.LCOLDE4:
	.text
.LHOTE4:
	.section	.text.unlikely
.LCOLDB5:
	.text
.LHOTB5:
	.p2align 4,,15
	.globl	setupSnake
	.type	setupSnake, @function
setupSnake:
.LFB5:
	.cfi_startproc
	mov	ecx, DWORD PTR snake_size[rip]
	mov	QWORD PTR snake[rip], 492
	mov	QWORD PTR snake[rip+8], 364
	test	ecx, ecx
	jle	.L43
	lea	edx, [rcx-1]
	mov	eax, OFFSET FLAT:snake+16
	sal	rdx, 5
	add	rdx, OFFSET FLAT:snake+48
	.p2align 4,,10
	.p2align 3
.L37:
	mov	QWORD PTR [rax], 1
	mov	QWORD PTR [rax+8], 0
	add	rax, 32
	cmp	rax, rdx
	jne	.L37
	cmp	ecx, 1
	jle	.L44
	sub	ecx, 2
	mov	edx, OFFSET FLAT:snake+32
	mov	eax, 492
	sal	rcx, 5
	add	rcx, OFFSET FLAT:snake+32
	jmp	.L39
	.p2align 4,,10
	.p2align 3
.L45:
	add	rdx, 32
.L39:
	sub	rax, 20
	cmp	rdx, rcx
	mov	QWORD PTR [rdx+8], 364
	mov	QWORD PTR [rdx], rax
	jne	.L45
	rep ret
.L43:
	rep ret
.L44:
	ret
	.cfi_endproc
.LFE5:
	.size	setupSnake, .-setupSnake
	.section	.text.unlikely
.LCOLDE5:
	.text
.LHOTE5:
	.section	.text.unlikely
.LCOLDB6:
	.text
.LHOTB6:
	.p2align 4,,15
	.globl	incrementSize
	.type	incrementSize, @function
incrementSize:
.LFB8:
	.cfi_startproc
	cmp	DWORD PTR count[rip], 5
	je	.L48
	rep ret
	.p2align 4,,10
	.p2align 3
.L48:
	xor	eax, eax
	jmp	incrementSize.part.0
	.cfi_endproc
.LFE8:
	.size	incrementSize, .-incrementSize
	.section	.text.unlikely
.LCOLDE6:
	.text
.LHOTE6:
	.section	.text.unlikely
.LCOLDB7:
	.text
.LHOTB7:
	.p2align 4,,15
	.globl	increaseSize
	.type	increaseSize, @function
increaseSize:
.LFB10:
	.cfi_startproc
	mov	edx, edi
	sub	edx, DWORD PTR ticks_to_bigger[rip]
	xor	eax, eax
	cmp	edx, DWORD PTR play_seconds[rip]
	jl	.L50
	mov	DWORD PTR play_seconds[rip], edi
	mov	al, 1
.L50:
	rep ret
	.cfi_endproc
.LFE10:
	.size	increaseSize, .-increaseSize
	.section	.text.unlikely
.LCOLDE7:
	.text
.LHOTE7:
	.section	.text.unlikely
.LCOLDB8:
	.text
.LHOTB8:
	.p2align 4,,15
	.globl	getseconds
	.type	getseconds, @function
getseconds:
.LFB13:
	.cfi_startproc
	sub	rsp, 56
	.cfi_def_cfa_offset 64
	mov	rdi, rsp
	call	sys_time
	mov	rax, QWORD PTR [rsp]
	add	rax, QWORD PTR [rsp+8]
	mov	rdx, QWORD PTR [rsp+40]
	add	edx, DWORD PTR [rsp+32]
	imul	eax, eax, 3600
	lea	edx, [rdx-1933008+rax]
	mov	rax, QWORD PTR [rsp+16]
	add	rax, QWORD PTR [rsp+24]
	add	rsp, 56
	.cfi_def_cfa_offset 8
	imul	eax, eax, 60
	add	eax, edx
	ret
	.cfi_endproc
.LFE13:
	.size	getseconds, .-getseconds
	.section	.text.unlikely
.LCOLDE8:
	.text
.LHOTE8:
	.section	.text.unlikely
.LCOLDB9:
	.text
.LHOTB9:
	.p2align 4,,15
	.globl	drawChar
	.type	drawChar, @function
drawChar:
.LFB15:
	.cfi_startproc
	push	r15
	.cfi_def_cfa_offset 16
	.cfi_offset 15, -16
	push	r14
	.cfi_def_cfa_offset 24
	.cfi_offset 14, -24
	movzx	eax, dl
	push	r13
	.cfi_def_cfa_offset 32
	.cfi_offset 13, -32
	push	r12
	.cfi_def_cfa_offset 40
	.cfi_offset 12, -40
	sal	rax, 3
	push	rbp
	.cfi_def_cfa_offset 48
	.cfi_offset 6, -48
	push	rbx
	.cfi_def_cfa_offset 56
	.cfi_offset 3, -56
	lea	rdx, fonts[rax]
	add	rax, OFFSET FLAT:fonts+8
	movzx	r14d, r8b
	movzx	r15d, cl
	sub	rsp, 72
	.cfi_def_cfa_offset 128
	mov	DWORD PTR [rsp+60], edi
	mov	edi, DWORD PTR [rsp+128]
	mov	QWORD PTR [rsp+32], rdx
	mov	QWORD PTR [rsp+48], rax
	movzx	eax, r9b
	mov	DWORD PTR [rsp+44], esi
	mov	DWORD PTR [rsp+12], eax
	movzx	edx, dil
	mov	DWORD PTR [rsp+56], edx
	mov	r12d, edx
.L55:
	mov	eax, DWORD PTR [rsp+60]
	mov	DWORD PTR [rsp+28], 0
	mov	DWORD PTR [rsp+40], eax
	mov	eax, DWORD PTR [rsp+44]
	add	eax, 1
	mov	DWORD PTR [rsp+24], eax
	.p2align 4,,10
	.p2align 3
.L57:
	mov	rax, QWORD PTR [rsp+32]
	mov	ecx, DWORD PTR [rsp+28]
	movsx	eax, BYTE PTR [rax]
	bt	eax, ecx
	jnc	.L60
	mov	eax, DWORD PTR [rsp+40]
	test	r12d, r12d
	mov	QWORD PTR [rsp+16], 0
	lea	ebp, [rax+1]
	je	.L60
	.p2align 4,,10
	.p2align 3
.L62:
	mov	ebx, DWORD PTR [rsp+24]
	add	ebx, DWORD PTR [rsp+16]
	xor	r13d, r13d
	.p2align 4,,10
	.p2align 3
.L61:
	mov	r8d, DWORD PTR [rsp+12]
	lea	edi, [rbp+0+r13]
	mov	ecx, r14d
	add	r13, 1
	mov	edx, r15d
	mov	esi, ebx
	call	sys_draw
	lea	eax, [r13+1]
	cmp	eax, r12d
	jle	.L61
	add	QWORD PTR [rsp+16], 1
	mov	rax, QWORD PTR [rsp+16]
	add	eax, 1
	cmp	eax, r12d
	jle	.L62
.L60:
	add	DWORD PTR [rsp+28], 1
	add	DWORD PTR [rsp+40], r12d
	mov	eax, DWORD PTR [rsp+28]
	cmp	eax, 8
	jne	.L57
	add	QWORD PTR [rsp+32], 1
	mov	ecx, DWORD PTR [rsp+56]
	mov	rax, QWORD PTR [rsp+32]
	add	DWORD PTR [rsp+44], ecx
	cmp	rax, QWORD PTR [rsp+48]
	jne	.L55
	add	rsp, 72
	.cfi_def_cfa_offset 56
	pop	rbx
	.cfi_restore 3
	.cfi_def_cfa_offset 48
	pop	rbp
	.cfi_restore 6
	.cfi_def_cfa_offset 40
	pop	r12
	.cfi_restore 12
	.cfi_def_cfa_offset 32
	pop	r13
	.cfi_restore 13
	.cfi_def_cfa_offset 24
	pop	r14
	.cfi_restore 14
	.cfi_def_cfa_offset 16
	pop	r15
	.cfi_restore 15
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE15:
	.size	drawChar, .-drawChar
	.section	.text.unlikely
.LCOLDE9:
	.text
.LHOTE9:
	.section	.text.unlikely
.LCOLDB10:
	.text
.LHOTB10:
	.p2align 4,,15
	.globl	drawString
	.type	drawString, @function
drawString:
.LFB16:
	.cfi_startproc
	push	r15
	.cfi_def_cfa_offset 16
	.cfi_offset 15, -16
	push	r14
	.cfi_def_cfa_offset 24
	.cfi_offset 14, -24
	mov	r15d, edi
	push	r13
	.cfi_def_cfa_offset 32
	.cfi_offset 13, -32
	push	r12
	.cfi_def_cfa_offset 40
	.cfi_offset 12, -40
	mov	rdi, rdx
	push	rbp
	.cfi_def_cfa_offset 48
	.cfi_offset 6, -48
	push	rbx
	.cfi_def_cfa_offset 56
	.cfi_offset 3, -56
	mov	r14d, esi
	mov	ebp, ecx
	mov	r12d, r8d
	mov	r13d, r9d
	sub	rsp, 24
	.cfi_def_cfa_offset 80
	mov	ebx, DWORD PTR [rsp+80]
	mov	QWORD PTR [rsp], rdx
	call	strlen
	cdqe
	test	rax, rax
	je	.L71
	mov	rdx, QWORD PTR [rsp]
	movzx	ebx, bl
	movzx	ecx, bpl
	lea	esi, [0+rbx*8]
	movzx	r13d, r13b
	movzx	r12d, r12b
	mov	DWORD PTR [rsp+8], ecx
	add	rax, rdx
	mov	DWORD PTR [rsp+12], esi
	mov	rbp, rdx
	mov	QWORD PTR [rsp], rax
	.p2align 4,,10
	.p2align 3
.L73:
	sub	rsp, 8
	.cfi_def_cfa_offset 88
	movzx	edx, BYTE PTR [rbp+0]
	mov	edi, r15d
	push	rbx
	.cfi_def_cfa_offset 96
	mov	ecx, DWORD PTR [rsp+24]
	mov	r9d, r13d
	mov	r8d, r12d
	mov	esi, r14d
	add	rbp, 1
	call	drawChar
	add	r15d, DWORD PTR [rsp+28]
	pop	rax
	.cfi_def_cfa_offset 88
	pop	rdx
	.cfi_def_cfa_offset 80
	cmp	rbp, QWORD PTR [rsp]
	jne	.L73
.L71:
	add	rsp, 24
	.cfi_def_cfa_offset 56
	pop	rbx
	.cfi_restore 3
	.cfi_def_cfa_offset 48
	pop	rbp
	.cfi_restore 6
	.cfi_def_cfa_offset 40
	pop	r12
	.cfi_restore 12
	.cfi_def_cfa_offset 32
	pop	r13
	.cfi_restore 13
	.cfi_def_cfa_offset 24
	pop	r14
	.cfi_restore 14
	.cfi_def_cfa_offset 16
	pop	r15
	.cfi_restore 15
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE16:
	.size	drawString, .-drawString
	.section	.text.unlikely
.LCOLDE10:
	.text
.LHOTE10:
	.section	.text.unlikely
.LCOLDB11:
	.text
.LHOTB11:
	.p2align 4,,15
	.globl	window
	.type	window, @function
window:
.LFB4:
	.cfi_startproc
	sub	rsp, 16
	.cfi_def_cfa_offset 24
	mov	r9d, 255
	mov	r8d, 255
	push	255
	.cfi_def_cfa_offset 32
	mov	ecx, 20
	mov	edx, 1024
	mov	esi, 20
	mov	edi, 20
	call	drawWindow
	mov	r9d, 255
	mov	r8d, 255
	mov	ecx, 20
	mov	edx, 1024
	mov	esi, 748
	xor	edi, edi
	mov	QWORD PTR [rsp], 255
	call	drawWindow
	mov	r9d, 255
	mov	r8d, 255
	mov	ecx, 768
	mov	edx, 20
	mov	esi, 20
	xor	edi, edi
	mov	QWORD PTR [rsp], 255
	call	drawWindow
	mov	r9d, 255
	mov	r8d, 255
	mov	ecx, 768
	mov	edx, 20
	mov	esi, 20
	mov	edi, 1004
	mov	QWORD PTR [rsp], 255
	call	drawWindow
	xor	r9d, r9d
	mov	r8d, 255
	xor	ecx, ecx
	mov	edx, OFFSET FLAT:start_message
	mov	esi, 164
	mov	edi, 292
	mov	DWORD PTR [rsp], 2
	call	drawString
	xor	r9d, r9d
	mov	r8d, 255
	xor	ecx, ecx
	mov	edx, OFFSET FLAT:commands
	mov	esi, 264
	mov	edi, 292
	mov	DWORD PTR [rsp], 2
	call	drawString
	add	rsp, 24
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE4:
	.size	window, .-window
	.section	.text.unlikely
.LCOLDE11:
	.text
.LHOTE11:
	.section	.text.unlikely
.LCOLDB12:
	.text
.LHOTB12:
	.p2align 4,,15
	.globl	start
	.type	start, @function
start:
.LFB6:
	.cfi_startproc
	sub	rsp, 8
	.cfi_def_cfa_offset 16
	xor	eax, eax
	mov	DWORD PTR snake_size[rip], 5
	call	sys_clear
	xor	eax, eax
	call	setupSnake
	xor	eax, eax
	add	rsp, 8
	.cfi_def_cfa_offset 8
	jmp	window
	.cfi_endproc
.LFE6:
	.size	start, .-start
	.section	.text.unlikely
.LCOLDE12:
	.text
.LHOTE12:
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC13:
	.string	"GAME OVER"
.LC14:
	.string	"Score : "
	.section	.text.unlikely
.LCOLDB15:
	.text
.LHOTB15:
	.p2align 4,,15
	.globl	gameOver
	.type	gameOver, @function
gameOver:
.LFB7:
	.cfi_startproc
	sub	rsp, 48
	.cfi_def_cfa_offset 56
	xor	r9d, r9d
	xor	r8d, r8d
	push	5
	.cfi_def_cfa_offset 64
	mov	ecx, 255
	mov	edx, OFFSET FLAT:.LC13
	mov	esi, 184
	mov	edi, 112
	call	drawString
	xor	r9d, r9d
	xor	r8d, r8d
	mov	ecx, 255
	mov	edx, OFFSET FLAT:.LC14
	mov	esi, 284
	mov	edi, 112
	mov	DWORD PTR [rsp], 5
	call	drawString
	mov	edi, DWORD PTR totalScore[rip]
	lea	rsi, [rsp+18]
	mov	edx, 10
	call	itoa
	lea	rdx, [rsp+18]
	xor	r9d, r9d
	xor	r8d, r8d
	mov	ecx, 255
	mov	esi, 284
	mov	edi, 462
	mov	DWORD PTR [rsp], 5
	call	drawString
	add	rsp, 56
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE7:
	.size	gameOver, .-gameOver
	.section	.text.unlikely
.LCOLDE15:
	.text
.LHOTE15:
	.section	.text.unlikely
.LCOLDB16:
	.text
.LHOTB16:
	.p2align 4,,15
	.globl	move
	.type	move, @function
move:
.LFB9:
	.cfi_startproc
	push	rbx
	.cfi_def_cfa_offset 16
	.cfi_offset 3, -16
.L120:
	xor	eax, eax
	call	getCharWithZero
	test	al, al
	mov	ebx, eax
	je	.L123
	mov	eax, DWORD PTR count[rip]
	add	eax, 1
	cmp	eax, 5
	mov	DWORD PTR count[rip], eax
	je	.L124
.L85:
	mov	eax, DWORD PTR snake_size[rip]
	lea	edx, [rax-1]
	test	edx, edx
	jle	.L94
	.p2align 4,,10
	.p2align 3
.L115:
	lea	esi, [rdx-1]
	movsx	rdx, edx
	sal	rdx, 5
	movsx	rcx, esi
	add	rdx, 16
	sal	rcx, 5
	mov	rdi, QWORD PTR snake[rcx]
	add	rcx, 16
	mov	QWORD PTR snake[rdx-16], rdi
	mov	rdi, QWORD PTR snake[rcx-8]
	mov	QWORD PTR snake[rdx-8], rdi
	mov	rdi, QWORD PTR snake[rcx]
	test	esi, esi
	mov	rcx, QWORD PTR snake[rcx+8]
	mov	QWORD PTR snake[rdx], rdi
	mov	QWORD PTR snake[rdx+8], rcx
	mov	edx, esi
	jne	.L115
.L94:
	sub	ebx, 65
	cmp	bl, 54
	ja	.L87
	movzx	ebx, bl
	jmp	[QWORD PTR .L89[0+rbx*8]]
	.section	.rodata
	.align 8
	.align 4
.L89:
	.quad	.L88
	.quad	.L87
	.quad	.L87
	.quad	.L90
	.quad	.L87
	.quad	.L87
	.quad	.L87
	.quad	.L87
	.quad	.L87
	.quad	.L87
	.quad	.L87
	.quad	.L87
	.quad	.L87
	.quad	.L87
	.quad	.L87
	.quad	.L87
	.quad	.L87
	.quad	.L87
	.quad	.L91
	.quad	.L87
	.quad	.L87
	.quad	.L87
	.quad	.L92
	.quad	.L87
	.quad	.L87
	.quad	.L87
	.quad	.L87
	.quad	.L87
	.quad	.L87
	.quad	.L87
	.quad	.L87
	.quad	.L87
	.quad	.L88
	.quad	.L87
	.quad	.L87
	.quad	.L90
	.quad	.L87
	.quad	.L87
	.quad	.L87
	.quad	.L87
	.quad	.L87
	.quad	.L87
	.quad	.L87
	.quad	.L87
	.quad	.L87
	.quad	.L87
	.quad	.L87
	.quad	.L87
	.quad	.L87
	.quad	.L87
	.quad	.L91
	.quad	.L87
	.quad	.L87
	.quad	.L87
	.quad	.L92
	.text
.L92:
	cmp	QWORD PTR snake[rip+24], 1
	je	.L125
	mov	QWORD PTR snake[rip+16], 0
	mov	QWORD PTR snake[rip+24], -1
	mov	rax, -20
	xor	edx, edx
	.p2align 4,,10
	.p2align 3
.L95:
	add	QWORD PTR snake[rip+8], rax
	xor	eax, eax
	add	QWORD PTR snake[rip], rdx
	call	printSnake
	mov	rdx, QWORD PTR snake[rip]
	lea	rax, [rdx-31]
	cmp	rax, 952
	ja	.L104
	mov	rsi, QWORD PTR snake[rip+8]
	lea	rax, [rsi-41]
	cmp	rax, 696
	ja	.L104
	mov	ecx, DWORD PTR snake_size[rip]
	cmp	ecx, 1
	jle	.L120
	sub	ecx, 2
	mov	eax, OFFSET FLAT:snake+32
	sal	rcx, 5
	add	rcx, OFFSET FLAT:snake+64
	jmp	.L105
	.p2align 4,,10
	.p2align 3
.L103:
	add	rax, 32
	cmp	rax, rcx
	je	.L120
.L105:
	cmp	rdx, QWORD PTR [rax]
	jne	.L103
	cmp	rsi, QWORD PTR [rax+8]
	jne	.L103
.L104:
	xor	eax, eax
	call	gameOver
	mov	eax, 1
	pop	rbx
	.cfi_remember_state
	.cfi_restore 3
	.cfi_def_cfa_offset 8
	ret
.L91:
	.cfi_restore_state
	cmp	QWORD PTR snake[rip+24], -1
	je	.L126
	mov	QWORD PTR snake[rip+16], 0
	mov	QWORD PTR snake[rip+24], 1
	mov	eax, 20
	xor	edx, edx
	jmp	.L95
.L90:
	cmp	QWORD PTR snake[rip+16], -1
	je	.L127
	mov	QWORD PTR snake[rip+16], 1
	mov	QWORD PTR snake[rip+24], 0
	xor	eax, eax
	mov	edx, 20
	jmp	.L95
.L88:
	cmp	QWORD PTR snake[rip+16], 1
	je	.L128
	mov	QWORD PTR snake[rip+16], -1
	mov	QWORD PTR snake[rip+24], 0
	xor	eax, eax
	mov	rdx, -20
	jmp	.L95
.L87:
	mov	rax, QWORD PTR snake[rip+16]
	lea	rdx, [rax+rax*4]
	mov	rax, QWORD PTR snake[rip+24]
	sal	rdx, 2
	lea	rax, [rax+rax*4]
	sal	rax, 2
	jmp	.L95
.L124:
	xor	eax, eax
	call	incrementSize.part.0
	jmp	.L85
.L125:
	mov	rax, QWORD PTR snake[rip+16]
	lea	rdx, [rax+rax*4]
	mov	eax, 20
	sal	rdx, 2
	jmp	.L95
.L128:
	mov	rax, QWORD PTR snake[rip+24]
	mov	edx, 20
	lea	rax, [rax+rax*4]
	sal	rax, 2
	jmp	.L95
.L127:
	mov	rax, QWORD PTR snake[rip+24]
	mov	rdx, -20
	lea	rax, [rax+rax*4]
	sal	rax, 2
	jmp	.L95
.L126:
	mov	rax, QWORD PTR snake[rip+16]
	lea	rdx, [rax+rax*4]
	mov	rax, -20
	sal	rdx, 2
	jmp	.L95
.L123:
	mov	eax, DWORD PTR snake_size[rip]
	sub	eax, 1
	test	eax, eax
	jle	.L110
	.p2align 4,,10
	.p2align 3
.L114:
	lea	ecx, [rax-1]
	cdqe
	sal	rax, 5
	movsx	rdx, ecx
	add	rax, 16
	sal	rdx, 5
	mov	rsi, QWORD PTR snake[rdx]
	add	rdx, 16
	mov	QWORD PTR snake[rax-16], rsi
	mov	rsi, QWORD PTR snake[rdx-8]
	mov	QWORD PTR snake[rax-8], rsi
	mov	rsi, QWORD PTR snake[rdx]
	test	ecx, ecx
	mov	rdx, QWORD PTR snake[rdx+8]
	mov	QWORD PTR snake[rax], rsi
	mov	QWORD PTR snake[rax+8], rdx
	mov	eax, ecx
	jne	.L114
.L110:
	mov	rax, QWORD PTR snake[rip+16]
	lea	rax, [rax+rax*4]
	sal	rax, 2
	add	QWORD PTR snake[rip], rax
	mov	rax, QWORD PTR snake[rip+24]
	lea	rax, [rax+rax*4]
	sal	rax, 2
	add	QWORD PTR snake[rip+8], rax
	xor	eax, eax
	call	printSnake
	mov	rcx, QWORD PTR snake[rip]
	lea	rax, [rcx-31]
	cmp	rax, 952
	ja	.L104
	mov	rsi, QWORD PTR snake[rip+8]
	lea	rax, [rsi-41]
	cmp	rax, 696
	ja	.L104
	mov	eax, DWORD PTR snake_size[rip]
	cmp	eax, 1
	jle	.L113
	sub	eax, 2
	mov	edx, OFFSET FLAT:snake+32
	sal	rax, 5
	add	rax, OFFSET FLAT:snake+64
	jmp	.L112
.L111:
	add	rdx, 32
	cmp	rdx, rax
	je	.L113
.L112:
	cmp	rcx, QWORD PTR [rdx]
	jne	.L111
	cmp	rsi, QWORD PTR [rdx+8]
	jne	.L111
	jmp	.L104
.L113:
	xor	eax, eax
	pop	rbx
	.cfi_restore 3
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE9:
	.size	move, .-move
	.section	.text.unlikely
.LCOLDE16:
	.text
.LHOTE16:
	.section	.text.unlikely
.LCOLDB17:
	.text
.LHOTB17:
	.p2align 4,,15
	.globl	play
	.type	play, @function
play:
.LFB11:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	push	rbx
	.cfi_def_cfa_offset 24
	.cfi_offset 3, -24
	xor	eax, eax
	sub	rsp, 40
	.cfi_def_cfa_offset 64
	call	getchar
	mov	edi, OFFSET FLAT:start_message
	call	strlen
	lea	edx, [rax+rax*4]
	mov	ecx, 20
	mov	esi, 164
	mov	edi, 292
	sal	edx, 2
	movsx	rdx, edx
	call	delete
	mov	ecx, 20
	mov	edx, 984
	mov	esi, 264
	mov	edi, 20
	call	delete
	.p2align 4,,10
	.p2align 3
.L130:
	lea	rdi, [rsp+8]
	call	sys_ticks
	sub	rsp, 8
	.cfi_def_cfa_offset 72
	xor	r9d, r9d
	xor	r8d, r8d
	push	2
	.cfi_def_cfa_offset 80
	mov	ecx, 255
	xor	esi, esi
	mov	edx, OFFSET FLAT:score
	mov	edi, 312
	call	drawString
	mov	edi, DWORD PTR totalScore[rip]
	lea	rsi, [rsp+38]
	mov	edx, 10
	call	itoa
	lea	rdx, [rsp+38]
	xor	r9d, r9d
	xor	r8d, r8d
	mov	ecx, 255
	xor	esi, esi
	mov	edi, 412
	mov	DWORD PTR [rsp], 2
	call	drawString
	movsx	rax, DWORD PTR ticksTillRefresh[rip]
	mov	ebx, DWORD PTR totalScore[rip]
	pop	rdx
	.cfi_def_cfa_offset 72
	add	rax, QWORD PTR ticks[rip]
	pop	rcx
	.cfi_def_cfa_offset 64
	cmp	rax, QWORD PTR [rsp+8]
	ja	.L130
	lea	rdi, [rsp+8]
	call	sys_ticks
	mov	QWORD PTR ticks[rip], rax
	xor	eax, eax
	call	move
	cmp	ebx, DWORD PTR totalScore[rip]
	mov	ebp, eax
	je	.L132
	mov	ecx, 20
	mov	edx, 40
	xor	esi, esi
	mov	edi, 412
	call	delete
.L132:
	test	ebp, ebp
	je	.L130
	add	rsp, 40
	.cfi_def_cfa_offset 24
	pop	rbx
	.cfi_restore 3
	.cfi_def_cfa_offset 16
	pop	rbp
	.cfi_restore 6
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE11:
	.size	play, .-play
	.section	.text.unlikely
.LCOLDE17:
	.text
.LHOTE17:
	.section	.rodata.str1.1
.LC18:
	.string	"Press enter to continue"
	.section	.text.unlikely
.LCOLDB19:
	.text
.LHOTB19:
	.p2align 4,,15
	.globl	showScore
	.type	showScore, @function
showScore:
.LFB12:
	.cfi_startproc
	sub	rsp, 16
	.cfi_def_cfa_offset 24
	mov	edx, OFFSET FLAT:.LC18
	xor	r9d, r9d
	push	3
	.cfi_def_cfa_offset 32
	xor	r8d, r8d
	mov	ecx, 255
	mov	esi, 584
	mov	edi, 200
	call	drawString
	pop	rax
	.cfi_def_cfa_offset 24
	pop	rdx
	.cfi_def_cfa_offset 16
	.p2align 4,,10
	.p2align 3
.L139:
	xor	eax, eax
	call	getchar
	cmp	eax, 10
	jne	.L139
	add	rsp, 8
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE12:
	.size	showScore, .-showScore
	.section	.text.unlikely
.LCOLDE19:
	.text
.LHOTE19:
	.section	.text.unlikely
.LCOLDB20:
	.text
.LHOTB20:
	.p2align 4,,15
	.globl	snake_game
	.type	snake_game, @function
snake_game:
.LFB14:
	.cfi_startproc
	sub	rsp, 8
	.cfi_def_cfa_offset 16
	xor	eax, eax
	call	start
	xor	eax, eax
	call	printSnake
	xor	eax, eax
	call	play
	xor	eax, eax
	call	showScore
	xor	eax, eax
	call	sys_clear
	xor	eax, eax
	add	rsp, 8
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE14:
	.size	snake_game, .-snake_game
	.section	.text.unlikely
.LCOLDE20:
	.text
.LHOTE20:
	.globl	totalScore
	.bss
	.align 4
	.type	totalScore, @object
	.size	totalScore, 4
totalScore:
	.zero	4
	.globl	count
	.align 4
	.type	count, @object
	.size	count, 4
count:
	.zero	4
	.globl	play_seconds
	.align 4
	.type	play_seconds, @object
	.size	play_seconds, 4
play_seconds:
	.zero	4
	.globl	start_seconds
	.align 4
	.type	start_seconds, @object
	.size	start_seconds, 4
start_seconds:
	.zero	4
	.globl	snake_speed
	.data
	.align 8
	.type	snake_speed, @object
	.size	snake_speed, 8
snake_speed:
	.long	0
	.long	1073217536
	.globl	ticksTillRefresh
	.align 4
	.type	ticksTillRefresh, @object
	.size	ticksTillRefresh, 4
ticksTillRefresh:
	.long	3
	.globl	ticks_to_bigger
	.align 4
	.type	ticks_to_bigger, @object
	.size	ticks_to_bigger, 4
ticks_to_bigger:
	.long	15
	.local	ticks
	.comm	ticks,8,8
	.align 32
	.type	commands, @object
	.size	commands, 41
commands:
	.string	"'w' Up ; 's' Down ; 'a' Left ; 'd' Right"
	.align 16
	.type	start_message, @object
	.size	start_message, 23
start_message:
	.string	"Press any key to start"
	.type	score, @object
	.size	score, 8
score:
	.string	"Score: "
	.align 4
	.type	snake_size, @object
	.size	snake_size, 4
snake_size:
	.long	5
	.local	snake
	.comm	snake,3200,64
	.globl	fonts
	.align 64
	.type	fonts, @object
	.size	fonts, 1040
fonts:
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	24
	.byte	60
	.byte	60
	.byte	24
	.byte	24
	.byte	0
	.byte	24
	.byte	0
	.byte	54
	.byte	54
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	54
	.byte	54
	.byte	127
	.byte	54
	.byte	127
	.byte	54
	.byte	54
	.byte	0
	.byte	12
	.byte	62
	.byte	3
	.byte	30
	.byte	48
	.byte	31
	.byte	12
	.byte	0
	.byte	0
	.byte	99
	.byte	51
	.byte	24
	.byte	12
	.byte	102
	.byte	99
	.byte	0
	.byte	28
	.byte	54
	.byte	28
	.byte	110
	.byte	59
	.byte	51
	.byte	110
	.byte	0
	.byte	6
	.byte	6
	.byte	3
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	24
	.byte	12
	.byte	6
	.byte	6
	.byte	6
	.byte	12
	.byte	24
	.byte	0
	.byte	6
	.byte	12
	.byte	24
	.byte	24
	.byte	24
	.byte	12
	.byte	6
	.byte	0
	.byte	0
	.byte	102
	.byte	60
	.byte	-1
	.byte	60
	.byte	102
	.byte	0
	.byte	0
	.byte	0
	.byte	12
	.byte	12
	.byte	63
	.byte	12
	.byte	12
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	12
	.byte	12
	.byte	6
	.byte	0
	.byte	0
	.byte	0
	.byte	63
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	12
	.byte	12
	.byte	0
	.byte	96
	.byte	48
	.byte	24
	.byte	12
	.byte	6
	.byte	3
	.byte	1
	.byte	0
	.byte	62
	.byte	99
	.byte	115
	.byte	123
	.byte	111
	.byte	103
	.byte	62
	.byte	0
	.byte	12
	.byte	14
	.byte	12
	.byte	12
	.byte	12
	.byte	12
	.byte	63
	.byte	0
	.byte	30
	.byte	51
	.byte	48
	.byte	28
	.byte	6
	.byte	51
	.byte	63
	.byte	0
	.byte	30
	.byte	51
	.byte	48
	.byte	28
	.byte	48
	.byte	51
	.byte	30
	.byte	0
	.byte	56
	.byte	60
	.byte	54
	.byte	51
	.byte	127
	.byte	48
	.byte	120
	.byte	0
	.byte	63
	.byte	3
	.byte	31
	.byte	48
	.byte	48
	.byte	51
	.byte	30
	.byte	0
	.byte	28
	.byte	6
	.byte	3
	.byte	31
	.byte	51
	.byte	51
	.byte	30
	.byte	0
	.byte	63
	.byte	51
	.byte	48
	.byte	24
	.byte	12
	.byte	12
	.byte	12
	.byte	0
	.byte	30
	.byte	51
	.byte	51
	.byte	30
	.byte	51
	.byte	51
	.byte	30
	.byte	0
	.byte	30
	.byte	51
	.byte	51
	.byte	62
	.byte	48
	.byte	24
	.byte	14
	.byte	0
	.byte	0
	.byte	12
	.byte	12
	.byte	0
	.byte	0
	.byte	12
	.byte	12
	.byte	0
	.byte	0
	.byte	12
	.byte	12
	.byte	0
	.byte	0
	.byte	12
	.byte	12
	.byte	6
	.byte	24
	.byte	12
	.byte	6
	.byte	3
	.byte	6
	.byte	12
	.byte	24
	.byte	0
	.byte	0
	.byte	0
	.byte	63
	.byte	0
	.byte	0
	.byte	63
	.byte	0
	.byte	0
	.byte	6
	.byte	12
	.byte	24
	.byte	48
	.byte	24
	.byte	12
	.byte	6
	.byte	0
	.byte	30
	.byte	51
	.byte	48
	.byte	24
	.byte	12
	.byte	0
	.byte	12
	.byte	0
	.byte	62
	.byte	99
	.byte	123
	.byte	123
	.byte	123
	.byte	3
	.byte	30
	.byte	0
	.byte	12
	.byte	30
	.byte	51
	.byte	51
	.byte	63
	.byte	51
	.byte	51
	.byte	0
	.byte	63
	.byte	102
	.byte	102
	.byte	62
	.byte	102
	.byte	102
	.byte	63
	.byte	0
	.byte	60
	.byte	102
	.byte	3
	.byte	3
	.byte	3
	.byte	102
	.byte	60
	.byte	0
	.byte	31
	.byte	54
	.byte	102
	.byte	102
	.byte	102
	.byte	54
	.byte	31
	.byte	0
	.byte	127
	.byte	70
	.byte	22
	.byte	30
	.byte	22
	.byte	70
	.byte	127
	.byte	0
	.byte	127
	.byte	70
	.byte	22
	.byte	30
	.byte	22
	.byte	6
	.byte	15
	.byte	0
	.byte	60
	.byte	102
	.byte	3
	.byte	3
	.byte	115
	.byte	102
	.byte	124
	.byte	0
	.byte	51
	.byte	51
	.byte	51
	.byte	63
	.byte	51
	.byte	51
	.byte	51
	.byte	0
	.byte	30
	.byte	12
	.byte	12
	.byte	12
	.byte	12
	.byte	12
	.byte	30
	.byte	0
	.byte	120
	.byte	48
	.byte	48
	.byte	48
	.byte	51
	.byte	51
	.byte	30
	.byte	0
	.byte	103
	.byte	102
	.byte	54
	.byte	30
	.byte	54
	.byte	102
	.byte	103
	.byte	0
	.byte	15
	.byte	6
	.byte	6
	.byte	6
	.byte	70
	.byte	102
	.byte	127
	.byte	0
	.byte	99
	.byte	119
	.byte	127
	.byte	127
	.byte	107
	.byte	99
	.byte	99
	.byte	0
	.byte	99
	.byte	103
	.byte	111
	.byte	123
	.byte	115
	.byte	99
	.byte	99
	.byte	0
	.byte	28
	.byte	54
	.byte	99
	.byte	99
	.byte	99
	.byte	54
	.byte	28
	.byte	0
	.byte	63
	.byte	102
	.byte	102
	.byte	62
	.byte	6
	.byte	6
	.byte	15
	.byte	0
	.byte	30
	.byte	51
	.byte	51
	.byte	51
	.byte	59
	.byte	30
	.byte	56
	.byte	0
	.byte	63
	.byte	102
	.byte	102
	.byte	62
	.byte	54
	.byte	102
	.byte	103
	.byte	0
	.byte	30
	.byte	51
	.byte	7
	.byte	14
	.byte	56
	.byte	51
	.byte	30
	.byte	0
	.byte	63
	.byte	45
	.byte	12
	.byte	12
	.byte	12
	.byte	12
	.byte	30
	.byte	0
	.byte	51
	.byte	51
	.byte	51
	.byte	51
	.byte	51
	.byte	51
	.byte	63
	.byte	0
	.byte	51
	.byte	51
	.byte	51
	.byte	51
	.byte	51
	.byte	30
	.byte	12
	.byte	0
	.byte	99
	.byte	99
	.byte	99
	.byte	107
	.byte	127
	.byte	119
	.byte	99
	.byte	0
	.byte	99
	.byte	99
	.byte	54
	.byte	28
	.byte	28
	.byte	54
	.byte	99
	.byte	0
	.byte	51
	.byte	51
	.byte	51
	.byte	30
	.byte	12
	.byte	12
	.byte	30
	.byte	0
	.byte	127
	.byte	99
	.byte	49
	.byte	24
	.byte	76
	.byte	102
	.byte	127
	.byte	0
	.byte	30
	.byte	6
	.byte	6
	.byte	6
	.byte	6
	.byte	6
	.byte	30
	.byte	0
	.byte	3
	.byte	6
	.byte	12
	.byte	24
	.byte	48
	.byte	96
	.byte	64
	.byte	0
	.byte	30
	.byte	24
	.byte	24
	.byte	24
	.byte	24
	.byte	24
	.byte	30
	.byte	0
	.byte	8
	.byte	28
	.byte	54
	.byte	99
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	-1
	.byte	12
	.byte	12
	.byte	24
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	30
	.byte	48
	.byte	62
	.byte	51
	.byte	110
	.byte	0
	.byte	7
	.byte	6
	.byte	6
	.byte	62
	.byte	102
	.byte	102
	.byte	59
	.byte	0
	.byte	0
	.byte	0
	.byte	30
	.byte	51
	.byte	3
	.byte	51
	.byte	30
	.byte	0
	.byte	56
	.byte	48
	.byte	48
	.byte	62
	.byte	51
	.byte	51
	.byte	110
	.byte	0
	.byte	0
	.byte	0
	.byte	30
	.byte	51
	.byte	63
	.byte	3
	.byte	30
	.byte	0
	.byte	28
	.byte	54
	.byte	6
	.byte	15
	.byte	6
	.byte	6
	.byte	15
	.byte	0
	.byte	0
	.byte	0
	.byte	110
	.byte	51
	.byte	51
	.byte	62
	.byte	48
	.byte	31
	.byte	7
	.byte	6
	.byte	54
	.byte	110
	.byte	102
	.byte	102
	.byte	103
	.byte	0
	.byte	12
	.byte	0
	.byte	14
	.byte	12
	.byte	12
	.byte	12
	.byte	30
	.byte	0
	.byte	48
	.byte	0
	.byte	48
	.byte	48
	.byte	48
	.byte	51
	.byte	51
	.byte	30
	.byte	7
	.byte	6
	.byte	102
	.byte	54
	.byte	30
	.byte	54
	.byte	103
	.byte	0
	.byte	14
	.byte	12
	.byte	12
	.byte	12
	.byte	12
	.byte	12
	.byte	30
	.byte	0
	.byte	0
	.byte	0
	.byte	51
	.byte	127
	.byte	127
	.byte	107
	.byte	99
	.byte	0
	.byte	0
	.byte	0
	.byte	31
	.byte	51
	.byte	51
	.byte	51
	.byte	51
	.byte	0
	.byte	0
	.byte	0
	.byte	30
	.byte	51
	.byte	51
	.byte	51
	.byte	30
	.byte	0
	.byte	0
	.byte	0
	.byte	59
	.byte	102
	.byte	102
	.byte	62
	.byte	6
	.byte	15
	.byte	0
	.byte	0
	.byte	110
	.byte	51
	.byte	51
	.byte	62
	.byte	48
	.byte	120
	.byte	0
	.byte	0
	.byte	59
	.byte	110
	.byte	102
	.byte	6
	.byte	15
	.byte	0
	.byte	0
	.byte	0
	.byte	62
	.byte	3
	.byte	30
	.byte	48
	.byte	31
	.byte	0
	.byte	8
	.byte	12
	.byte	62
	.byte	12
	.byte	12
	.byte	44
	.byte	24
	.byte	0
	.byte	0
	.byte	0
	.byte	51
	.byte	51
	.byte	51
	.byte	51
	.byte	110
	.byte	0
	.byte	0
	.byte	0
	.byte	51
	.byte	51
	.byte	51
	.byte	30
	.byte	12
	.byte	0
	.byte	0
	.byte	0
	.byte	99
	.byte	107
	.byte	127
	.byte	127
	.byte	54
	.byte	0
	.byte	0
	.byte	0
	.byte	99
	.byte	54
	.byte	28
	.byte	54
	.byte	99
	.byte	0
	.byte	0
	.byte	0
	.byte	51
	.byte	51
	.byte	51
	.byte	62
	.byte	48
	.byte	31
	.byte	0
	.byte	0
	.byte	63
	.byte	25
	.byte	12
	.byte	38
	.byte	63
	.byte	0
	.byte	56
	.byte	12
	.byte	12
	.byte	7
	.byte	12
	.byte	12
	.byte	56
	.byte	0
	.byte	24
	.byte	24
	.byte	24
	.byte	0
	.byte	24
	.byte	24
	.byte	24
	.byte	0
	.byte	7
	.byte	12
	.byte	12
	.byte	56
	.byte	12
	.byte	12
	.byte	7
	.byte	0
	.byte	110
	.byte	59
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	102
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	126
	.byte	60
	.byte	24
	.byte	0
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.ident	"GCC: (Debian 4.9.2-10+deb8u1) 4.9.2"
	.section	.note.GNU-stack,"",@progbits

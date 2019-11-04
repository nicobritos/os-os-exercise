	.file	"stdlib.c"
	.intel_syntax noprefix
	.section	.text.unlikely,"ax",@progbits
.LCOLDB0:
	.text
.LHOTB0:
	.p2align 4,,15
	.globl	strlen
	.type	strlen, @function
strlen:
.LFB0:
	.cfi_startproc
	cmp	BYTE PTR [rdi], 0
	je	.L4
	add	rdi, 1
	xor	eax, eax
	.p2align 4,,10
	.p2align 3
.L3:
	add	rdi, 1
	add	eax, 1
	cmp	BYTE PTR [rdi-1], 0
	jne	.L3
	rep ret
.L4:
	xor	eax, eax
	ret
	.cfi_endproc
.LFE0:
	.size	strlen, .-strlen
	.section	.text.unlikely
.LCOLDE0:
	.text
.LHOTE0:
	.section	.text.unlikely
.LCOLDB1:
	.text
.LHOTB1:
	.p2align 4,,15
	.globl	strcmp
	.type	strcmp, @function
strcmp:
.LFB1:
	.cfi_startproc
	movsx	eax, BYTE PTR [rdi]
	test	al, al
	je	.L15
	lea	rdx, [rdi+1]
	xor	r8d, r8d
	.p2align 4,,10
	.p2align 3
.L9:
	add	rdx, 1
	add	r8d, 1
	cmp	BYTE PTR [rdx-1], 0
	jne	.L9
.L8:
	movsx	r10d, BYTE PTR [rsi]
	test	r10b, r10b
	je	.L10
	lea	rdx, [rsi+1]
	xor	r9d, r9d
	.p2align 4,,10
	.p2align 3
.L11:
	add	rdx, 1
	add	r9d, 1
	cmp	BYTE PTR [rdx-1], 0
	jne	.L11
	test	r8d, r8d
	jle	.L10
	cmp	r10b, al
	jne	.L10
	xor	ecx, ecx
	xor	edx, edx
	.p2align 4,,10
	.p2align 3
.L14:
	add	edx, 1
	cmp	edx, r9d
	jge	.L16
	cmp	edx, r8d
	jge	.L16
	movsx	eax, BYTE PTR [rdi+1+rcx]
	add	rcx, 1
	movsx	r10d, BYTE PTR [rsi+rcx]
	cmp	al, r10b
	je	.L14
.L10:
	sub	eax, r10d
	ret
	.p2align 4,,10
	.p2align 3
.L16:
	movsx	rdx, edx
	movsx	eax, BYTE PTR [rdi+rdx]
	movsx	r10d, BYTE PTR [rsi+rdx]
	sub	eax, r10d
	ret
.L15:
	xor	r8d, r8d
	jmp	.L8
	.cfi_endproc
.LFE1:
	.size	strcmp, .-strcmp
	.section	.text.unlikely
.LCOLDE1:
	.text
.LHOTE1:
	.section	.text.unlikely
.LCOLDB2:
	.text
.LHOTB2:
	.p2align 4,,15
	.globl	strncmp
	.type	strncmp, @function
strncmp:
.LFB2:
	.cfi_startproc
	cmp	BYTE PTR [rdi], 0
	je	.L36
	lea	rax, [rdi+1]
	xor	r9d, r9d
	.p2align 4,,10
	.p2align 3
.L28:
	add	rax, 1
	add	r9d, 1
	cmp	BYTE PTR [rax-1], 0
	jne	.L28
.L27:
	cmp	BYTE PTR [rsi], 0
	je	.L37
	lea	rax, [rsi+1]
	xor	r8d, r8d
	.p2align 4,,10
	.p2align 3
.L30:
	add	rax, 1
	add	r8d, 1
	cmp	BYTE PTR [rax-1], 0
	jne	.L30
.L29:
	xor	ecx, ecx
	jmp	.L35
	.p2align 4,,10
	.p2align 3
.L45:
	cmp	r8d, ecx
	jle	.L38
	cmp	ecx, r9d
	jge	.L38
	movsx	eax, BYTE PTR [rdi+rcx]
	add	rcx, 1
	movsx	r10d, BYTE PTR [rsi-1+rcx]
	cmp	al, r10b
	jne	.L32
.L35:
	lea	r10d, [rcx+1]
	mov	eax, ecx
	cmp	edx, r10d
	jg	.L45
.L38:
	movsx	rdx, eax
	movsx	eax, BYTE PTR [rdi+rdx]
	movsx	r10d, BYTE PTR [rsi+rdx]
.L32:
	sub	eax, r10d
	ret
.L36:
	xor	r9d, r9d
	jmp	.L27
.L37:
	xor	r8d, r8d
	jmp	.L29
	.cfi_endproc
.LFE2:
	.size	strncmp, .-strncmp
	.section	.text.unlikely
.LCOLDE2:
	.text
.LHOTE2:
	.section	.text.unlikely
.LCOLDB3:
	.text
.LHOTB3:
	.p2align 4,,15
	.globl	itoa
	.type	itoa, @function
itoa:
.LFB3:
	.cfi_startproc
	mov	r11d, edx
	mov	edx, edi
	mov	eax, edi
	shr	edx, 31
	test	dl, dl
	je	.L54
	cmp	r11d, 10
	jne	.L54
	neg	eax
	mov	BYTE PTR [rsi], 45
	mov	r10d, 1
.L47:
	mov	rcx, rsi
	jmp	.L50
	.p2align 4,,10
	.p2align 3
.L55:
	mov	rcx, r9
.L50:
	cdq
	lea	r9, [rcx+1]
	idiv	r11d
	lea	edi, [rdx+48]
	lea	r8d, [rdx+55]
	cmp	edx, 9
	cmovg	edi, r8d
	add	r10d, 1
	test	eax, eax
	mov	BYTE PTR [r9-1], dil
	jne	.L55
	xor	eax, eax
	mov	BYTE PTR [rcx+1], 0
	cmp	BYTE PTR [rsi], 45
	sete	al
	add	rsi, rax
	cmp	rsi, rcx
	jb	.L53
	jmp	.L57
	.p2align 4,,10
	.p2align 3
.L60:
	movzx	edi, BYTE PTR [rcx]
.L53:
	movzx	eax, BYTE PTR [rsi]
	sub	rcx, 1
	mov	BYTE PTR [rsi], dil
	add	rsi, 1
	mov	BYTE PTR [rcx+1], al
	cmp	rsi, rcx
	jb	.L60
.L57:
	mov	eax, r10d
	ret
	.p2align 4,,10
	.p2align 3
.L54:
	xor	r10d, r10d
	jmp	.L47
	.cfi_endproc
.LFE3:
	.size	itoa, .-itoa
	.section	.text.unlikely
.LCOLDE3:
	.text
.LHOTE3:
	.section	.text.unlikely
.LCOLDB4:
	.text
.LHOTB4:
	.p2align 4,,15
	.globl	atoi
	.type	atoi, @function
atoi:
.LFB4:
	.cfi_startproc
	movsx	edx, BYTE PTR [rdi]
	test	dl, dl
	je	.L66
	lea	ecx, [rdx-48]
	mov	eax, -1
	cmp	cl, 9
	ja	.L63
	add	rdi, 1
	xor	eax, eax
	jmp	.L64
	.p2align 4,,10
	.p2align 3
.L65:
	lea	ecx, [rdx-48]
	add	rdi, 1
	cmp	cl, 9
	ja	.L68
.L64:
	lea	eax, [rax+rax*4]
	lea	eax, [rdx-48+rax*2]
	movsx	edx, BYTE PTR [rdi]
	test	dl, dl
	jne	.L65
	rep ret
	.p2align 4,,10
	.p2align 3
.L68:
	mov	eax, -1
.L63:
	rep ret
.L66:
	xor	eax, eax
	ret
	.cfi_endproc
.LFE4:
	.size	atoi, .-atoi
	.section	.text.unlikely
.LCOLDE4:
	.text
.LHOTE4:
	.section	.text.unlikely
.LCOLDB5:
	.text
.LHOTB5:
	.p2align 4,,15
	.globl	atox
	.type	atox, @function
atox:
.LFB5:
	.cfi_startproc
	xor	eax, eax
	jmp	.L70
	.p2align 4,,10
	.p2align 3
.L77:
	sal	eax, 4
	lea	eax, [rax-48+rdx]
.L72:
	add	rdi, 1
.L70:
	movsx	edx, BYTE PTR [rdi]
	test	dl, dl
	je	.L76
	lea	ecx, [rdx-48]
	cmp	cl, 9
	jbe	.L77
	lea	ecx, [rdx-97]
	cmp	cl, 5
	ja	.L75
	sal	eax, 4
	lea	eax, [rax-87+rdx]
	jmp	.L72
	.p2align 4,,10
	.p2align 3
.L76:
	rep ret
	.p2align 4,,10
	.p2align 3
.L75:
	mov	eax, -1
	ret
	.cfi_endproc
.LFE5:
	.size	atox, .-atox
	.section	.text.unlikely
.LCOLDE5:
	.text
.LHOTE5:
	.section	.text.unlikely
.LCOLDB6:
	.text
.LHOTB6:
	.p2align 4,,15
	.globl	malloc
	.type	malloc, @function
malloc:
.LFB6:
	.cfi_startproc
	jmp	sys_malloc
	.cfi_endproc
.LFE6:
	.size	malloc, .-malloc
	.section	.text.unlikely
.LCOLDE6:
	.text
.LHOTE6:
	.section	.text.unlikely
.LCOLDB7:
	.text
.LHOTB7:
	.p2align 4,,15
	.globl	free
	.type	free, @function
free:
.LFB7:
	.cfi_startproc
	jmp	sys_free
	.cfi_endproc
.LFE7:
	.size	free, .-free
	.section	.text.unlikely
.LCOLDE7:
	.text
.LHOTE7:
	.section	.text.unlikely
.LCOLDB8:
	.text
.LHOTB8:
	.p2align 4,,15
	.globl	lineCount
	.type	lineCount, @function
lineCount:
.LFB8:
	.cfi_startproc
	movzx	edx, BYTE PTR [rdi]
	test	dl, dl
	je	.L84
	xor	ecx, ecx
	mov	eax, 1
	.p2align 4,,10
	.p2align 3
.L83:
	cmp	dl, 10
	sete	dl
	movzx	edx, dl
	add	eax, edx
	lea	edx, [rcx+1]
	mov	rcx, rdx
	movzx	edx, BYTE PTR [rdi+rdx]
	test	dl, dl
	jne	.L83
	rep ret
.L84:
	mov	eax, 1
	ret
	.cfi_endproc
.LFE8:
	.size	lineCount, .-lineCount
	.section	.text.unlikely
.LCOLDE8:
	.text
.LHOTE8:
	.section	.text.unlikely
.LCOLDB9:
	.text
.LHOTB9:
	.p2align 4,,15
	.globl	filterVowels
	.type	filterVowels, @function
filterVowels:
.LFB9:
	.cfi_startproc
	movzx	edx, BYTE PTR [rsi]
	mov	rax, rdi
	test	dl, dl
	je	.L90
	xor	ecx, ecx
	xor	edi, edi
	.p2align 4,,10
	.p2align 3
.L89:
	mov	r9d, edx
	mov	r8d, edx
	and	r9d, -33
	cmp	r9b, 73
	setne	r10b
	and	r8d, -37
	cmp	r8b, 65
	setne	r8b
	and	r8d, r10d
	cmp	r9b, 79
	setne	r10b
	test	r8b, r10b
	je	.L88
	cmp	r9b, 85
	je	.L88
	mov	r8d, edi
	add	edi, 1
	mov	BYTE PTR [rax+r8], dl
	.p2align 4,,10
	.p2align 3
.L88:
	movzx	edx, BYTE PTR [rsi+1+rcx]
	cmp	ecx, 199
	setne	r9b
	test	dl, dl
	setne	r8b
	add	rcx, 1
	test	r9b, r8b
	jne	.L89
.L87:
	mov	BYTE PTR [rax+rdi], 0
	ret
.L90:
	xor	edi, edi
	jmp	.L87
	.cfi_endproc
.LFE9:
	.size	filterVowels, .-filterVowels
	.section	.text.unlikely
.LCOLDE9:
	.text
.LHOTE9:
	.section	.text.unlikely
.LCOLDB10:
	.text
.LHOTB10:
	.p2align 4,,15
	.globl	trim
	.type	trim, @function
trim:
.LFB10:
	.cfi_startproc
	movzx	eax, BYTE PTR [rdi]
	cmp	al, 32
	jne	.L99
	mov	rax, rdi
	.p2align 4,,10
	.p2align 3
.L100:
	add	rax, 1
	cmp	BYTE PTR [rax], 32
	je	.L100
	.p2align 4,,10
	.p2align 3
.L103:
	add	rdi, 1
	cmp	BYTE PTR [rdi], 0
	jne	.L103
.L102:
	lea	rdx, [rdi-1]
	cmp	rdx, rax
	jb	.L108
	cmp	BYTE PTR [rdi-1], 32
	jne	.L108
	lea	rcx, [rax-1]
	jmp	.L105
	.p2align 4,,10
	.p2align 3
.L112:
	cmp	BYTE PTR [rdx], 32
	jne	.L108
.L105:
	sub	rdx, 1
	cmp	rdx, rcx
	jne	.L112
	mov	BYTE PTR [rcx+1], 0
	ret
	.p2align 4,,10
	.p2align 3
.L108:
	mov	rcx, rdx
	mov	BYTE PTR [rcx+1], 0
	ret
.L99:
	test	al, al
	mov	rax, rdi
	je	.L102
	jmp	.L103
	.cfi_endproc
.LFE10:
	.size	trim, .-trim
	.section	.text.unlikely
.LCOLDE10:
	.text
.LHOTE10:
	.section	.text.unlikely
.LCOLDB11:
	.text
.LHOTB11:
	.p2align 4,,15
	.globl	replaceChars
	.type	replaceChars, @function
replaceChars:
.LFB11:
	.cfi_startproc
	movzx	ecx, BYTE PTR [rdi]
	xor	eax, eax
	test	cl, cl
	jne	.L116
	jmp	.L117
	.p2align 4,,10
	.p2align 3
.L115:
	add	rdi, 1
	movzx	ecx, BYTE PTR [rdi]
	test	cl, cl
	je	.L119
.L116:
	cmp	cl, sil
	jne	.L115
	mov	BYTE PTR [rdi], dl
	add	rdi, 1
	movzx	ecx, BYTE PTR [rdi]
	add	rax, 1
	test	cl, cl
	jne	.L116
.L119:
	rep ret
.L117:
	rep ret
	.cfi_endproc
.LFE11:
	.size	replaceChars, .-replaceChars
	.section	.text.unlikely
.LCOLDE11:
	.text
.LHOTE11:
	.section	.text.unlikely
.LCOLDB12:
	.text
.LHOTB12:
	.p2align 4,,15
	.globl	strcpy
	.type	strcpy, @function
strcpy:
.LFB12:
	.cfi_startproc
	movzx	edx, BYTE PTR [rsi]
	xor	eax, eax
	test	dl, dl
	je	.L121
	.p2align 4,,10
	.p2align 3
.L122:
	mov	BYTE PTR [rdi+rax], dl
	add	rax, 1
	movzx	edx, BYTE PTR [rsi+rax]
	test	dl, dl
	jne	.L122
.L121:
	mov	BYTE PTR [rdi+rax], 0
	ret
	.cfi_endproc
.LFE12:
	.size	strcpy, .-strcpy
	.section	.text.unlikely
.LCOLDE12:
	.text
.LHOTE12:
	.section	.text.unlikely
.LCOLDB13:
	.text
.LHOTB13:
	.p2align 4,,15
	.globl	tokenArgs
	.type	tokenArgs, @function
tokenArgs:
.LFB13:
	.cfi_startproc
	sub	rsp, 112
	.cfi_def_cfa_offset 120
	movzx	edx, BYTE PTR [rsi]
	test	dl, dl
	je	.L131
	lea	r8, [rsp+12]
	xor	eax, eax
	.p2align 4,,10
	.p2align 3
.L127:
	mov	BYTE PTR [r8+rax], dl
	add	rax, 1
	movzx	edx, BYTE PTR [rsi+rax]
	test	dl, dl
	jne	.L127
	add	rax, r8
.L126:
	mov	BYTE PTR [rax], 0
	movzx	eax, BYTE PTR [rsp+12]
	test	al, al
	je	.L132
	lea	rcx, [r8+1]
	mov	edx, 1
	xor	esi, esi
	jmp	.L130
	.p2align 4,,10
	.p2align 3
.L129:
	movzx	eax, BYTE PTR [rsp+12+rdx]
	add	rcx, 1
	add	rdx, 1
	test	al, al
	je	.L137
.L130:
	cmp	al, 32
	jne	.L129
	mov	QWORD PTR [rdi+rsi*8], r8
	mov	BYTE PTR [rcx-1], 0
	add	rsi, 1
	mov	r8, rcx
	jmp	.L129
.L137:
	lea	rdx, [0+rsi*8]
	lea	rax, [rsi+1]
.L128:
	mov	QWORD PTR [rdi+rdx], r8
	add	rsp, 112
	.cfi_remember_state
	.cfi_def_cfa_offset 8
	ret
.L131:
	.cfi_restore_state
	lea	r8, [rsp+12]
	mov	rax, r8
	jmp	.L126
.L132:
	mov	eax, 1
	xor	edx, edx
	jmp	.L128
	.cfi_endproc
.LFE13:
	.size	tokenArgs, .-tokenArgs
	.section	.text.unlikely
.LCOLDE13:
	.text
.LHOTE13:
	.ident	"GCC: (Debian 4.9.2-10+deb8u1) 4.9.2"
	.section	.note.GNU-stack,"",@progbits

	.file	"_loader.c"
	.intel_syntax noprefix
	.section	.text.unlikely,"ax",@progbits
.LCOLDB0:
	.text
.LHOTB0:
	.p2align 4,,15
	.globl	_start
	.type	_start, @function
_start:
.LFB0:
	.cfi_startproc
	mov	edx, OFFSET FLAT:endOfBinary
	sub	rdx, OFFSET FLAT:bss
	test	rdx, rdx
	lea	rax, [rdx-1]
	je	.L4
	.p2align 4,,10
	.p2align 3
.L5:
	mov	BYTE PTR bss[rax], 0
	sub	rax, 1
	cmp	rax, -1
	jne	.L5
.L4:
	xor	eax, eax
	jmp	main
	.cfi_endproc
.LFE0:
	.size	_start, .-_start
	.section	.text.unlikely
.LCOLDE0:
	.text
.LHOTE0:
	.section	.text.unlikely
.LCOLDB1:
	.text
.LHOTB1:
	.p2align 4,,15
	.globl	memset
	.type	memset, @function
memset:
.LFB1:
	.cfi_startproc
	test	rdx, rdx
	mov	rax, rdi
	lea	rcx, [rdx-1]
	je	.L14
	.p2align 4,,10
	.p2align 3
.L12:
	mov	BYTE PTR [rax+rcx], sil
	sub	rcx, 1
	cmp	rcx, -1
	jne	.L12
.L14:
	rep ret
	.cfi_endproc
.LFE1:
	.size	memset, .-memset
	.section	.text.unlikely
.LCOLDE1:
	.text
.LHOTE1:
	.ident	"GCC: (Debian 4.9.2-10+deb8u1) 4.9.2"
	.section	.note.GNU-stack,"",@progbits

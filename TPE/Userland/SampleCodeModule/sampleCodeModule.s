	.file	"sampleCodeModule.c"
	.intel_syntax noprefix
	.section	.text.unlikely,"ax",@progbits
.LCOLDB0:
	.section	.text.startup,"ax",@progbits
.LHOTB0:
	.p2align 4,,15
	.globl	main
	.type	main, @function
main:
.LFB0:
	.cfi_startproc
	sub	rsp, 8
	.cfi_def_cfa_offset 16
	xor	eax, eax
	call	shell
	xor	eax, eax
	add	rsp, 8
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.section	.text.unlikely
.LCOLDE0:
	.section	.text.startup
.LHOTE0:
	.ident	"GCC: (Debian 4.9.2-10+deb8u1) 4.9.2"
	.section	.note.GNU-stack,"",@progbits

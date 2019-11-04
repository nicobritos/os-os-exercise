	.file	"commands.c"
	.intel_syntax noprefix
	.section	.text.unlikely,"ax",@progbits
.LCOLDB0:
	.text
.LHOTB0:
	.p2align 4,,15
	.globl	clearScreen
	.type	clearScreen, @function
clearScreen:
.LFB0:
	.cfi_startproc
	xor	eax, eax
	jmp	sys_clear
	.cfi_endproc
.LFE0:
	.size	clearScreen, .-clearScreen
	.section	.text.unlikely
.LCOLDE0:
	.text
.LHOTE0:
	.section	.text.unlikely
.LCOLDB1:
	.text
.LHOTB1:
	.p2align 4,,15
	.globl	time
	.type	time, @function
time:
.LFB1:
	.cfi_startproc
	sub	rsp, 72
	.cfi_def_cfa_offset 80
	lea	rdi, [rsp+16]
	call	sys_time
	movzx	eax, BYTE PTR [rsp+16]
	lea	rdi, [rsp+7]
	mov	BYTE PTR [rsp+9], 58
	mov	BYTE PTR [rsp+12], 58
	mov	BYTE PTR [rsp+15], 0
	add	eax, 48
	mov	BYTE PTR [rsp+7], al
	movzx	eax, BYTE PTR [rsp+24]
	add	eax, 48
	mov	BYTE PTR [rsp+8], al
	movzx	eax, BYTE PTR [rsp+32]
	add	eax, 48
	mov	BYTE PTR [rsp+10], al
	movzx	eax, BYTE PTR [rsp+40]
	add	eax, 48
	mov	BYTE PTR [rsp+11], al
	movzx	eax, BYTE PTR [rsp+48]
	add	eax, 48
	mov	BYTE PTR [rsp+13], al
	movzx	eax, BYTE PTR [rsp+56]
	add	eax, 48
	mov	BYTE PTR [rsp+14], al
	xor	eax, eax
	call	printf
	add	rsp, 72
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE1:
	.size	time, .-time
	.section	.text.unlikely
.LCOLDE1:
	.text
.LHOTE1:
	.section	.text.unlikely
.LCOLDB2:
	.text
.LHOTB2:
	.p2align 4,,15
	.globl	division
	.type	division, @function
division:
.LFB2:
	.cfi_startproc
	mov	eax, 666
	cdq
	idiv	edi
	ret
	.cfi_endproc
.LFE2:
	.size	division, .-division
	.section	.text.unlikely
.LCOLDE2:
	.text
.LHOTE2:
	.section	.text.unlikely
.LCOLDB3:
	.text
.LHOTB3:
	.p2align 4,,15
	.globl	divisionExc
	.type	divisionExc, @function
divisionExc:
.LFB3:
	.cfi_startproc
	rep ret
	.cfi_endproc
.LFE3:
	.size	divisionExc, .-divisionExc
	.section	.text.unlikely
.LCOLDE3:
	.text
.LHOTE3:
	.section	.text.unlikely
.LCOLDB4:
	.text
.LHOTB4:
	.p2align 4,,15
	.globl	invalidOpCodeException
	.type	invalidOpCodeException, @function
invalidOpCodeException:
.LFB4:
	.cfi_startproc
	xor	eax, eax
	jmp	invalidOpCode
	.cfi_endproc
.LFE4:
	.size	invalidOpCodeException, .-invalidOpCodeException
	.section	.text.unlikely
.LCOLDE4:
	.text
.LHOTE4:
	.section	.text.unlikely
.LCOLDB5:
	.text
.LHOTB5:
	.p2align 4,,15
	.globl	usedMem
	.type	usedMem, @function
usedMem:
.LFB5:
	.cfi_startproc
	xor	eax, eax
	jmp	sys_usedMem
	.cfi_endproc
.LFE5:
	.size	usedMem, .-usedMem
	.section	.text.unlikely
.LCOLDE5:
	.text
.LHOTE5:
	.section	.text.unlikely
.LCOLDB6:
	.text
.LHOTB6:
	.p2align 4,,15
	.globl	freeMem
	.type	freeMem, @function
freeMem:
.LFB6:
	.cfi_startproc
	xor	eax, eax
	jmp	sys_freeMem
	.cfi_endproc
.LFE6:
	.size	freeMem, .-freeMem
	.section	.text.unlikely
.LCOLDE6:
	.text
.LHOTE6:
	.ident	"GCC: (Debian 4.9.2-10+deb8u1) 4.9.2"
	.section	.note.GNU-stack,"",@progbits

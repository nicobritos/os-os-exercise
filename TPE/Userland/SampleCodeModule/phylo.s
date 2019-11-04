	.file	"phylo.c"
	.intel_syntax noprefix
	.section	.text.unlikely,"ax",@progbits
.LCOLDB0:
	.text
.LHOTB0:
	.p2align 4,,15
	.globl	phylo
	.type	phylo, @function
phylo:
.LFB4:
	.cfi_startproc
	cmp	edi, 3
	je	.L7
	mov	eax, 1
	ret
.L7:
	mov	rax, QWORD PTR [rsi]
	push	r12
	.cfi_def_cfa_offset 16
	.cfi_offset 12, -16
	push	rbp
	.cfi_def_cfa_offset 24
	.cfi_offset 6, -24
	push	rbx
	.cfi_def_cfa_offset 32
	.cfi_offset 3, -32
	mov	rbp, QWORD PTR [rsi+16]
	mov	rbx, QWORD PTR [rsi+8]
	movsx	r12, BYTE PTR [rax]
	.p2align 4,,10
	.p2align 3
.L3:
	mov	edi, 5000
	call	sleep
	mov	rdi, QWORD PTR [rbx]
	call	sys_wait_semaphore
	mov	rdi, QWORD PTR [rbp+0]
	mov	QWORD PTR [rbx+8], r12
	call	sys_wait_semaphore
	mov	QWORD PTR [rbp+8], r12
	mov	edi, 5000
	call	sleep
	mov	rdi, QWORD PTR [rbx]
	mov	QWORD PTR [rbx+8], -1
	mov	QWORD PTR [rbp+8], -1
	call	sys_post_semaphore
	jmp	.L3
	.cfi_endproc
.LFE4:
	.size	phylo, .-phylo
	.section	.text.unlikely
.LCOLDE0:
	.text
.LHOTE0:
	.section	.text.unlikely
.LCOLDB1:
	.text
.LHOTB1:
	.p2align 4,,15
	.globl	createPhylo
	.type	createPhylo, @function
createPhylo:
.LFB2:
	.cfi_startproc
	push	r12
	.cfi_def_cfa_offset 16
	.cfi_offset 12, -16
	push	rbp
	.cfi_def_cfa_offset 24
	.cfi_offset 6, -24
	movabs	rax, 13563770516434758
	push	rbx
	.cfi_def_cfa_offset 32
	.cfi_offset 3, -32
	mov	ebx, 1717986919
	sub	rsp, 80
	.cfi_def_cfa_offset 112
	movsx	rbp, DWORD PTR currentQty[rip]
	mov	QWORD PTR [rsp+15], rax
	mov	eax, ebp
	mov	edi, ebp
	imul	ebx
	mov	eax, ebp
	sal	rbp, 4
	sar	eax, 31
	sar	edx, 2
	sub	edx, eax
	lea	eax, [rdx+48]
	mov	BYTE PTR [rsp+20], al
	lea	eax, [rdx+rdx*4]
	add	eax, eax
	sub	edi, eax
	mov	eax, edi
	lea	rdi, [rsp+15]
	add	eax, 48
	mov	BYTE PTR [rsp+21], al
	call	sys_createSem
	mov	QWORD PTR forks[rbp], rax
	movsx	rax, DWORD PTR currentQty[rip]
	sal	rax, 4
	mov	rdi, QWORD PTR forks[rax]
	call	sys_post_semaphore
	movsx	rbp, DWORD PTR currentQty[rip]
	movabs	rax, 3472325269287168080
	lea	rcx, [rsp+32]
	mov	QWORD PTR [rsp+23], rax
	lea	rdi, [rsp+23]
	mov	r8d, 1
	mov	eax, ebp
	mov	rsi, rbp
	mov	DWORD PTR phylosIds[0+rbp*4], ebp
	imul	ebx
	mov	eax, ebp
	mov	ebx, ebp
	sar	eax, 31
	sal	rsi, 4
	mov	QWORD PTR forks[rsi+8], -1
	add	rsi, OFFSET FLAT:forks
	sar	edx, 2
	mov	QWORD PTR [rsp+40], rsi
	mov	esi, OFFSET FLAT:phylo
	sub	edx, eax
	lea	eax, [rdx+48]
	mov	BYTE PTR [rsp+30], al
	lea	eax, [rdx+rdx*4]
	add	eax, eax
	sub	ebx, eax
	mov	eax, ebx
	add	eax, 48
	mov	BYTE PTR [rsp+31], al
	lea	rax, phylosIds[0+rbp*4]
	mov	QWORD PTR [rsp+32], rax
	lea	eax, [rbp+1]
	cdq
	idiv	eax
	movsx	rdx, edx
	sal	rdx, 4
	add	rdx, OFFSET FLAT:forks
	mov	QWORD PTR [rsp+48], rdx
	mov	edx, 3
	call	sys_newProcess
	mov	QWORD PTR phylosPids[0+rbp*8], rax
	mov	eax, DWORD PTR currentQty[rip]
	test	eax, eax
	je	.L9
	sub	eax, 1
	xor	ebp, ebp
	cdqe
	mov	rdx, rax
	sal	rdx, 4
	cmp	QWORD PTR forks[rdx+8], rax
	je	.L26
.L10:
	xor	ebx, ebx
	cmp	QWORD PTR forks[rip+8], rax
	je	.L27
.L11:
	mov	rdi, QWORD PTR phylosPids[0+rax*8]
	call	sys_freeProcess
	movsx	r12, DWORD PTR currentQty[rip]
	mov	edx, 1717986919
	lea	rdi, [rsp+23]
	mov	r8d, 1
	lea	ecx, [r12-1]
	mov	eax, ecx
	mov	esi, ecx
	imul	edx
	mov	eax, ecx
	sar	eax, 31
	sar	edx, 2
	sub	edx, eax
	lea	eax, [rdx+48]
	mov	BYTE PTR [rsp+30], al
	lea	eax, [rdx+rdx*4]
	movsx	rdx, ecx
	mov	DWORD PTR phylosIds[0+rdx*4], ecx
	lea	rcx, [rsp+56]
	add	eax, eax
	sub	esi, eax
	mov	eax, esi
	mov	esi, OFFSET FLAT:phylo
	add	eax, 48
	mov	BYTE PTR [rsp+31], al
	lea	rax, phylosIds[0+rdx*4]
	sal	rdx, 4
	add	rdx, OFFSET FLAT:forks
	mov	QWORD PTR [rsp+56], rax
	mov	eax, r12d
	mov	QWORD PTR [rsp+64], rdx
	cdq
	idiv	r12d
	movsx	rdx, edx
	sal	rdx, 4
	add	rdx, OFFSET FLAT:forks
	mov	QWORD PTR [rsp+72], rdx
	mov	edx, 3
	call	sys_newProcess
	test	bpl, bpl
	mov	QWORD PTR phylosPids[0+r12*8], rax
	jne	.L28
	test	bl, bl
	jne	.L29
.L13:
	mov	eax, DWORD PTR currentQty[rip]
.L9:
	add	eax, 1
	mov	DWORD PTR currentQty[rip], eax
	add	rsp, 80
	.cfi_remember_state
	.cfi_def_cfa_offset 32
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
	.p2align 4,,10
	.p2align 3
.L29:
	.cfi_restore_state
	mov	rdi, QWORD PTR forks[rip]
	call	sys_post_semaphore
	jmp	.L13
	.p2align 4,,10
	.p2align 3
.L28:
	mov	eax, DWORD PTR currentQty[rip]
	sub	eax, 1
	cdqe
	sal	rax, 4
	mov	rdi, QWORD PTR forks[rax]
	call	sys_post_semaphore
	test	bl, bl
	je	.L13
	jmp	.L29
	.p2align 4,,10
	.p2align 3
.L26:
	mov	rdi, QWORD PTR forks[rdx]
	mov	ebp, 1
	call	sys_wait_semaphore
	mov	eax, DWORD PTR currentQty[rip]
	sub	eax, 1
	cdqe
	jmp	.L10
	.p2align 4,,10
	.p2align 3
.L27:
	mov	rdi, QWORD PTR forks[rip]
	mov	ebx, 1
	call	sys_wait_semaphore
	mov	eax, DWORD PTR currentQty[rip]
	sub	eax, 1
	cdqe
	jmp	.L11
	.cfi_endproc
.LFE2:
	.size	createPhylo, .-createPhylo
	.section	.text.unlikely
.LCOLDE1:
	.text
.LHOTE1:
	.section	.text.unlikely
.LCOLDB2:
	.text
.LHOTB2:
	.p2align 4,,15
	.globl	addPhylo
	.type	addPhylo, @function
addPhylo:
.LFB1:
	.cfi_startproc
	cmp	DWORD PTR currentQty[rip], 99
	jle	.L32
	rep ret
	.p2align 4,,10
	.p2align 3
.L32:
	xor	eax, eax
	jmp	createPhylo
	.cfi_endproc
.LFE1:
	.size	addPhylo, .-addPhylo
	.section	.text.unlikely
.LCOLDE2:
	.text
.LHOTE2:
	.section	.text.unlikely
.LCOLDB3:
	.text
.LHOTB3:
	.p2align 4,,15
	.globl	removePhylo
	.type	removePhylo, @function
removePhylo:
.LFB3:
	.cfi_startproc
	sub	rsp, 8
	.cfi_def_cfa_offset 16
	mov	eax, DWORD PTR currentQty[rip]
	sub	eax, 1
	mov	DWORD PTR currentQty[rip], eax
	cdqe
	sal	rax, 4
	mov	rdi, QWORD PTR forks[rax]
	call	sys_closeSem
	movsx	rax, DWORD PTR currentQty[rip]
	movsx	rdx, DWORD PTR phylosIds[0+rax*4]
	cmp	QWORD PTR forks[rip+8], rdx
	je	.L36
	mov	rdi, QWORD PTR phylosPids[0+rax*8]
	add	rsp, 8
	.cfi_remember_state
	.cfi_def_cfa_offset 8
	jmp	sys_freeProcess
	.p2align 4,,10
	.p2align 3
.L36:
	.cfi_restore_state
	mov	rdi, QWORD PTR phylosPids[0+rax*8]
	mov	QWORD PTR forks[rip+8], -1
	call	sys_freeProcess
	mov	rdi, QWORD PTR forks[rip]
	add	rsp, 8
	.cfi_def_cfa_offset 8
	jmp	sys_post_semaphore
	.cfi_endproc
.LFE3:
	.size	removePhylo, .-removePhylo
	.section	.text.unlikely
.LCOLDE3:
	.text
.LHOTE3:
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC4:
	.string	"WAITING FORK"
.LC5:
	.string	"THINKING"
.LC6:
	.string	"EATING"
.LC7:
	.string	"NADIE"
.LC8:
	.string	"Filosofo %d: %s\n"
.LC9:
	.string	"Cubierto %d: USADO POR %s\n"
	.section	.text.unlikely
.LCOLDB10:
	.text
.LHOTB10:
	.p2align 4,,15
	.globl	printTable
	.type	printTable, @function
printTable:
.LFB5:
	.cfi_startproc
	mov	ecx, DWORD PTR currentQty[rip]
	test	ecx, ecx
	jle	.L49
	push	r15
	.cfi_def_cfa_offset 16
	.cfi_offset 15, -16
	push	r14
	.cfi_def_cfa_offset 24
	.cfi_offset 14, -24
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
	xor	ebp, ebp
	mov	ebx, OFFSET FLAT:forks+8
	sub	rsp, 24
	.cfi_def_cfa_offset 80
	lea	r14, [rsp+4]
	lea	r15, [r14+9]
	jmp	.L42
	.p2align 4,,10
	.p2align 3
.L40:
	mov	edi, OFFSET FLAT:.LC8
	xor	eax, eax
	call	printf
	mov	edi, DWORD PTR [rbx]
	movabs	rax, 8027225927415785798
	mov	edx, 10
	mov	rsi, r15
	mov	QWORD PTR [rsp+4], rax
	mov	DWORD PTR [rsp+12], 3158048
	call	itoa
	cmp	QWORD PTR [rbx], -1
	mov	edx, OFFSET FLAT:.LC7
	mov	esi, r13d
	mov	edi, OFFSET FLAT:.LC9
	cmovne	rdx, r14
	xor	eax, eax
	add	rbp, 1
	call	printf
	mov	ecx, DWORD PTR currentQty[rip]
	add	rbx, 16
	cmp	ecx, r12d
	jle	.L50
.L42:
	movsx	rax, DWORD PTR phylosIds[0+rbp*4]
	mov	rdi, QWORD PTR [rbx]
	mov	r13d, ebp
	lea	r12d, [rbp+1]
	mov	edx, OFFSET FLAT:.LC5
	cmp	rdi, rax
	mov	rsi, rax
	jne	.L40
	mov	eax, r12d
	cdq
	idiv	ecx
	mov	eax, OFFSET FLAT:.LC6
	movsx	rdx, edx
	sal	rdx, 4
	cmp	rdi, QWORD PTR forks[rdx+8]
	mov	edx, OFFSET FLAT:.LC4
	cmove	rdx, rax
	jmp	.L40
.L50:
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
.L49:
	rep ret
	.cfi_endproc
.LFE5:
	.size	printTable, .-printTable
	.section	.text.unlikely
.LCOLDE10:
	.text
.LHOTE10:
	.section	.rodata.str1.1
.LC11:
	.string	"\nToy"
	.section	.text.unlikely
.LCOLDB12:
	.text
.LHOTB12:
	.p2align 4,,15
	.globl	phyloProblem
	.type	phyloProblem, @function
phyloProblem:
.LFB0:
	.cfi_startproc
	mov	rax, QWORD PTR [rsi]
	cmp	eax, 100
	jg	.L70
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	push	rbx
	.cfi_def_cfa_offset 24
	.cfi_offset 3, -24
	xor	ebx, ebx
	mov	ebp, eax
	sub	rsp, 24
	.cfi_def_cfa_offset 48
	test	eax, eax
	jle	.L60
.L71:
	xor	eax, eax
	add	ebx, 1
	call	createPhylo
	cmp	ebp, ebx
	jne	.L71
	.p2align 4,,10
	.p2align 3
.L60:
	lea	rdi, [rsp+13]
	mov	edx, 10
	mov	esi, 2
	call	scanf
	xor	eax, eax
	mov	edi, OFFSET FLAT:.LC11
	call	printf
	movzx	eax, BYTE PTR [rsp+13]
	cmp	al, 82
	je	.L57
	jle	.L79
	cmp	al, 97
	je	.L59
	cmp	al, 114
	jne	.L56
.L57:
	xor	eax, eax
	call	removePhylo
	jmp	.L60
	.p2align 4,,10
	.p2align 3
.L79:
	cmp	al, 65
	jne	.L56
.L59:
	cmp	DWORD PTR currentQty[rip], 99
	jg	.L60
	xor	eax, eax
	call	createPhylo
	jmp	.L60
	.p2align 4,,10
	.p2align 3
.L56:
	xor	eax, eax
	call	printTable
	jmp	.L60
.L70:
	.cfi_def_cfa_offset 8
	.cfi_restore 3
	.cfi_restore 6
	mov	eax, -1
	ret
	.cfi_endproc
.LFE0:
	.size	phyloProblem, .-phyloProblem
	.section	.text.unlikely
.LCOLDE12:
	.text
.LHOTE12:
	.globl	phylosIds
	.bss
	.align 64
	.type	phylosIds, @object
	.size	phylosIds, 400
phylosIds:
	.zero	400
	.globl	phylosPids
	.align 64
	.type	phylosPids, @object
	.size	phylosPids, 800
phylosPids:
	.zero	800
	.globl	currentQty
	.align 4
	.type	currentQty, @object
	.size	currentQty, 4
currentQty:
	.zero	4
	.globl	forks
	.align 64
	.type	forks, @object
	.size	forks, 1600
forks:
	.zero	1600
	.ident	"GCC: (Debian 4.9.2-10+deb8u1) 4.9.2"
	.section	.note.GNU-stack,"",@progbits

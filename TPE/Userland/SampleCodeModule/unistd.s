	.file	"unistd.c"
	.intel_syntax noprefix
	.section	.text.unlikely,"ax",@progbits
.LCOLDB0:
	.text
.LHOTB0:
	.p2align 4,,15
	.globl	newProcessArgs
	.type	newProcessArgs, @function
newProcessArgs:
.LFB0:
	.cfi_startproc
	jmp	sys_newProcess
	.cfi_endproc
.LFE0:
	.size	newProcessArgs, .-newProcessArgs
	.section	.text.unlikely
.LCOLDE0:
	.text
.LHOTE0:
	.section	.text.unlikely
.LCOLDB1:
	.text
.LHOTB1:
	.p2align 4,,15
	.globl	newProcess
	.type	newProcess, @function
newProcess:
.LFB1:
	.cfi_startproc
	mov	r8d, edx
	xor	ecx, ecx
	xor	edx, edx
	jmp	sys_newProcess
	.cfi_endproc
.LFE1:
	.size	newProcess, .-newProcess
	.section	.text.unlikely
.LCOLDE1:
	.text
.LHOTE1:
	.section	.text.unlikely
.LCOLDB2:
	.text
.LHOTB2:
	.p2align 4,,15
	.globl	freeProcess
	.type	freeProcess, @function
freeProcess:
.LFB2:
	.cfi_startproc
	jmp	sys_freeProcess
	.cfi_endproc
.LFE2:
	.size	freeProcess, .-freeProcess
	.section	.text.unlikely
.LCOLDE2:
	.text
.LHOTE2:
	.section	.text.unlikely
.LCOLDB3:
	.text
.LHOTB3:
	.p2align 4,,15
	.globl	getPid
	.type	getPid, @function
getPid:
.LFB3:
	.cfi_startproc
	sub	rsp, 8
	.cfi_def_cfa_offset 16
	xor	eax, eax
	call	sys_getPid
	add	rsp, 8
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE3:
	.size	getPid, .-getPid
	.section	.text.unlikely
.LCOLDE3:
	.text
.LHOTE3:
	.section	.text.unlikely
.LCOLDB4:
	.text
.LHOTB4:
	.p2align 4,,15
	.globl	waitpid
	.type	waitpid, @function
waitpid:
.LFB4:
	.cfi_startproc
	jmp	sys_wait_pid
	.cfi_endproc
.LFE4:
	.size	waitpid, .-waitpid
	.section	.text.unlikely
.LCOLDE4:
	.text
.LHOTE4:
	.section	.text.unlikely
.LCOLDB5:
	.text
.LHOTB5:
	.p2align 4,,15
	.globl	killProcess
	.type	killProcess, @function
killProcess:
.LFB5:
	.cfi_startproc
	jmp	sys_freeProcess
	.cfi_endproc
.LFE5:
	.size	killProcess, .-killProcess
	.section	.text.unlikely
.LCOLDE5:
	.text
.LHOTE5:
	.section	.text.unlikely
.LCOLDB6:
	.text
.LHOTB6:
	.p2align 4,,15
	.globl	setProcessMode
	.type	setProcessMode, @function
setProcessMode:
.LFB6:
	.cfi_startproc
	jmp	sys_set_process_mode
	.cfi_endproc
.LFE6:
	.size	setProcessMode, .-setProcessMode
	.section	.text.unlikely
.LCOLDE6:
	.text
.LHOTE6:
	.section	.text.unlikely
.LCOLDB7:
	.text
.LHOTB7:
	.p2align 4,,15
	.globl	setProcessPriority
	.type	setProcessPriority, @function
setProcessPriority:
.LFB7:
	.cfi_startproc
	jmp	sys_set_process_priority
	.cfi_endproc
.LFE7:
	.size	setProcessPriority, .-setProcessPriority
	.section	.text.unlikely
.LCOLDE7:
	.text
.LHOTE7:
	.section	.text.unlikely
.LCOLDB8:
	.text
.LHOTB8:
	.p2align 4,,15
	.globl	toogleProcessLock
	.type	toogleProcessLock, @function
toogleProcessLock:
.LFB8:
	.cfi_startproc
	jmp	sys_toggle_process_lock
	.cfi_endproc
.LFE8:
	.size	toogleProcessLock, .-toogleProcessLock
	.section	.text.unlikely
.LCOLDE8:
	.text
.LHOTE8:
	.section	.text.unlikely
.LCOLDB9:
	.text
.LHOTB9:
	.p2align 4,,15
	.globl	sleep
	.type	sleep, @function
sleep:
.LFB9:
	.cfi_startproc
	jmp	sys_sleep
	.cfi_endproc
.LFE9:
	.size	sleep, .-sleep
	.section	.text.unlikely
.LCOLDE9:
	.text
.LHOTE9:
	.ident	"GCC: (Debian 4.9.2-10+deb8u1) 4.9.2"
	.section	.note.GNU-stack,"",@progbits

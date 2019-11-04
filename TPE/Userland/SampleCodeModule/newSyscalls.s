	.file	"newSyscalls.c"
	.intel_syntax noprefix
	.section	.text.unlikely,"ax",@progbits
.LCOLDB0:
	.text
.LHOTB0:
	.p2align 4,,15
	.globl	sys_read
	.type	sys_read, @function
sys_read:
.LFB0:
	.cfi_startproc
	mov	ecx, edx
	xor	eax, eax
	mov	rdx, rsi
	mov	esi, edi
	xor	edi, edi
	jmp	_systemCall
	.cfi_endproc
.LFE0:
	.size	sys_read, .-sys_read
	.section	.text.unlikely
.LCOLDE0:
	.text
.LHOTE0:
	.section	.text.unlikely
.LCOLDB1:
	.text
.LHOTB1:
	.p2align 4,,15
	.globl	sys_write
	.type	sys_write, @function
sys_write:
.LFB1:
	.cfi_startproc
	mov	ecx, edx
	xor	eax, eax
	mov	rdx, rsi
	mov	esi, edi
	mov	edi, 1
	jmp	_systemCall
	.cfi_endproc
.LFE1:
	.size	sys_write, .-sys_write
	.section	.text.unlikely
.LCOLDE1:
	.text
.LHOTE1:
	.section	.text.unlikely
.LCOLDB2:
	.text
.LHOTB2:
	.p2align 4,,15
	.globl	sys_clear
	.type	sys_clear, @function
sys_clear:
.LFB2:
	.cfi_startproc
	mov	edi, 2
	xor	eax, eax
	jmp	_systemCall
	.cfi_endproc
.LFE2:
	.size	sys_clear, .-sys_clear
	.section	.text.unlikely
.LCOLDE2:
	.text
.LHOTE2:
	.section	.text.unlikely
.LCOLDB3:
	.text
.LHOTB3:
	.p2align 4,,15
	.globl	sys_draw
	.type	sys_draw, @function
sys_draw:
.LFB3:
	.cfi_startproc
	mov	r9d, r8d
	xor	eax, eax
	mov	r8d, ecx
	mov	ecx, edx
	mov	edx, esi
	mov	esi, edi
	mov	edi, 3
	jmp	_systemCall
	.cfi_endproc
.LFE3:
	.size	sys_draw, .-sys_draw
	.section	.text.unlikely
.LCOLDE3:
	.text
.LHOTE3:
	.section	.text.unlikely
.LCOLDB4:
	.text
.LHOTB4:
	.p2align 4,,15
	.globl	sys_time
	.type	sys_time, @function
sys_time:
.LFB4:
	.cfi_startproc
	mov	rsi, rdi
	xor	eax, eax
	mov	edi, 4
	jmp	_systemCall
	.cfi_endproc
.LFE4:
	.size	sys_time, .-sys_time
	.section	.text.unlikely
.LCOLDE4:
	.text
.LHOTE4:
	.section	.text.unlikely
.LCOLDB5:
	.text
.LHOTB5:
	.p2align 4,,15
	.globl	sys_getPid
	.type	sys_getPid, @function
sys_getPid:
.LFB5:
	.cfi_startproc
	mov	edi, 5
	xor	eax, eax
	jmp	_systemCall
	.cfi_endproc
.LFE5:
	.size	sys_getPid, .-sys_getPid
	.section	.text.unlikely
.LCOLDE5:
	.text
.LHOTE5:
	.section	.text.unlikely
.LCOLDB6:
	.text
.LHOTB6:
	.p2align 4,,15
	.globl	sys_newProcess
	.type	sys_newProcess, @function
sys_newProcess:
.LFB6:
	.cfi_startproc
	mov	r8, rcx
	xor	eax, eax
	mov	ecx, edx
	mov	rdx, rsi
	mov	rsi, rdi
	mov	edi, 6
	jmp	_systemCall
	.cfi_endproc
.LFE6:
	.size	sys_newProcess, .-sys_newProcess
	.section	.text.unlikely
.LCOLDE6:
	.text
.LHOTE6:
	.section	.text.unlikely
.LCOLDB7:
	.text
.LHOTB7:
	.p2align 4,,15
	.globl	sys_freeProcess
	.type	sys_freeProcess, @function
sys_freeProcess:
.LFB7:
	.cfi_startproc
	mov	rsi, rdi
	xor	eax, eax
	mov	edi, 7
	jmp	_systemCall
	.cfi_endproc
.LFE7:
	.size	sys_freeProcess, .-sys_freeProcess
	.section	.text.unlikely
.LCOLDE7:
	.text
.LHOTE7:
	.section	.text.unlikely
.LCOLDB8:
	.text
.LHOTB8:
	.p2align 4,,15
	.globl	sys_free
	.type	sys_free, @function
sys_free:
.LFB8:
	.cfi_startproc
	mov	rsi, rdi
	xor	eax, eax
	mov	edi, 8
	jmp	_systemCall
	.cfi_endproc
.LFE8:
	.size	sys_free, .-sys_free
	.section	.text.unlikely
.LCOLDE8:
	.text
.LHOTE8:
	.section	.text.unlikely
.LCOLDB9:
	.text
.LHOTB9:
	.p2align 4,,15
	.globl	sys_ticks
	.type	sys_ticks, @function
sys_ticks:
.LFB9:
	.cfi_startproc
	mov	rsi, rdi
	xor	eax, eax
	mov	edi, 9
	jmp	_systemCall
	.cfi_endproc
.LFE9:
	.size	sys_ticks, .-sys_ticks
	.section	.text.unlikely
.LCOLDE9:
	.text
.LHOTE9:
	.section	.text.unlikely
.LCOLDB10:
	.text
.LHOTB10:
	.p2align 4,,15
	.globl	sys_ticksPerSecond
	.type	sys_ticksPerSecond, @function
sys_ticksPerSecond:
.LFB10:
	.cfi_startproc
	mov	rsi, rdi
	xor	eax, eax
	mov	edi, 10
	jmp	_systemCall
	.cfi_endproc
.LFE10:
	.size	sys_ticksPerSecond, .-sys_ticksPerSecond
	.section	.text.unlikely
.LCOLDE10:
	.text
.LHOTE10:
	.section	.text.unlikely
.LCOLDB11:
	.text
.LHOTB11:
	.p2align 4,,15
	.globl	sys_usedMem
	.type	sys_usedMem, @function
sys_usedMem:
.LFB11:
	.cfi_startproc
	mov	edi, 11
	xor	eax, eax
	jmp	_systemCall
	.cfi_endproc
.LFE11:
	.size	sys_usedMem, .-sys_usedMem
	.section	.text.unlikely
.LCOLDE11:
	.text
.LHOTE11:
	.section	.text.unlikely
.LCOLDB12:
	.text
.LHOTB12:
	.p2align 4,,15
	.globl	sys_freeMem
	.type	sys_freeMem, @function
sys_freeMem:
.LFB12:
	.cfi_startproc
	mov	edi, 12
	xor	eax, eax
	jmp	_systemCall
	.cfi_endproc
.LFE12:
	.size	sys_freeMem, .-sys_freeMem
	.section	.text.unlikely
.LCOLDE12:
	.text
.LHOTE12:
	.section	.text.unlikely
.LCOLDB13:
	.text
.LHOTB13:
	.p2align 4,,15
	.globl	sys_malloc
	.type	sys_malloc, @function
sys_malloc:
.LFB13:
	.cfi_startproc
	mov	rsi, rdi
	xor	eax, eax
	mov	edi, 13
	jmp	_systemCall
	.cfi_endproc
.LFE13:
	.size	sys_malloc, .-sys_malloc
	.section	.text.unlikely
.LCOLDE13:
	.text
.LHOTE13:
	.section	.text.unlikely
.LCOLDB14:
	.text
.LHOTB14:
	.p2align 4,,15
	.globl	sys_yield
	.type	sys_yield, @function
sys_yield:
.LFB14:
	.cfi_startproc
	mov	edi, 14
	xor	eax, eax
	jmp	_systemCall
	.cfi_endproc
.LFE14:
	.size	sys_yield, .-sys_yield
	.section	.text.unlikely
.LCOLDE14:
	.text
.LHOTE14:
	.section	.text.unlikely
.LCOLDB15:
	.text
.LHOTB15:
	.p2align 4,,15
	.globl	sys_get_process_mode
	.type	sys_get_process_mode, @function
sys_get_process_mode:
.LFB15:
	.cfi_startproc
	sub	rsp, 8
	.cfi_def_cfa_offset 16
	mov	rsi, rdi
	xor	eax, eax
	mov	edi, 15
	call	_systemCall
	add	rsp, 8
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE15:
	.size	sys_get_process_mode, .-sys_get_process_mode
	.section	.text.unlikely
.LCOLDE15:
	.text
.LHOTE15:
	.section	.text.unlikely
.LCOLDB16:
	.text
.LHOTB16:
	.p2align 4,,15
	.globl	sys_set_process_mode
	.type	sys_set_process_mode, @function
sys_set_process_mode:
.LFB16:
	.cfi_startproc
	mov	edx, esi
	xor	eax, eax
	mov	rsi, rdi
	mov	edi, 16
	jmp	_systemCall
	.cfi_endproc
.LFE16:
	.size	sys_set_process_mode, .-sys_set_process_mode
	.section	.text.unlikely
.LCOLDE16:
	.text
.LHOTE16:
	.section	.text.unlikely
.LCOLDB17:
	.text
.LHOTB17:
	.p2align 4,,15
	.globl	sys_get_process_priority
	.type	sys_get_process_priority, @function
sys_get_process_priority:
.LFB17:
	.cfi_startproc
	sub	rsp, 8
	.cfi_def_cfa_offset 16
	mov	rsi, rdi
	xor	eax, eax
	mov	edi, 17
	call	_systemCall
	add	rsp, 8
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE17:
	.size	sys_get_process_priority, .-sys_get_process_priority
	.section	.text.unlikely
.LCOLDE17:
	.text
.LHOTE17:
	.section	.text.unlikely
.LCOLDB18:
	.text
.LHOTB18:
	.p2align 4,,15
	.globl	sys_set_process_priority
	.type	sys_set_process_priority, @function
sys_set_process_priority:
.LFB18:
	.cfi_startproc
	mov	edx, esi
	xor	eax, eax
	mov	rsi, rdi
	mov	edi, 18
	jmp	_systemCall
	.cfi_endproc
.LFE18:
	.size	sys_set_process_priority, .-sys_set_process_priority
	.section	.text.unlikely
.LCOLDE18:
	.text
.LHOTE18:
	.section	.text.unlikely
.LCOLDB19:
	.text
.LHOTB19:
	.p2align 4,,15
	.globl	sys_get_process_state
	.type	sys_get_process_state, @function
sys_get_process_state:
.LFB19:
	.cfi_startproc
	sub	rsp, 8
	.cfi_def_cfa_offset 16
	mov	rsi, rdi
	xor	eax, eax
	mov	edi, 19
	call	_systemCall
	add	rsp, 8
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE19:
	.size	sys_get_process_state, .-sys_get_process_state
	.section	.text.unlikely
.LCOLDE19:
	.text
.LHOTE19:
	.section	.text.unlikely
.LCOLDB20:
	.text
.LHOTB20:
	.p2align 4,,15
	.globl	sys_readPipe
	.type	sys_readPipe, @function
sys_readPipe:
.LFB20:
	.cfi_startproc
	sub	rsp, 8
	.cfi_def_cfa_offset 16
	mov	rcx, rdx
	xor	eax, eax
	mov	rdx, rsi
	mov	rsi, rdi
	mov	edi, 20
	call	_systemCall
	add	rsp, 8
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE20:
	.size	sys_readPipe, .-sys_readPipe
	.section	.text.unlikely
.LCOLDE20:
	.text
.LHOTE20:
	.section	.text.unlikely
.LCOLDB21:
	.text
.LHOTB21:
	.p2align 4,,15
	.globl	sys_writePipe
	.type	sys_writePipe, @function
sys_writePipe:
.LFB21:
	.cfi_startproc
	sub	rsp, 8
	.cfi_def_cfa_offset 16
	mov	rcx, rdx
	xor	eax, eax
	mov	rdx, rsi
	mov	rsi, rdi
	mov	edi, 21
	call	_systemCall
	add	rsp, 8
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE21:
	.size	sys_writePipe, .-sys_writePipe
	.section	.text.unlikely
.LCOLDE21:
	.text
.LHOTE21:
	.section	.text.unlikely
.LCOLDB22:
	.text
.LHOTB22:
	.p2align 4,,15
	.globl	sys_createSem
	.type	sys_createSem, @function
sys_createSem:
.LFB22:
	.cfi_startproc
	mov	rsi, rdi
	xor	eax, eax
	mov	edi, 22
	jmp	_systemCall
	.cfi_endproc
.LFE22:
	.size	sys_createSem, .-sys_createSem
	.section	.text.unlikely
.LCOLDE22:
	.text
.LHOTE22:
	.section	.text.unlikely
.LCOLDB23:
	.text
.LHOTB23:
	.p2align 4,,15
	.globl	sys_openSem
	.type	sys_openSem, @function
sys_openSem:
.LFB23:
	.cfi_startproc
	mov	rsi, rdi
	xor	eax, eax
	mov	edi, 23
	jmp	_systemCall
	.cfi_endproc
.LFE23:
	.size	sys_openSem, .-sys_openSem
	.section	.text.unlikely
.LCOLDE23:
	.text
.LHOTE23:
	.section	.text.unlikely
.LCOLDB24:
	.text
.LHOTB24:
	.p2align 4,,15
	.globl	sys_closeSem
	.type	sys_closeSem, @function
sys_closeSem:
.LFB24:
	.cfi_startproc
	mov	rsi, rdi
	xor	eax, eax
	mov	edi, 24
	jmp	_systemCall
	.cfi_endproc
.LFE24:
	.size	sys_closeSem, .-sys_closeSem
	.section	.text.unlikely
.LCOLDE24:
	.text
.LHOTE24:
	.section	.text.unlikely
.LCOLDB25:
	.text
.LHOTB25:
	.p2align 4,,15
	.globl	sys_wait_semaphore
	.type	sys_wait_semaphore, @function
sys_wait_semaphore:
.LFB25:
	.cfi_startproc
	mov	rsi, rdi
	xor	eax, eax
	mov	edi, 25
	jmp	_systemCall
	.cfi_endproc
.LFE25:
	.size	sys_wait_semaphore, .-sys_wait_semaphore
	.section	.text.unlikely
.LCOLDE25:
	.text
.LHOTE25:
	.section	.text.unlikely
.LCOLDB26:
	.text
.LHOTB26:
	.p2align 4,,15
	.globl	sys_post_semaphore
	.type	sys_post_semaphore, @function
sys_post_semaphore:
.LFB26:
	.cfi_startproc
	mov	rsi, rdi
	xor	eax, eax
	mov	edi, 26
	jmp	_systemCall
	.cfi_endproc
.LFE26:
	.size	sys_post_semaphore, .-sys_post_semaphore
	.section	.text.unlikely
.LCOLDE26:
	.text
.LHOTE26:
	.section	.text.unlikely
.LCOLDB27:
	.text
.LHOTB27:
	.p2align 4,,15
	.globl	sys_printSems
	.type	sys_printSems, @function
sys_printSems:
.LFB27:
	.cfi_startproc
	mov	edi, 27
	xor	eax, eax
	jmp	_systemCall
	.cfi_endproc
.LFE27:
	.size	sys_printSems, .-sys_printSems
	.section	.text.unlikely
.LCOLDE27:
	.text
.LHOTE27:
	.section	.text.unlikely
.LCOLDB28:
	.text
.LHOTB28:
	.p2align 4,,15
	.globl	sys_wait_pid
	.type	sys_wait_pid, @function
sys_wait_pid:
.LFB28:
	.cfi_startproc
	sub	rsp, 8
	.cfi_def_cfa_offset 16
	mov	rsi, rdi
	xor	eax, eax
	mov	edi, 28
	call	_systemCall
	add	rsp, 8
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE28:
	.size	sys_wait_pid, .-sys_wait_pid
	.section	.text.unlikely
.LCOLDE28:
	.text
.LHOTE28:
	.section	.text.unlikely
.LCOLDB29:
	.text
.LHOTB29:
	.p2align 4,,15
	.globl	sys_printProcesses
	.type	sys_printProcesses, @function
sys_printProcesses:
.LFB29:
	.cfi_startproc
	mov	edi, 29
	xor	eax, eax
	jmp	_systemCall
	.cfi_endproc
.LFE29:
	.size	sys_printProcesses, .-sys_printProcesses
	.section	.text.unlikely
.LCOLDE29:
	.text
.LHOTE29:
	.section	.text.unlikely
.LCOLDB30:
	.text
.LHOTB30:
	.p2align 4,,15
	.globl	sys_toggle_process_lock
	.type	sys_toggle_process_lock, @function
sys_toggle_process_lock:
.LFB30:
	.cfi_startproc
	sub	rsp, 8
	.cfi_def_cfa_offset 16
	mov	rsi, rdi
	xor	eax, eax
	mov	edi, 30
	call	_systemCall
	add	rsp, 8
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE30:
	.size	sys_toggle_process_lock, .-sys_toggle_process_lock
	.section	.text.unlikely
.LCOLDE30:
	.text
.LHOTE30:
	.section	.text.unlikely
.LCOLDB31:
	.text
.LHOTB31:
	.p2align 4,,15
	.globl	sys_sleep
	.type	sys_sleep, @function
sys_sleep:
.LFB31:
	.cfi_startproc
	mov	rsi, rdi
	xor	eax, eax
	mov	edi, 31
	jmp	_systemCall
	.cfi_endproc
.LFE31:
	.size	sys_sleep, .-sys_sleep
	.section	.text.unlikely
.LCOLDE31:
	.text
.LHOTE31:
	.ident	"GCC: (Debian 4.9.2-10+deb8u1) 4.9.2"
	.section	.note.GNU-stack,"",@progbits

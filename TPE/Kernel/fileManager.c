//This is a personal academic project. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "include/keyboard-Driver.h"
#include "include/videoDriver.h"
#include "processHandler.h"
#include "fileManager.h"
#include "memManager.h"
#include "list.h"
#include "ipc.h"

#define STARTING_PIPE_FD 2
#define MAX_PIPES 5000

typedef struct fdPipeNodeCDT *fdPipeNodeADT;
typedef struct stdinNodeCDT *stdinNodeADT;

typedef struct stdinNodeCDT {
	uint64_t size;
	char *buffer;
	pid_t pid;
} stdinNodeCDT;

t_pipeADT getFdNode(fd_t fd);
uint64_t readStdin(char *buffer, uint64_t size, t_stack currentProcessStackFrame);
uint64_t writeStdout(char *buffer, uint64_t size);
void processStdinList();

static listADT stdinList = NULL;
static t_pipeADT *pipeList = NULL;

void initializeFileManager() {
	pipeList = pmalloc(sizeof(t_pipeADT) * MAX_PIPES, SYSTEM_PID);

	fd_t fd = 0;
	while (fd < MAX_PIPES) {
		pipeList[fd] = NULL;
		fd++;
	}

	stdinList = createList();
}

fd_t openPipe(const char *name, uint8_t mode, t_process process) {
	fd_t fd = 0;
	while (fd < MAX_PIPES) {
		if (pipeList[fd] == NULL) {
			break;
		}
		fd++;
	}
	if (fd == MAX_PIPES) return -1;

	t_pipeADT pipe = _openPipe(name, mode, process);
	pipeList[fd] = pipe;
	return fd + STARTING_PIPE_FD;
}

void closePipe(fd_t fd, t_process process) {
	if (fd >= STARTING_PIPE_FD && fd < MAX_PIPES - STARTING_PIPE_FD) {
		fd -= STARTING_PIPE_FD;
		_closePipe(pipeList[fd], process);
		pipeList[fd] = NULL;
	}
}

uint64_t readFile(fd_t fd, char *buffer, uint64_t size, t_stack currentProcessStackFrame) {
	if (size == 0) return 0;

	uint64_t i = 0;
	if (fd == STDOUT) return i;
	if (fd == STDIN) return readStdin(buffer, size, currentProcessStackFrame);

	if (fd >= STARTING_PIPE_FD && fd < MAX_PIPES - STARTING_PIPE_FD) {
		fd -= STARTING_PIPE_FD;
		t_pipeADT pipe = getFdNode(fd);
		if (pipe == NULL) return i;
		return readPipe(pipe, buffer, size, currentProcessStackFrame);
	}

	return i;
}

uint64_t writeFile(fd_t fd, char *buffer, uint64_t size, t_stack currentProcessStackFrame) {
	if (size == 0) return 0;

	uint64_t i = 0;
	if (fd == STDIN) return i;
	if (fd == STDOUT) return writeStdout(buffer, size);

	if (fd >= STARTING_PIPE_FD && fd < MAX_PIPES - STARTING_PIPE_FD) {
		fd -= STARTING_PIPE_FD;
		t_pipeADT pipe = getFdNode(fd);
		if (pipe == NULL) return i;
		return writePipe(pipe, buffer, size, currentProcessStackFrame);
	}

	return i;
}

uint64_t writeStdout(char *buffer, uint64_t size) {
	uint64_t i = 0;

	while(size--) {
		char c = *buffer;
		if (c == '\n') {
			newLine();
		} else if (c == '\b') {
			backspace();
		} else {
			printChar(c,0,255,0);
		}
		buffer++;
		i++;
	}

	return i;
}

uint64_t readStdin(char *buffer, uint64_t size, t_stack currentProcessStackFrame) {
	uint64_t i = 0;
	char c;

	if (getSizeList(stdinList) != 0 || !(c = get_key_input())) {
		stdinNodeADT node = pmalloc(sizeof(stdinNodeCDT), SYSTEM_PID);
		node->buffer = buffer;
		node->size = size;
		node->pid = getProcessPid(getCurrentProcess());

		addElementToIndexList(stdinList, node, getSizeList(stdinList));
		lockProcess(node->pid, currentProcessStackFrame);
	} else {
		do {
			buffer[i++] = c;
			size--;			
		} while(size > 0 && (c = get_key_input()));
	}
	
	return i;
}

void keyWasPressed() {
	processStdinList();
}

void processStdinList() {
	nodeListADT node = getNodeAtIndexList(stdinList, 0), nextNode = NULL;
	
	uint8_t finished = 0;
	for(char c = 0; node != NULL && !finished; node = nextNode){
		stdinNodeADT stdinNode = (stdinNodeADT) getElementList(node);
		nextNode = getNextNodeList(node);
		
		uint64_t i = 0;
		while (stdinNode->size > 0 && (c = get_key_input())) {
			stdinNode->buffer[i++] = c;
			stdinNode->size--;
		}
		removeNodeList(stdinList, node);
		unlockProcess(stdinNode->pid);
		pfree(stdinNode, SYSTEM_PID);

		if (!c) finished = 1;
		node = nextNode;
	}
}

t_pipeADT getFdNode(fd_t fd) {
	return pipeList[fd];
}

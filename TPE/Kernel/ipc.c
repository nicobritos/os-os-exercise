//This is a personal academic project. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "include/memManager.h"
#include "include/scheduler.h"
#include "include/process.h"
#include "include/lib.h"
#include "include/ipc.h"

typedef struct t_pipeCDT {
	t_process readingProcess;
	t_process writingProcess;
	char buffer[_PIPE_BUFFER];
	char *readingPointer;
	char *writingPointer;
	char *name;

	t_pipeADT next;
	t_pipeADT previous;
} t_pipeCDT;

typedef struct t_pipe_listCDT {
	t_pipeADT firstPipe;
	t_pipeADT currentPipe;
	uint64_t length;
	uint8_t initialized;
} t_pipe_listCDT;

static t_pipeADT firstPipe = NULL;

t_pipeADT getPreviousPipeWithName(const char *name);

// PUBLIC
t_pipeADT _openPipe(const char *name, uint8_t mode, t_process process) {
	if (name == NULL) return NULL;
	t_pipeADT existingPipe = getPreviousPipeWithName(name);
	t_pipeADT newPipe;

	if (existingPipe == NULL) {
		if (mode & _PIPE_CREATE) {
			newPipe = firstPipe = pmalloc(sizeof(t_pipeCDT), SYSTEM_PID);
			if (newPipe == NULL) return NULL; // TODO: Error
			
			strcpy(newPipe->name,name);
			newPipe->next = newPipe->previous = NULL;
		} else {
			return NULL;
		}
	} else {
		if (strcmp(existingPipe->name, name) == 0) {
			if (mode & _PIPE_CREATE || (mode & _PIPE_READ && existingPipe->readingProcess != NULL) || (mode & _PIPE_WRITE && existingPipe->writingProcess != 0)) {
				return NULL;
			}

			if (mode & _PIPE_READ) {
				existingPipe->readingPointer = existingPipe->buffer;
				existingPipe->readingProcess = process;
			} else if (mode & _PIPE_WRITE) {
				existingPipe->writingPointer = existingPipe->buffer;
				existingPipe->writingProcess = process;
			}

			return existingPipe;
		} else if (mode & _PIPE_CREATE) {
			newPipe = pmalloc(sizeof(t_pipeCDT), SYSTEM_PID);
			if (newPipe == NULL) return NULL; // TODO: Error

			strcpy(newPipe->name, name);
			newPipe->next = existingPipe->next;
			newPipe->previous = existingPipe;
			if (existingPipe->next != NULL) {
				existingPipe->next->previous = newPipe;
			}
		} else {
			return NULL;
		}
	}

	strcpy(newPipe->name, name);
	newPipe->readingPointer = newPipe->writingPointer = newPipe->buffer;
	if (mode & _PIPE_READ) {
		newPipe->readingProcess = process;
	} else if (mode & _PIPE_WRITE) {
		newPipe->writingProcess = process;
	}

	return newPipe;
}

void _closePipe(t_pipeADT pipe, t_process process) {
	if (pipe == NULL) return;
	if (process == pipe->readingProcess) pipe->readingProcess = NULL;
	if (process == pipe->writingProcess) pipe->writingProcess = NULL;

	if (pipe->readingProcess == NULL && pipe->writingProcess == NULL) {
		pfree(pipe, SYSTEM_PID);
	}
}

uint64_t readPipe(t_pipeADT pipe, char *dst, uint64_t length, t_stack currentProcessStackFrame){
	if(pipe->readingPointer == pipe->writingPointer){ // no hay nada mas que leer
		lockProcess(getProcessPid(pipe->readingProcess), currentProcessStackFrame);
	}
	uint64_t i;
	for (i = 0; i < length; i++)
	{
		dst[i] = *(pipe->readingPointer);
		if(pipe->readingPointer == pipe->buffer + _PIPE_BUFFER - 1)
			pipe->readingPointer = pipe->buffer;
		else{
			(pipe->readingPointer)++;
		}
	}
	dst[i] = 0;
	if( (getProcessState(pipe->writingProcess) == P_LOCKED) && (length != 0)){ // genere espacio
		unlockProcess(getProcessPid(pipe->writingProcess));
	}
	return i;
}

uint64_t writePipe(t_pipeADT pipe, char *src, uint64_t length, t_stack currentProcessStackFrame){
	if((pipe->readingPointer + 1 == pipe->writingPointer) || ((pipe->writingPointer == pipe->buffer + _PIPE_BUFFER - 1) && (pipe->readingPointer == pipe->buffer))){ // no hay espacio para escribir
		lockProcess(getProcessPid(pipe->writingProcess), currentProcessStackFrame);
	}
	uint64_t i;
	for (i = 0; i < length; i++)
	{
		*(pipe->writingPointer) = src[i];
		if(pipe->writingPointer == pipe->buffer + _PIPE_BUFFER - 1)
			pipe->writingPointer = pipe->buffer;
		else{
			(pipe->writingPointer)++;
		}
	}
	if((getProcessState(pipe->readingProcess) == P_LOCKED) && (length != 0)){ // hay algo para leer
		unlockProcess(getProcessPid(pipe->readingProcess));
	}
	return i;
}

// PRIVATE
t_pipeADT getPreviousPipeWithName(const char *name) {
	int16_t difference = -1;
	t_pipeADT auxPipe = firstPipe;
	if (auxPipe == NULL) return NULL;

	while (auxPipe->next != NULL && difference < 0) {
		difference = strcmp(auxPipe->name, name);
	}

	if (difference > 0) return auxPipe->previous;
	return auxPipe;
}


t_pipe_listADT createPipeList() {
	t_pipe_listADT pipeList = pmalloc(sizeof(t_pipe_listCDT), SYSTEM_PID);
	pipeList->currentPipe = NULL;
	pipeList->initialized = 0;
	pipeList->length = 0;

	t_pipeADT pipeListNode = NULL;
	t_pipeADT previousPipeListNode = NULL;
	t_pipeADT pipe = firstPipe;
	while (pipe != NULL) {
		if (pipeListNode == NULL) {
			pipeListNode = pipeList->firstPipe = pmalloc(sizeof(t_pipeCDT), SYSTEM_PID);
		} else {
			pipeListNode = pipeListNode->next = pmalloc(sizeof(t_pipeCDT), SYSTEM_PID);
		}

		memcpy(pipeListNode, pipe, sizeof(t_pipeCDT));
		pipeListNode->previous = previousPipeListNode;
		pipeList->length++;
		pipe = pipe->next;
		previousPipeListNode = pipeListNode;
	}
	if (pipeListNode != NULL) {
		pipeListNode->next = NULL;
	}

	return pipeList;
}

uint64_t getPipeListLength(t_pipe_listADT pipeList) {
	if (pipeList != NULL) return pipeList->length;
	return 0;
}

uint8_t hasNextPipe(t_pipe_listADT pipeList) {
	if (pipeList != NULL) {
		if (!pipeList->initialized) {
			return pipeList->firstPipe != NULL;
		} else {
			return pipeList->currentPipe->next != NULL;
		}
	}
	return 0;
}

t_pipeADT getNextPipe(t_pipe_listADT pipeList) {
	if (!hasNextPipe(pipeList)) return NULL;

	if (!pipeList->initialized) {
		pipeList->initialized = 1;
		return pipeList->currentPipe = pipeList->firstPipe;
	}

	if (pipeList->currentPipe == NULL) {
		pipeList->currentPipe = pipeList->firstPipe;
	} else {
		pipeList->currentPipe = pipeList->currentPipe->next;
	}

	return pipeList->currentPipe;
}

void freePipeList(t_pipe_listADT pipeList) {
	t_pipeADT pipeNode;
	t_pipeADT auxPipeNode;

	if (pipeList != NULL) {
		pipeNode = pipeList->firstPipe;
		while (pipeNode != NULL) {
			auxPipeNode = pipeNode->next;
			pfree(pipeNode, SYSTEM_PID);
			pipeNode = auxPipeNode;
		}
		pfree(pipeList, SYSTEM_PID);
	}
}
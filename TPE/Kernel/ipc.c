#include "memManager.h"
#include "process.h"
#include "string.h"
#include "ipc.h"

typedef struct t_pipeCDT {
	int readingPid;
	int writingPid;
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
t_pipeADT openPipe(const char *name, uint8_t mode, int pid) {
	if (name == NULL) return NULL;
	t_pipeADT existingPipe = getPreviousPipeWithName(name);
	t_pipeADT newPipe;

	if (existingPipe == NULL) {
		if (mode & _PIPE_CREATE) {
			newPipe = firstPipe = pmalloc(sizeof(t_pipeCDT), SYSTEM_PID);
			if (newPipe == NULL) return NULL; // TODO: Error
			
			newPipe->name = name;
			newPipe->next = newPipe->previous = NULL;
		} else {
			return NULL;
		}
	} else {
		if (strcmp(existingPipe->name, name) == 0) {
			if (mode & _PIPE_CREATE || (mode & _PIPE_READ && existingPipe->readingPid >= 0) || (mode & _PIPE_WRITE && existingPipe->writingPid >= 0)) {
				return NULL;
			}

			if (mode & _PIPE_READ) {
				existingPipe->readingPointer = existingPipe->buffer;
				existingPipe->readingPid = pid;
			} else if (mode & _PIPE_WRITE) {
				existingPipe->writingPointer = existingPipe->buffer;
				existingPipe->writingPid = pid;
			}

			return existingPipe;
		} else if (mode & _PIPE_CREATE) {
			newPipe = pmalloc(sizeof(t_pipeCDT), SYSTEM_PID);
			if (newPipe == NULL) return NULL; // TODO: Error

			newPipe->name = name;
			newPipe->next = existingPipe->next;
			newPipe->previous = existingPipe;
			if (existingPipe->next != NULL) {
				existingPipe->next->previous = newPipe;
			}
		} else {
			return NULL;
		}
	}

	newPipe->name = name;
	newPipe->readingPointer = newPipe->writingPointer = newPipe->buffer;
	if (mode & _PIPE_READ) {
		newPipe->readingPid = pid;
	} else if (mode & _PIPE_WRITE) {
		newPipe->writingPid = pid;
	}

	return newPipe;
}

void closePipe(t_pipeADT pipe, int pid) {
	if (pipe == NULL) return;
	if (pid == pipe->readingPid) pipe->readingPid = -1;
	if (pid == pipe->writingPid) pipe->writingPid = -1;

	if (pipe->readingPid == -1 && pipe->writingPid == -1) {
		pfree(pipe, SYSTEM_PID);
	}
}

uint64_t read(t_pipeADT pipe, char *dst, uint64_t length){
	if(pipe->readingPointer == pipe->writingPointer){ // no hay nada mas que leer
		blockProcess(pipe->readingPid);
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
	if( (getState(pipe->writingPid) == BLOCKED) && (length != 0)){ // genere espacio
		unlockProcess(pipe->writingPid);
	}
	return i;
}

uint64_t write(t_pipeADT pipe, char *src, uint64_t length){
	if((pipe->readingPointer + 1 == pipe->writingPointer) || ((pipe->writingPointer == pipe->buffer + _PIPE_BUFFER - 1) && (pipe->readingPointer == pipe->buffer))){ // no hay espacio para escribir
		blockProcess(pipe->writingPid);
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
	if((getState(pipe->readingPid) == BLOCKED) && (length != 0)){ // hay algo para leer
		unlockProcess(pipe->readingPid);
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

	t_pipeADT pipeListNode;
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

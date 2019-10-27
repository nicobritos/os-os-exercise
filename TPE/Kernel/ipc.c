#include "ipc.h"

typedef struct t_pipeCDT {
	int readingPid;
	int writingPid;
	char buffer[_PIPE_BUFFER];
	char *readingPointer;
	char *writingPointer;

	t_pipeADT next;
	t_pipeADT previous;
} t_pipeCDT;

static t_pipeADT fistPipe = NULL;

void getPreviousPipeWithName(const char *name);

// PUBLIC
t_pipeADT openPipe(const char *name, uint8_t mode) {
	if (name == NULL) return _PIPE_INVALID_NAME;
	t_pipeADT existingPipe = getPreviousPipeWithName(name);
	t_pipeADT newPipe;

	if (existingPipe == NULL) {
		if (mode & _PIPE_CREATE) {
			newPipe = fistPipe = malloc(sizeof(t_pipeCDT));
			if (newPipe == NULL) return NULL; // TODO: Error
			
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
				existingPipe->readingPid = getpid();
			} else if (mode & _PIPE_WRITE) {
				existingPipe->writingPointer = existingPipe->buffer;
				existingPipe->writingPid = getpid();
			}

			return existingPipe;
		} else if (mode & _PIPE_CREATE) {
			newPipe = malloc(sizeof(t_pipeCDT));
			if (newPipe == NULL) return NULL; // TODO: Error

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
		newPipe->readingPid = getpid();
	} else if (mode & _PIPE_WRITE) {
		newPipe->writingPid = getpid();
	}

	return newPipe;
}

void closePipe(t_pipeADT pipe) {
	if (pipe == NULL) return;
	int pid = getpid();
	if (pid == pipe->readingPid) pipe->readingPid = -1;
	if (pid == pipe->writingPid) pipe->writingPid = -1;

	if (pipe->readingPid == -1 && pipe->writingPid == -1) {
		free(pipe);
	}
}

void read(t_pipeADT pipe, char *dst, uint64_t length);
void write(t_pipeADT pipe, char *src, uint64_t length);

// PRIVATE
void getPreviousPipeWithName(const char *name) {
	int16_t difference = -1;
	t_pipeADT auxPipe = fistPipe;
	if (auxPipe == NULL) return NULL;

	while (auxPipe->next != NULL && difference < 0) {
		difference = strcmp(auxPipe->name, name);
	}

	if (difference > 0) return auxPipe->previous;
	return auxPipe;
}

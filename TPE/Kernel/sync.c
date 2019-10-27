#include "process.h"
#include "string.h"
#include "sync.h"

typedef struct t_sem_listCDT *t_sem_listADT;
typedef struct t_sem_nodeCDT *t_sem_nodeADT;
typedef struct t_process_nodeCDT *t_process_nodeADT;
typedef struct t_process_list_nodeCDT *t_process_list_nodeADT;
typedef struct t_semaphore_list_nodeCDT *t_semaphore_list_nodeADT;

typedef struct t_semaphore_list_nodeCDT {
	t_process_list_nodeADT firstWaitingProcessNode;
	t_process_list_nodeADT currentWaitingProcessNode;
	int64_t value;
	char *name;
	uint8_t initialized;
	t_semaphore_list_nodeADT next;
} t_semaphore_list_nodeCDT;

typedef struct t_semaphore_listCDT {
	t_semaphore_list_nodeADT firstSemaphoreNode;
	t_semaphore_list_nodeADT currentSemaphoreNode;
	uint64_t length;
	uint8_t initialized;
} t_semaphore_listCDT;

typedef struct t_process_list_nodeCDT {
	int pid;
	t_process_list_nodeADT next;
} t_process_list_nodeCDT;

typedef struct t_process_nodeCDT {
	int pid;
	t_process_nodeADT next;
	t_process_nodeADT previous;
} t_process_nodeCDT;

typedef struct t_semCDT {
	t_process_nodeADT firstWaitingProcessNode;
	t_process_nodeADT lastWaitingProcessNode;
	int64_t value;
	char *name;
} t_semCDT;

typedef struct t_sem_nodeCDT {
	t_semADT semaphore;
	t_sem_nodeADT next;
	t_sem_nodeADT previous;
} t_sem_nodeCDT;

static t_sem_nodeADT firstSemaphoreNode = NULL;

void processQueue(t_semADT semaphore);
t_sem_nodeADT getPreviousSemaphoreNodeWithName(const char *name);
uint8_t removeProcessFromSemaphoreNode(int pid, t_sem_nodeADT semaphoreNode);
void freeWaitingProcessList(t_semaphore_list_nodeADT semaphoreListNode);
void createWaitingProcessList(t_semaphore_list_nodeADT semaphoreListNode, t_semADT semaphore);

// PUBLIC
t_semADT createSemaphore(const char *name, int64_t initialValue) {
	if (name == NULL) return NULL;
	t_sem_nodeADT existingSemaphoreNode = getPreviousSemaphoreNodeWithName(name);
	t_sem_nodeADT newSemaphoreNode;

	if (existingSemaphoreNode == NULL) {
		newSemaphoreNode = firstSemaphoreNode = malloc(sizeof(t_sem_nodeCDT));
		if (newSemaphoreNode == NULL) return NULL; // TODO: Error
		
		newSemaphoreNode->next = newSemaphoreNode->previous = NULL;
	} else {
		if (strcmp(existingSemaphoreNode->semaphore->name, name) == 0) return NULL; // TODO: Error
		newSemaphoreNode = malloc(sizeof(t_sem_nodeCDT));
		if (newSemaphoreNode == NULL) return NULL; // TODO: Error

		newSemaphoreNode->next = existingSemaphoreNode->next;
		newSemaphoreNode->previous = existingSemaphoreNode;
		if (existingSemaphoreNode->next != NULL) {
			existingSemaphoreNode->next->previous = newSemaphoreNode;
		}
	}

	newSemaphoreNode->semaphore = malloc(sizeof(t_semCDT));
	newSemaphoreNode->semaphore->name = name;
	newSemaphoreNode->semaphore->value = initialValue;

	return newSemaphoreNode->semaphore;
}

t_semADT openSemaphore(const char *name) {
	if (name == NULL) return NULL;
	t_sem_nodeADT semaphoreNode = getPreviousSemaphoreNodeWithName(name);
	if (semaphoreNode == NULL || strcmp(semaphoreNode->semaphore->name, name) != 0) return NULL; // TODO: Error
	return semaphoreNode->semaphore;
}

void closeSemaphore(t_semADT semaphore) {
	if (semaphore == NULL) return;
	removeProcessFromSemaphoreNode(getpid(), semaphore);
}

int8_t post(t_semADT semaphore) {
	if (semaphore == NULL) return _SEM_INVALID_SEMAPHORE;
	if (semaphore->value == INT64_MAX) return _SEM_SEMAPHORE_MAX_VALUE;

	semaphore->value++;
	processQueue(semaphore);

	return _SEM_NO_ERROR;
}

int8_t wait(t_semADT semaphore) {
	if (semaphore == NULL) return _SEM_INVALID_SEMAPHORE;
	if (semaphore->value == INT64_MIN) return _SEM_SEMAPHORE_MIN_VALUE;

	t_process_nodeADT processNode = malloc(sizeof(t_process_nodeCDT));
	if (malloc == NULL) return _SEM_MEMORY_ALLOC_ERROR;

	processNode->pid = getpid();
	processNode->next = NULL;
	processNode->previous = semaphore->lastWaitingProcessNode;
	if (processNode->previous != NULL) {
		semaphore->lastWaitingProcessNode->next = processNode;
	} else {
		semaphore->firstWaitingProcessNode = processNode;
	}
	semaphore->lastWaitingProcessNode = processNode;
	semaphore->value--;

	return _SEM_NO_ERROR;
}

// Iterator
t_semaphore_listADT createSemaphoreList() {
	t_semaphore_listADT semaphoreList = malloc(sizeof(t_semaphore_listCDT));
	semaphoreList->currentSemaphoreNode = NULL;
	t_semaphore_list_nodeADT semaphoreListNode = NULL;
	semaphoreList->initialized = 0;
	semaphoreList->length = 0;

	t_sem_nodeADT semaphoreNode = firstSemaphoreNode;
	while (semaphoreNode != NULL) {
		if (semaphoreListNode == NULL) {
			semaphoreListNode = semaphoreList->firstSemaphoreNode = malloc(sizeof(t_semaphore_list_nodeCDT));
		} else {
			semaphoreListNode = semaphoreListNode->next = malloc(sizeof(t_semaphore_list_nodeCDT));
		}

		createWaitingProcessList(semaphoreListNode, semaphoreNode->semaphore);
		semaphoreList->length++;
		semaphoreNode = semaphoreNode->next;
	}
	if (semaphoreListNode != NULL) {
		semaphoreListNode->next = NULL;
	}

	return semaphoreList;
}

uint8_t hasNextWaitingProcess(t_semaphore_list_nodeADT semaphoreListNode) {
	if (semaphoreListNode != NULL) {
		if (!semaphoreListNode->initialized) {
			return semaphoreListNode->firstWaitingProcessNode != NULL;
		} else {
			return semaphoreListNode->currentWaitingProcessNode->next != NULL;
		}
	}
	return 0;
}

uint8_t hasNextSemaphore(t_semaphore_listADT semaphoreList) {
	if (semaphoreList != NULL) {
		if (!semaphoreList->initialized) {
			return semaphoreList->firstSemaphoreNode != NULL;
		} else {
			return semaphoreList->currentSemaphoreNode->next != NULL;
		}
	}
	return 0;
}

uint64_t getWaitingProcessLength(t_semaphore_list_nodeADT semaphoreListNode) {
	if (semaphoreListNode != NULL && semaphoreListNode->value < 0) {
		return -semaphoreListNode->value;
	}
	return 0;
}

uint64_t getSemaphoreListLength(t_semaphore_listADT semaphoreList) {
	if (semaphoreList != NULL) return semaphoreList->length;
	return 0;
}

int getNextWaitingProcessPid(t_semaphore_list_nodeADT semaphoreListNode) {
	if (!hasNextWaitingProcess(semaphoreListNode)) return -1;

	if (!semaphoreListNode->initialized) {
		semaphoreListNode->initialized = 1;
		semaphoreListNode->currentWaitingProcessNode = semaphoreListNode->firstWaitingProcessNode;
		return semaphoreListNode->currentWaitingProcessNode->pid;
	}

	if (semaphoreListNode->currentWaitingProcessNode == NULL) {
		semaphoreListNode->currentWaitingProcessNode = semaphoreListNode->firstWaitingProcessNode;
	} else {
		semaphoreListNode->currentWaitingProcessNode = semaphoreListNode->currentWaitingProcessNode->next;
	}

	return semaphoreListNode->currentWaitingProcessNode->pid;
}

t_semaphore_list_nodeADT getNextSemaphore(t_semaphore_listADT semaphoreList) {
	if (!hasNextSemaphore(semaphoreList)) return NULL;

	if (!semaphoreList->initialized) {
		semaphoreList->initialized = 1;
		return semaphoreList->currentSemaphoreNode = semaphoreList->firstSemaphoreNode;
	}

	if (semaphoreList->currentSemaphoreNode == NULL) {
		semaphoreList->currentSemaphoreNode = semaphoreList->firstSemaphoreNode;
	} else {
		semaphoreList->currentSemaphoreNode = semaphoreList->currentSemaphoreNode->next;
	}

	return semaphoreList->currentSemaphoreNode;
}

void freeSemaphoreList(t_semaphore_listADT semaphoreList) {
	t_semaphore_list_nodeADT semaphoreListNode;
	t_semaphore_list_nodeADT auxSemaphoreList;

	if (semaphoreList != NULL) {
		semaphoreListNode = semaphoreList->firstSemaphoreNode;
		while (semaphoreListNode != NULL) {
			freeWaitingProcessList(semaphoreListNode);
			auxSemaphoreList = semaphoreListNode->next;
			free(semaphoreListNode);
			semaphoreListNode = auxSemaphoreList;
		}
		free(semaphoreList);
	}
}


// Should only visibile to Kernel?
void removeProcess(int pid) {
	t_sem_nodeADT currentSemaphoreNode = firstSemaphoreNode;

	while (currentSemaphoreNode != NULL && !removeProcessFromSemaphoreNode(pid, currentSemaphoreNode)) {
		currentSemaphoreNode = currentSemaphoreNode->next;
	}
}

// PRIVATE
void processQueue(t_semADT semaphore) {
	t_process_nodeADT auxProcessNode;
	t_process_nodeADT processNode = semaphore->firstWaitingProcessNode;

	while (semaphore->value > 0 && processNode != NULL) {
		// Scheduler
		unlockProcess(processNode->pid);
		auxProcessNode = processNode;
		processNode = processNode->next;
		free(auxProcessNode);
		semaphore->value--;
	}

	semaphore->firstWaitingProcessNode = processNode;
	if (processNode == NULL || processNode->next == NULL)
		semaphore->lastWaitingProcessNode = processNode;
	if (processNode != NULL)
		processNode->previous = NULL;
}

t_sem_nodeADT getPreviousSemaphoreNodeWithName(const char *name) {
	if (firstSemaphoreNode == NULL) return NULL;
	t_sem_nodeADT semaphoreNode = firstSemaphoreNode;

	int16_t difference = -1;
	while (semaphoreNode->next != NULL && difference < 0) {
		difference = strcmp(semaphoreNode->semaphore->name, name);
	}

	if (difference > 0) return semaphoreNode->previous;
	return semaphoreNode;
}

uint8_t removeProcessFromSemaphoreNode(int pid, t_sem_nodeADT semaphoreNode) {
	t_process_nodeADT currentWaitingProcessNode = semaphoreNode->semaphore->firstWaitingProcessNode;
	while (currentWaitingProcessNode != NULL) {
		if (currentWaitingProcessNode->pid == pid) {
			if (currentWaitingProcessNode->previous != NULL) {
				currentWaitingProcessNode->previous->next = currentWaitingProcessNode->next;
			} else {
				semaphoreNode->semaphore->firstWaitingProcessNode = semaphoreNode->next;
			}
			if (semaphoreNode->semaphore->lastWaitingProcessNode == currentWaitingProcessNode) {
				semaphoreNode->semaphore->lastWaitingProcessNode = currentWaitingProcessNode->previous;
			}
			free(currentWaitingProcessNode);

			if (semaphoreNode->semaphore->value < 0) semaphoreNode->semaphore->value++;
			return 1;
		}
	}
	return 0;
}

void createWaitingProcessList(t_semaphore_list_nodeADT semaphoreListNode, t_semADT semaphore) {
	semaphoreListNode->currentWaitingProcessNode = NULL;
	semaphoreListNode->value = semaphore->value;
	semaphoreListNode->initialized = 0;
	semaphoreListNode->name = malloc(sizeof(char) * (strlen(semaphore->name) + 1));
	strcpy(semaphoreListNode->name, semaphore->name);

	t_process_nodeADT processNode = semaphore->firstWaitingProcessNode;
	t_process_list_nodeADT processListNode = NULL;
	while (processNode != NULL) {
		if (processListNode == NULL) {
			processListNode = semaphoreListNode->firstWaitingProcessNode = malloc(sizeof(t_process_list_nodeCDT));
		} else {
			processListNode = processListNode->next = malloc(sizeof(t_process_list_nodeCDT));
		}

		processListNode->pid = processNode->pid;
		processNode = processNode->next;
	}
	if (processListNode != NULL) {
		processListNode->next = NULL;
	}
}

void freeWaitingProcessList(t_semaphore_list_nodeADT semaphoreListNode) {
	t_process_list_nodeADT processNode;
	t_process_list_nodeADT auxProcessNode;

	if (semaphoreListNode != NULL) {
		processNode = semaphoreListNode->firstWaitingProcessNode;
		while (processNode != NULL) {
			auxProcessNode = processNode->next;
			free(processNode);
			processNode = auxProcessNode;
		}
	}
}

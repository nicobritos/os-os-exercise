#include "process.h"
#include "string.h"
#include "sync.h"

typedef struct t_sem_listCDT *t_sem_listADT;
typedef struct t_sem_nodeCDT *t_sem_nodeADT;
typedef struct t_process_nodeCDT *t_process_nodeADT;

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

typedef struct t_sem_listCDT {
	t_sem_nodeADT firstSemaphoreNode;
	t_sem_nodeADT lastSemaphoreNode;
} t_sem_listCDT;

static t_sem_listADT semaphoreList = NULL;

void processQueue(t_semADT semaphore);
void getPreviousSemaphoreWithName(const char *name);
uint8_t removeProcessFromSemaphore(int pid, t_semADT semaphore);

// PUBLIC
int8_t initializeSemaphore() {
	semaphoreList = malloc(sizeof(t_sem_listCDT));
	if (semaphoreList == NULL) return _SEM_MEMORY_ALLOC_ERROR;
}

t_semADT createSemaphore(const char *name, int64_t initialValue) {
	if (name == NULL) return _SEM_INVALID_NAME;
	t_semADT existingSemaphore = getPreviousSemaphoreWithName(name);
	t_semADT newSemaphore;

	if (existingSemaphore == NULL) {
		newSemaphore = semaphoreList->firstSemaphoreNode = semaphoreList->lastSemaphoreNode = malloc(sizeof(t_sem_nodeCDT));
		if (newSemaphore == NULL) return NULL; // TODO: Error
		
		newSemaphore->next = newSemaphore->previous = NULL;
	} else {
		if (strcmp(existingSemaphore->semaphore->name, name) == 0) return NULL; // TODO: Error
		newSemaphore = malloc(sizeof(t_sem_nodeCDT));
		if (newSemaphore == NULL) return NULL; // TODO: Error

		newSemaphore->next = existingSemaphore->next;
		newSemaphore->previous = existingSemaphore;
		if (existingSemaphore->next == NULL) {
			semaphoreList->lastSemaphoreNode = newSemaphore;
		} else {
			existingSemaphore->next->previous = newSemaphore;
		}
	}

	newSemaphore->name = name;
	newSemaphore->value = initialValue;

	return newSemaphore;
}

t_semADT openSemaphore(const char *name) {
	if (name == NULL) return _SEM_INVALID_NAME;
	t_semADT semaphore = getPreviousSemaphoreWithName(name);
	if (semaphore == NULL || strcmp(semaphore->semaphore->name, name) != 0) return NULL; // TODO: Error
	return semaphore;
}

void closeSemaphore(t_semADT semaphore) {
	if (semaphore == NULL) return _SEM_INVALID_SEMAPHORE;
	removeProcessFromSemaphore(getpid(), semaphore);
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

// Should only visibile to Kernel?
void removeProcess(int pid) {
	t_sem_nodeADT currentSemaphoreNode = semaphoreList->firstSemaphoreNode;

	while (currentSemaphoreNode != NULL && !removeProcessFromSemaphore(pid, currentSemaphoreNode)) {
		currentSemaphoreNode = currentSemaphoreNode->next;
	}
}

uint8_t removeProcessFromSemaphore(int pid, t_semADT semaphore) {
	t_process_nodeADT currentWaitingProcessNode = currentSemaphoreNode->semaphore->firstWaitingProcessNode;
	while (currentWaitingProcessNode != NULL) {
		if (currentWaitingProcessNode->pid == pid) {
			if (currentWaitingProcessNode->previous != NULL) {
				currentWaitingProcessNode->previous->next = currentWaitingProcessNode->next;
			} else {
				semaphore->firstWaitingProcessNode = currentSemaphoreNode->next;
			}
			if (semaphore->lastSemaphoreNode == currentSemaphoreNode) {
				semaphore->lastSemaphoreNode = currentSemaphoreNode->previous;
			}
			free(currentWaitingProcessNode);

			if (semaphore->value < 0) semaphore->value++;
			return 1;
		}
	}
	return 0;
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

void getPreviousSemaphoreWithName(const char *name) {
	if (semaphoreList->firstSemaphoreNode == NULL) return NULL;
	t_sem_nodeADT semaphoreNode = semaphoreList->firstSemaphoreNode;

	int16_t difference = -1;
	while (semaphoreNode->next != NULL && difference < 0) {
		difference = strcmp(semaphoreNode->semaphore->name, name);
	}

	if (difference > 0) return semaphoreNode->previous;
	return semaphoreNode;
}


#include "scheduler.h"
#include "process.h"
#include "time.h"

#define QUANTUM 4

typedef struct processListNodeCDT {
	t_process *process;
	processListNodeADT next;
} processListNodeCDT;

typedef struct processListCDT {
	processListNodeADT firstProcessNode;
	processListNodeADT currentProcessNode;
	uint64_t length;
	uint8_t initialized;
} processListCDT;

typedef struct queueNodeCDT *queueNodeADT;
typedef struct queueCDT *queueADT;

typedef struct queueNodeCDT {
	t_priority priority;
    t_process *process;
    uint64_t executedOnTicks;
    queueNodeADT previous;
    queueNodeADT next;
} queueNodeCDT;

typedef struct queueCDT {
	queueNodeADT firstProcessNode;
	queueNodeADT lastProcessNode;
	uint64_t count;
} queueCDT;

static const uint64_t quantumSlice[2] = {QUANTUM * 2, QUANTUM};

static queueNodeADT currentProcessNode = NULL;
static queueADT waitingQueue = NULL;
static queueADT readyQueue = NULL;

static uint8_t initialized = 0;

static t_process *idleProcess = NULL;

void loadNextProcess(t_stack *currentProcessStack);
queueNodeADT fetchNextNode();
void dispatchProcess(t_process *process, t_stack *currentProcessStack);
void updateProcessState(t_stack *dst, t_stack *src);
queueNodeADT getNode(int pid, queueADT queue);
queueNodeADT getNodeReadyQueue(int pid);
queueNodeADT getNodeWaitingQueue(int pid);
void removeProcess(queueNodeADT processNode, queueADT queue);
void moveNode(queueNodeADT processNode, queueADT fromQueue, queueADT toQueue);

// Public
void initScheduler(t_process *_idleProcess) {
	idleProcess = _idleProcess;

	waitingQueue = malloc(sizeof(queueCDT));
	waitingQueue->firstProcessNode = waitingQueue->lastProcessNode = NULL;

	readyQueue = malloc(sizeof(queueCDT));
	readyQueue->firstProcessNode = readyQueue->lastProcessNode = NULL;

	initialized = 1;
}

void runScheduler(t_stack *currentProcessStack) {
	if (!initialized) {
		return;
	}

	if (currentProcessNode == NULL) {
		if (readyQueue->count >= 1) {
			loadNextProcess(currentProcessStack);
		} else {
			dispatchProcess(idleProcess, currentProcessStack);
		}

		return;
	}
	if (currentProcessNode->process->state == RUNNING && ticks_elapsed() - currentProcessNode->executedOnTicks < quantumSlice[currentProcessNode->priority]) return;

	loadNextProcess(currentProcessStack);
}

uint8_t addProcess(t_process *process, t_priority priority) {
	queueNodeADT processNode = malloc(sizeof(queueNodeCDT));
	if (processNode == NULL) {
		// TODO: Error
		return 0;
	}
	processNode->priority = priority;
	processNode->process = process;
	processNode->executedOnTicks = 0;
	processNode->next = NULL;

	if (readyQueue->firstProcessNode == NULL) {
		readyQueue->firstProcessNode = readyQueue->lastProcessNode = processNode;
		processNode->previous = NULL;
	} else {
		processNode->previous = readyQueue->lastProcessNode;
		readyQueue->lastProcessNode = readyQueue->lastProcessNode->next = processNode;
	}

	readyQueue->count++;	
	return 1;
}

void killProcess(int pid) {
	queueNodeADT processNode = getNodeReadyQueue(pid);
	if (processNode == NULL) {
		processNode = getNodeWaitingQueue(pid);
		if (processNode == NULL) return;

		removeProcess(processNode, waitingQueue);
		return;
	}

	if (processNode == currentProcessNode) {
		processNode->process->state = KILLED;
	} else {
		removeProcess(processNode, readyQueue);
	}
}

t_process *getCurrentProcess() {
	if (currentProcessNode != NULL) return currentProcessNode->process;
	return idleProcess;
}

int getpid() {
	if (currentProcessNode != NULL) return currentProcessNode->process->pid;
	return 0;
}

void lockProcess(int pid) {
	// TODO: Race condition
	queueNodeADT processNode = getNodeReadyQueue(pid);
	if (processNode == NULL) return;
	processNode->process->state = LOCKED;
	
	if (processNode != currentProcessNode) {
		moveNode(processNode, readyQueue, waitingQueue);
	}
}

void unlockProcess(int pid) {
	queueNodeADT processNode = getNodeWaitingQueue(pid);
	if (processNode == NULL) return;
	processNode->process->state = READY;
	
	moveNode(processNode, waitingQueue, readyQueue);
}

processListADT createProcessList() {
	processListADT processList = malloc(sizeof(processListCDT));
	processList->currentProcessNode = NULL;
	processListNodeADT processListNode = NULL;
	processList->initialized = 0;
	processList->length = 0;

	queueNodeADT processNode = readyQueue->firstProcessNode;
	while (processNode != NULL) {
		if (processListNode == NULL) {
			processListNode = processList->firstProcessNode = malloc(sizeof(processListNodeCDT));
		} else {
			processListNode = processListNode->next = malloc(sizeof(processListNodeCDT));
		}

		processListNode->process = malloc(sizeof(t_process));
		memcpy(processListNode->process, processNode->process, sizeof(t_process));
		processList->length++;

		processNode = processNode->next;
	}
	if (processListNode != NULL) {
		processListNode->next = NULL;
	}

	return processList;
}

uint8_t hasNextProcess(processListADT processList) {
	if (processList != NULL) {
		if (!processList->initialized) {
			return processList->firstProcessNode != NULL;
		} else {
			return processList->currentProcessNode->next != NULL;
		}
	}
	return 0;
}

uint64_t getProcessListLength(processListADT processList) {
	if (processList != NULL) return processList-> length;
	return 0;
}


t_process *getNextProcess(processListADT processList) {
	if (!hasNextProcess(processList)) return NULL;

	if (!processList->initialized) {
		processList->initialized = 1;
		return processList->currentProcessNode = processList->firstProcessNode;
	}

	if (processList->currentProcessNode == NULL) {
		processList->currentProcessNode = processList->firstProcessNode;
	} else {
		processList->currentProcessNode = processList->currentProcessNode->next;
	}

	return processList->currentProcessNode->process;
}

void freeProcessesList(processListADT processList) {
	processListNodeADT processListNode = NULL;
	processListNodeADT auxProcessListNode;

	if (processList != NULL) {
		processListNode = processList->firstProcessNode;
		while (processListNode != NULL) {
			auxProcessListNode = processListNode->next;
			free(processListNode->process);
			free(processListNode);
			processListNode = auxProcessListNode;
		}
		free(processList);
		processList = NULL;
	}
}

// Private
void loadNextProcess(t_stack *currentProcessStack) {
	queueNodeADT nextProcessNode = fetchNextNode();
	if (nextProcessNode == NULL) {
		dispatchProcess(idleProcess, currentProcessStack);
		return;
	}

	if (nextProcessNode == currentProcessNode) {
		currentProcessNode->executedOnTicks = ticks_elapsed();
	} else {
		if (currentProcessNode != NULL) {
			currentProcessNode->process->state = READY;
			updateProcessState(currentProcessNode->process->stack, currentProcessStack);
		}

		currentProcessNode = nextProcessNode;
		currentProcessNode->executedOnTicks = ticks_elapsed();
		dispatchProcess(currentProcessNode->process, currentProcessStack);
	}
}

queueNodeADT fetchNextNode() {
	queueNodeADT currentNode = currentProcessNode;
	if (currentNode == NULL) { // Solo pasa esto cuando no hay ningun proceso corriendo
		currentNode = readyQueue->firstProcessNode;
	} else {
		currentNode = currentProcessNode->next;
	}

	while (currentNode != currentProcessNode && readyQueue->count >= 1) {
		if (currentNode == NULL) {
			currentNode = readyQueue->firstProcessNode;
		} else {
			if (currentNode->process->state == KILLED) {
				removeProcess(currentNode, readyQueue);
			} else if (currentNode->process->state == READY) {
				break;
			} else if (currentNode->process->state == LOCKED) {
				moveNode(currentNode, readyQueue, waitingQueue);
			}

			currentNode = currentProcessNode->next;
		}
	}
	if (readyQueue->count == 0 || currentNode == NULL || currentNode->process->state != READY) {
		return NULL;
	}
	return currentNode;
}

void dispatchProcess(t_process *process, t_stack *currentProcessStack) {
	process->state = RUNNING;
	updateProcessState(currentProcessStack, process->stack);
}

void updateProcessState(t_stack *dst, t_stack *src) {
	// TODO: Change to order in struct t_stack
	dst->r15 = src->r15;
	dst->r14 = src->r14;
	dst->r13 = src->r13;
	dst->r12 = src->r12;
	dst->r11 = src->r11;
	dst->r10 = src->r10;
	dst->r9 = src->r9;
	dst->r8 = src->r8;
	
	dst->rsi = src->rsi;
	dst->rdi = src->rdi;
	dst->rbp = src->rbp;
	
	dst->rdx = src->rdx;
	dst->rcx = src->rcx;
	dst->rbx = src->rbx;
	dst->rax = src->rax;
	
	dst->rip = src->rip;
	dst->rflags = src->rflags;
	dst->rsp = src->rsp;
}

queueNodeADT getNode(int pid, queueADT queue) {
	queueNodeADT processNode = queue->firstProcessNode;

	while (processNode == NULL || processNode->process->pid != pid) {
		processNode = processNode->next;
	}
	return processNode;
}

queueNodeADT getNodeReadyQueue(int pid) {
	return getNode(pid, readyQueue);
}

queueNodeADT getNodeWaitingQueue(int pid) {
	return getNode(pid, waitingQueue);
}

void removeProcess(queueNodeADT processNode, queueADT queue) {
	if (processNode->previous != NULL) {
		processNode->previous->next = processNode->next;
	} else {
		queue->firstProcessNode = processNode->next;
	}
	if (queue->lastProcessNode == processNode) {
		queue->lastProcessNode = NULL;
	}

	free(processNode);
	queue->count--;
}

void moveNode(queueNodeADT processNode, queueADT fromQueue, queueADT toQueue) {
	if (processNode->previous != NULL) {
		processNode->previous->next = processNode->next;
	} else {
		fromQueue->firstProcessNode = processNode->next;
	}
	if (processNode->next == NULL) {
		fromQueue->lastProcessNode = processNode->previous;
	}

	if (toQueue->firstProcessNode == NULL) {
		toQueue->firstProcessNode = processNode;
		toQueue->lastProcessNode = processNode;
		processNode->next = processNode->previous = NULL;
	} else {
		toQueue->lastProcessNode->next = processNode;
		processNode->previous = toQueue->lastProcessNode;
		toQueue->lastProcessNode = processNode;
	}

	processNode->next = NULL;
}

#include <scheduler.h>
#include <dispatcher.h>

#define QUANTUM 1

typedef struct queueNodeADT *queueNode;
typedef struct queueADT *queue;

typedef struct queueNode {
    t_process *process;
    uint64_t timeSpent;
    queueNodeADT previous;
    queueNodeADT next;
} queueNode;

typedef struct queue {
	t_priority originalPriority;
	t_priority adjustedPriority;
	queueNodeADT firstProcessNode;
	queueNodeADT lastProcessNode;
} queue;

static queueNodeADT currentProcessNode = NULL;
static t_priority currentPriorityQueue = NULL;
static queueADT highPriorityQueue = NULL;
static queueADT lowPriorityQueue = NULL;
static uint64_t processQuantity = 0;

void loadNextProcess();

// Public
void runScheduler() {
	// Si el que corre es el proceso idle (pid 0) entonces tengo que alojar un proceso si es que hay alguno en Ready.
	// Como manejar el tema de prioridades?
	// Hashtable es una. Lo que no se es cuando "resetear" la prioridad de un proceso
	//

	if (currentProcessNode == NULL) {
		if (processQuantity >= 1) {
			loadNextProcess();
		} else {
			// loadIdle();
		}

		return;
	}
	currentProcessNode->timeSpent += getTicks(); // TODO
	if (currentProcessNode->timeSpent < QUANTUM) return;

	loadNextProcess();
}

void addProcess(t_process *process, t_priority priority) {
	queueNodeADT processNode;

	switch (priority) {
		case HIGH:
			if (highPriorityQueue == NULL) {
				highPriorityQueue = malloc(sizeof(queue));
				if (highPriorityQueue == NULL) {
					// TODO: Error
					return;
				}
				processNode = highPriorityQueue->firstProcessNode = highPriorityQueue->lastProcessNode = malloc(sizeof(queueNode));
				if (procesNode == NULL) {
					// TODO: Error
					free(highPriorityQueue);
					highPriorityQueue = NULL;
					return;
				}

				processNode->previous = processNode->next = NULL;
				highPriorityQueue->originalPriority = highPriorityQueue->adjustedPriority = HIGH;

				if (currentPriorityQueue == NULL) {
					currentPriorityQueue = highPriorityQueue;
				}
			} else {
				processNode = highPriorityQueue->lastProcessNode->next = malloc(sizeof(queueNode));
				if (processNode == NULL) {
					// TODO: Error
					return;
				}
				processNode->previous = highPriorityQueue->lastProcessNode;
				highPriorityQueue->lastProcessNode = processNode;
			}
			break;
		case LOW:
			if (lowPriorityQueue == NULL) {
				lowPriorityQueue = malloc(sizeof(queue));
				if (lowPriorityQueue == NULL) {
					// TODO: Error
					return;
				}
				processNode = lowPriorityQueue->firstProcessNode = lowPriorityQueue->lastProcessNode = malloc(sizeof(queueNode));
				if (procesNode == NULL) {
					// TODO: Error
					free(lowPriorityQueue);
					lowPriorityQueue = NULL;
					return;
				}

				processNode->previous = processNode->next = NULL;
				lowPriorityQueue->originalPriority = lowPriorityQueue->adjustedPriority = HIGH;

				if (currentPriorityQueue == NULL) {
					currentPriorityQueue = lowPriorityQueue;
				}
			} else {
				processNode = lowPriorityQueue->lastProcessNode->next = malloc(sizeof(queueNode));
				if (processNode == NULL) {
					// TODO: Error
					return;
				}
				processNode->previous = lowPriorityQueue->lastProcessNode;
				lowPriorityQueue->lastProcessNode = processNode;
			}
			break;
	}

	procesNode->timeSpent = 0;
	processNode->process = process;
	processNode->next = NULL;
	processQuantity++;	
}

void killProcess(int pid) {
	queueNodeADT processNode = NULL;
	queueNodeADT currentNode;
	queueADT queue = highPriorityQueue;

	while (queue != NULL) {
		if (queue != NULL) {
			currentNode = queue->firstProcessNode;

			if (currentNode->process->pid == pid) {
				processNode = currentNode;
				break;
			} else {
				while (currentNode != NULL && currentNode->process->pid != pid) {
					currentNode = currentNode->next;
				}
				if (currentNode != NULL) {
					processNode = currentNode;
					break;
				}
			}
		}

		if (queue == lowPriorityQueue) {
			queue = NULL;
		} else {
			queue = lowPriorityQueue;
		}
	}
	if (processNode == NULL) {
		return;
	}

	if (processNode->previous != NULL) {
		processNode->previous->next = processNode->next;
	}

	if (processNode == currentProcessNode) {
		currentProcessNode = processNode->next;
	}
	free(processNode);
}

t_process *getCurrentProcess() {
	return currentProcess != NULL ? currentProcess->process : NULL;
}


// Private
// TODO: Only load READY processes
void loadNextProcess() {
	if (currentProcessNode == NULL) {
		currentProcessNode = queue.firstProcessNode;
	}
	
	// if (currentProcessNode->process->state != READY || currentProcessNode->next == NULL) {
	if (currentProcessNode->next == NULL) {
		if (currentPriorityQueue->adjustedPriority == LOW) {
			currentPriorityQueue->adjustedPriority = currentPriorityQueue->originalPriority;
			switch (currentPriorityQueue->adjustedPriority) {
				case HIGH:
					if (highPriorityQueue != NULL) {
						currentPriorityQueue = highPriorityQueue;
						break;
					}
				case LOW:
					if (lowPriorityQueue != NULL) {
						currentPriorityQueue = lowPriorityQueue;
						break;
					}
			}
		} else {
			currentPriorityQueue->adjustedPriority--;
		}
		currentProcessNode = currentPriorityQueue->firstProcessNode;
	} else {
		currentProcessNode = currentProcessNode->next;
	}

	currentProcessNode->process->state = RUNNING;
	// dispatchProcess(currentProcessNode->process) TODO: Dispatch currentProcess
}

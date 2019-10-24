#include <scheduler.h>
#include <dispatcher.h>

#define QUANTUM 1

typedef struct queueNodeADT *queueNode;
typedef struct queueADT *queue;

typedef struct queueNode {
    t_process process;
    uint64_t timeSpent;
    uint8_t quantumsRun;
    queueNodeADT previous;
    queueNodeADT next;
} queueNode;

typedef struct queue {
	t_priority adjustedPriority;
	queueNodeADT firstProcessNode;
	queueNodeADT currentProcessNode;
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
		}

		return;
	}
	currentProcessNode->timeSpent += getTicks(); // TODO
	if (currentProcessNode->timeSpent < QUANTUM) return;

	loadNextProcess();
}

void killProcess(int pid) {
	
}

// Private
void loadNextProcess() {
	if (currentPriorityQueue == NULL) {
		if (highPriorityQueue != NULL) {
			currentPriorityQueue = highPriorityQueue;
		} else if (lowPriorityQueue != NULL) {
			currentPriorityQueue = lowPriorityQueue;
		} else {
			return;
		}
	}

	queueNode processNodeToLoad = NULL;
	if (currentPriorityQueue->currentProcessNode->next == NULL) {
		currentPriorityQueue->currentProcessNode = currentPriorityQueue->firstProcessNode;
		if (currentPriorityQueue->adjustedPriority == LOW) {
			currentPriorityQueue->adjustedPriority = HIGH;

			if (lowPriorityQueue != NULL) {
				currentPriorityQueue = lowPriorityQueue;
				processNodeToLoad = currentPriorityQueue->firstProcessNode;
			}
		} else if (lowPriorityQueue != NULL) {
			currentPriorityQueue->adjustedPriority = LOW;
		}
	} else {
		processNodeToLoad = currentPriorityQueue->firstProcessNode;
	}

	if (processNodeToLoad != NULL) {
		currentPriorityQueue->currentProcessNode = processNodeToLoad;
		// TODO: dispatch node
	} else {
		// IDLE PROCESS
	}
}


// Scheduler
// •	Init
// •	Run process
// •	Kill process
// •	Run scheduler
// •	set process state
// •	Get current processes
// •	Get current process
// •	Threads?
// Funcionamiento:
// 1.	Timer tick llama a scheduler (RR). Si ticks >= Quantum entonces desalojamos (backup con dispatcher) y agarramos otro proceso READY. Si están todos bloqueados ni idea. Lo marcamos como RUNNING y llamamos al dispatcher para que lo aloje
// 2.	Run process lo manda a la lista. Si vacia, dispatcher
// 3.	Kill process lo saca de la lista. Si estaba corriendo, dispatcher y se ejecuta siguiente (si es que hay).
// 4.	Set process state: cambia el estado del proceso. Si corria => dispatcher

void addProcess(t_process process, t_priority priority);
void killProcess(t_process process);
void blockProcess(t_process process);
void unblockProcess(t_process process);
void getProcesses();
void getCurrentProcess();




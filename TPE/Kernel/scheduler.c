//This is a personal academic project. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "processHandler.h"
#include "videoDriver.h"
#include "memManager.h"
#include "scheduler.h"
#include "semaphore.h"
#include "stdio.h"
#include "mutex.h"
#include "time.h"

#define QUANTUM 2

typedef struct processNodeCDT *processNodeADT;

typedef struct processNodeCDT {
    uint64_t activateOnTicks;
    uint64_t executedOnTicks;
    t_mutexADT waitpidMutex;
	t_priority priority;
	t_process process;
    t_mode mode;
} processNodeCDT;

static const uint64_t quantumSlice[2] = {QUANTUM * 2, QUANTUM};

static nodeListADT currentProcessNode = NULL;
static listADT waitingQueue = NULL;
static listADT readyQueue = NULL;
static listADT foregroundStack = NULL;
static uint8_t initialized = 0;
static uint64_t backgroundProcesses = 0;

static t_process idleProcess = NULL;
static void (*onProcessKill) (t_process process) = NULL;
static uint64_t nextProcessActivateOnTicks = 0;

void idleFunction();


void runSchedulerForce(t_stack currentProcessStack, uint8_t force);

void loadNextProcess(t_stack currentProcessStack);

nodeListADT fetchNextNode();

void dispatchProcess(t_process process, t_stack currentProcessStack);

nodeListADT getNodePid(pid_t pid);

nodeListADT getNode(pid_t pid, listADT queue);

nodeListADT getNodeReadyQueue(pid_t pid);

nodeListADT getNodeWaitingQueue(pid_t pid);

t_priority getProcessNodePriority(nodeListADT node);

void setProcessNodePriority(nodeListADT node, t_priority priority);

void setProcessNodeMode(nodeListADT node, t_mode mode, t_stack currentProcessStack);

void removeProcess(nodeListADT processNode, listADT queue, t_stack stackFrame);

void moveNode(nodeListADT processNode, listADT fromQueue, listADT toQueue);

processNodeADT getProcessNodeFromNode(nodeListADT node);

t_process getProcessFromNode(nodeListADT node);

void *duplicateProcessNode(void *_processNode);

void freeProcessNodeReadOnly(void *_processNode);

int equalsPid(void *_process, void *_pid);

void freeProcessNodeReadOnly(void *_processNode);

t_mode getProcessNodeMode(nodeListADT node);

void printQueue(listADT queue, char *title);

void printProcessNode(void *_processNode);

void printProcessHeaderScheduler();

char *getProcessPriorityString(t_priority priority);

char *getProcessModeString(t_mode mode);

void wakeProcesses();

void addNodeToForegroundStack(processNodeADT processNode, t_stack currentProcessStack);

void removeNodeFromForegroundStack(processNodeADT processNode, t_stack currentProcessStack);

// Public
void initializeScheduler() {
	idleProcess = createProcess("Idle Process", processWrapper, SYSTEM_PID, SYSTEM_PID, 0, NULL, (int (*)(int, char**))idleFunction);

	foregroundStack = createList();
	waitingQueue = createList();
	readyQueue = createList();

	initialized = 1;
}

void runScheduler(t_stack currentProcessStack) {
	runSchedulerForce(currentProcessStack, 0);
}

uint8_t addProcess(t_process process, t_priority priority, t_mode mode, t_stack currentProcessStack) {
	if (priority == S_P_INVALID || mode == S_M_INVALID || process == NULL || (getProcessState(process) != P_READY && getProcessState(process) != P_LOCKED)) return 0;

	processNodeADT processNode = pmalloc(sizeof(processNodeCDT), SYSTEM_PID);
	if (getProcessState(process) == P_READY)
		addElementToIndexList(readyQueue, processNode, getSizeList(readyQueue));
	else
		addElementToIndexList(waitingQueue, processNode, getSizeList(waitingQueue));

	processNode->executedOnTicks = 0;
	processNode->process = process;
	processNode->priority = priority;
	processNode->mode = mode;
	processNode->waitpidMutex = createMutex();

	if (mode == S_M_FOREGROUND) {
		addNodeToForegroundStack(processNode, currentProcessStack);
	} else {
		backgroundProcesses++;
	}

	return 1;
}

void addNodeToForegroundStack(processNodeADT processNode, t_stack currentProcessStack) {
	processNodeADT currentForegroundProcessNode = (processNodeADT) getElementList(getNodeAtIndexList(foregroundStack, 0));
	addElementToIndexList(foregroundStack, processNode, 0);

	if (currentForegroundProcessNode != NULL) {
		lockProcess(getProcessPid(currentForegroundProcessNode->process), currentProcessStack, L_FOREGROUND);
	}
}

void removeNodeFromForegroundStack(processNodeADT processNode, t_stack currentProcessStack) {
	if (getSizeList(foregroundStack) == 0 || processNode == NULL) return;
	nodeListADT nodeList = getNode(getProcessPid(processNode->process), foregroundStack);
	if (nodeList == NULL) return;
	removeNodeList(foregroundStack, nodeList);
	processNodeADT currentForegroundProcessNode = (processNodeADT) getElementList(getNodeAtIndexList(foregroundStack, 0));

	if (currentForegroundProcessNode != NULL && getProcessState(currentForegroundProcessNode->process) == P_LOCKED && getProcessLockReason(currentForegroundProcessNode->process) == L_FOREGROUND) {
		unlockProcess(getProcessPid(currentForegroundProcessNode->process), L_FOREGROUND);
	}
}

int8_t killProcess(pid_t pid, t_stack stackFrame) {
	nodeListADT processNode = getNodeReadyQueue(pid);
	if (processNode == NULL) {
		processNode = getNodeWaitingQueue(pid);
		if (processNode == NULL) return 0;

		removeProcess(processNode, waitingQueue, stackFrame);
		return 1;
	}

	if (processNode == currentProcessNode) {
		setProcessState(getProcessFromNode(processNode), P_DEAD, L_INVALID);
		currentProcessNode = fetchNextNode();
		if (currentProcessNode != NULL) {
			dispatchProcess(getProcessFromNode(currentProcessNode), stackFrame);
		} else {
			dispatchProcess(idleProcess, stackFrame);
		}
	}

	removeProcess(processNode, readyQueue, stackFrame);
	return 1;
}

t_process getCurrentProcess() {
	if (currentProcessNode != NULL) return getProcessFromNode(currentProcessNode);
	return idleProcess;
}

t_priority getCurrentProcessPriority() {
	return getProcessNodePriority(currentProcessNode);
}

t_priority getProcessPriority(pid_t pid) {
	return getProcessNodePriority(getNodePid(pid));
}

void lockProcess(pid_t pid, t_stack stackFrame, t_lock_reason lockReason) {
	nodeListADT processNode = getNodeReadyQueue(pid);
	if (processNode == NULL) return;
	
	setProcessState(getProcessFromNode(processNode), P_LOCKED, lockReason);
	moveNode(processNode, readyQueue, waitingQueue);

	if (processNode == currentProcessNode) {
		updateProcessStack(getProcessStackFrame(getProcessFromNode(currentProcessNode)), stackFrame);
		currentProcessNode = fetchNextNode();
	}
	if (currentProcessNode != NULL)
		dispatchProcess(getProcessFromNode(currentProcessNode), stackFrame);
	else
		dispatchProcess(idleProcess, stackFrame);
}

void unlockProcess(pid_t pid, t_lock_reason lockReason) {
	nodeListADT processNode = getNodeWaitingQueue(pid);
	if (processNode == NULL) return;

	t_process process = getProcessFromNode(processNode);
	if (getProcessLockReason(process) != L_TIME && getProcessLockReason(process) != lockReason) return;
	// if (getProcessNodeMode(processNode) == S_M_FOREGROUND && ((t_process) getElementList(getNodeAtIndexList(foregroundStack, 0))) != process) return;

	setProcessState(process, P_READY, L_INVALID);
	
	moveNode(processNode, waitingQueue, readyQueue);
}

t_state toggleProcessLock(pid_t pid, t_stack stackFrame) {
	t_state state = getProcessStatePid(pid);
	if (state == P_LOCKED) {
		unlockProcess(pid, L_ARBITRARY);
		state = P_READY;
	} else if (state != P_DEAD && state != P_INVALID) {
		lockProcess(pid, stackFrame, L_ARBITRARY);
		state = P_LOCKED;
	}
	return state;
}

void setCurrentProcessPriority(t_priority priority) {
	setProcessNodePriority(currentProcessNode, priority);
}

void setProcessPriority(pid_t pid, t_priority priority) {
	setProcessNodePriority(getNodePid(pid), priority);
}

void setProcessNodePriority(nodeListADT node, t_priority priority) {
	if (node == NULL) return;
	getProcessNodeFromNode(node)->priority = priority;
}

t_state getCurrentProcessState() {
	if (currentProcessNode == NULL) return P_INVALID;
	return getProcessState(getProcessFromNode(currentProcessNode));
}

void setCurrentProcessMode(t_mode mode, t_stack currentProcessStack) {
	setProcessNodeMode(currentProcessNode, mode, currentProcessStack);
}

void setProcessMode(pid_t pid, t_mode mode, t_stack currentProcessStack) {
	setProcessNodeMode(getNodePid(pid), mode, currentProcessStack);
}

void setProcessNodeMode(nodeListADT node, t_mode mode, t_stack currentProcessStack) {
	if (node == NULL || mode == S_M_INVALID) return;
	processNodeADT processNode = getProcessNodeFromNode(node);
	if (processNode->mode == mode) return;
	processNode->mode = mode;

	if (mode == S_M_FOREGROUND) {
		addNodeToForegroundStack(processNode, currentProcessStack);
		backgroundProcesses--;
	} else {
		removeNodeFromForegroundStack(processNode, currentProcessStack);
		backgroundProcesses++;
	}
}

t_mode getCurrentProcessMode() {
	return getProcessNodeMode(currentProcessNode);
}

t_mode getProcessMode(pid_t pid) {
	return getProcessNodeMode(getNodePid(pid));
}

void setOnProcessKillScheduler(void(_onProcessKill) (t_process process)) {
	onProcessKill = _onProcessKill;
}

void yieldScheduler(t_stack stackFrame) {
	runSchedulerForce(stackFrame, 1);
}

// Lock process until pid is killed
void waitpid(pid_t pid, t_stack currentProcessStack) {
	processNodeADT observedProcessNode = getProcessNodeFromNode(getNodePid(pid));
	if (observedProcessNode != NULL) {
		processNodeADT processNode = getProcessNodeFromNode(currentProcessNode);
		waitMutex(observedProcessNode->waitpidMutex, processNode->process, currentProcessStack);
	}
}

void printProcessesScheduler() {
	uint64_t total = getSizeList(readyQueue) + getSizeList(waitingQueue);
	newLine();
	printString("Processes: (", 0, 255, 0);
	printDec(total, 0, 255, 0);
	printString("/", 0, 255, 0);
	printDec(MAX_PROC, 0, 255, 0);
	printString(")", 0, 255, 0);
	newLine();
	printQueue(readyQueue, "Ready queue: ");
	newLine();
	printQueue(waitingQueue, "Waiting queue: ");
	newLine();
}

void sleepScheduler(uint64_t ms, t_stack currentProcessStack) {
	processNodeADT processNode = getProcessNodeFromNode(currentProcessNode);
	processNode->activateOnTicks = msToTicks(ms);
	if (processNode->activateOnTicks == 0) {
		if (ms > 0)
			processNode->activateOnTicks = 1;
		else
			return;
	}
	
	processNode->activateOnTicks = processNode->activateOnTicks + ticks_elapsed();
	if (nextProcessActivateOnTicks > processNode->activateOnTicks || nextProcessActivateOnTicks == 0) {
		nextProcessActivateOnTicks = processNode->activateOnTicks;
	}
	
	lockProcess(getProcessPid(processNode->process), currentProcessStack, L_TIME);
}

// Iterator
// listADT createProcessList() {
// 	listADT newList = duplicateList(readyQueue, duplicateProcessNode);
// 	return duplicateAndConcatList(newList, waitingQueue, duplicateProcessNode);
// }

// uint8_t hasNextProcess(listADT list) {
// 	return hasNextListIterator(list);
// }

// uint64_t getProcessListLength(listADT list) {
// 	return getSizeList(list);
// }

// t_process getNextProcess(listADT list) {
// 	if (!hasNextProcess(list)) return NULL;
// 	nodeListADT processNode = getNextNodeListIterator(list);
// 	if (processNode != NULL) {
// 		return getProcessFromNode(processNode);
// 	}
// 	return NULL;
// }

// void freeProcessesList(listADT list) {
// 	freeList(list, freeProcessNodeReadOnly);
// }

// Private
void runSchedulerForce(t_stack currentProcessStack, uint8_t force) {
	if (!initialized) {
		return;
	}

	if (nextProcessActivateOnTicks > 0 && ticks_elapsed() >= nextProcessActivateOnTicks) {
		wakeProcesses();
	}
	if (currentProcessNode != NULL) {
		processNodeADT myCurrentProcessNode = getProcessNodeFromNode(currentProcessNode);

		if (!force && getProcessState(myCurrentProcessNode->process) == P_RUNNING && 
				ticks_elapsed() - myCurrentProcessNode->executedOnTicks < quantumSlice[myCurrentProcessNode->priority]) {
			return;
		}
	}

	loadNextProcess(currentProcessStack);
}

void loadNextProcess(t_stack currentProcessStack) {
	nodeListADT nextProcessNode = fetchNextNode();
	if (nextProcessNode == NULL) {		
		if (currentProcessNode != NULL) {
			setProcessState(getProcessFromNode(currentProcessNode), P_READY, L_INVALID);
			updateProcessStack(getProcessStackFrame(getProcessFromNode(currentProcessNode)), currentProcessStack);
		}

		dispatchProcess(idleProcess, currentProcessStack);
		return;
	}

	if (nextProcessNode == currentProcessNode) {
		getProcessNodeFromNode(currentProcessNode)->executedOnTicks = ticks_elapsed();
	} else {
		if (currentProcessNode != NULL) {
			setProcessState(getProcessFromNode(currentProcessNode), P_READY, L_INVALID);
			updateProcessStack(getProcessStackFrame(getProcessFromNode(currentProcessNode)), currentProcessStack);
		}

		currentProcessNode = nextProcessNode;
		getProcessNodeFromNode(currentProcessNode)->executedOnTicks = ticks_elapsed();
		dispatchProcess(getProcessFromNode(currentProcessNode), currentProcessStack);
	}
}

nodeListADT fetchNextNode() {
	nodeListADT currentNode = currentProcessNode;
	if (currentNode == NULL) {
		currentNode = getNodeAtIndexList(readyQueue, 0);
	} else {
		currentNode = getNextNodeList(currentProcessNode);
	}

	while (currentNode != currentProcessNode && getSizeList(readyQueue) >= 1) {
		if (currentNode == NULL) {
			currentNode = getNodeAtIndexList(readyQueue, 0);
		} else {
			if (getProcessState(getProcessFromNode(currentNode)) == P_READY) {
				break;
			} else if (getProcessState(getProcessFromNode(currentNode)) == P_LOCKED) {
				moveNode(currentNode, readyQueue, waitingQueue);
			}

			currentNode = getNextNodeList(currentNode);
		}
	}
	if (currentNode == currentProcessNode) {
		t_state state = getProcessState(getProcessFromNode(currentNode));
		if (state != P_READY && state != P_RUNNING) return NULL;
		return currentNode;
	}
	if (getSizeList(readyQueue) == 0 || currentNode == NULL || getProcessState(getProcessFromNode(currentNode)) != P_READY) {
		return NULL;
	}

	return currentNode;
}

void dispatchProcess(t_process process, t_stack currentProcessStack) {
	setProcessState(process, P_RUNNING, L_INVALID);
	updateProcessStack(currentProcessStack, getProcessStackFrame(process));
}

nodeListADT getNode(pid_t pid, listADT list) {
	return searchNodeList(list, (void *)pid, equalsPid);
}

nodeListADT getNodeReadyQueue(pid_t pid) {
	return getNode(pid, readyQueue);
}

nodeListADT getNodeWaitingQueue(pid_t pid) {
	return getNode(pid, waitingQueue);
}

void removeProcess(nodeListADT processNode, listADT queue, t_stack stackFrame) {
	processNodeADT myProcessNode = getProcessNodeFromNode(processNode);
	removeNodeList(queue, processNode);
	
	if (myProcessNode->mode == S_M_FOREGROUND) {
		removeNodeFromForegroundStack(myProcessNode, stackFrame);
	} else {
		backgroundProcesses--;
	}

	postMutex(myProcessNode->waitpidMutex, getProcessStackFrameRegister(myProcessNode->process, REGISTER_RAX));
	closeMutex(myProcessNode->waitpidMutex);
	if (onProcessKill != NULL) onProcessKill(myProcessNode->process);
	pfree(myProcessNode, SYSTEM_PID);
}

void moveNode(nodeListADT processNode, listADT fromQueue, listADT toQueue) {
	moveNodeToIndexList(toQueue, fromQueue, processNode, getSizeList(toQueue));
}

void *duplicateProcessNode(void *_processNode) {
	processNodeADT processNode = (processNodeADT) _processNode;

	processNodeADT newProcessNode = pmalloc(sizeof(processNodeCDT), SYSTEM_PID);

	newProcessNode->process = duplicateProcessReadOnly(processNode->process);
	newProcessNode->executedOnTicks = processNode->executedOnTicks;
	newProcessNode->priority = processNode->priority;
	newProcessNode->mode = processNode->mode;

	return (void*)newProcessNode;
}

void freeProcessNodeReadOnly(void *_processNode) {
	processNodeADT processNode = (processNodeADT) _processNode;
	freeProcessReadOnly(processNode->process);
	pfree(processNode, SYSTEM_PID);
}

processNodeADT getProcessNodeFromNode(nodeListADT node) {
	if (node == NULL) return NULL;
	return (processNodeADT)(getElementList(node));
}

t_process getProcessFromNode(nodeListADT node) {
	if (node == NULL) return NULL;
	processNodeADT processNode = getProcessNodeFromNode(node);
	if(processNode != NULL)
		return processNode->process;
	return NULL;
	
}

int equalsPid(void *processNode, void *_pid) {
	t_process process = ((processNodeADT) processNode)->process;
	pid_t pid = (pid_t) _pid;
	return getProcessPid(process) == pid;
}

nodeListADT getNodePid(pid_t pid) {
	nodeListADT node = getNodeReadyQueue(pid);
	if (node == NULL)
		return getNodeWaitingQueue(pid);
	return node;
}

t_priority getProcessNodePriority(nodeListADT node) {
	if (node == NULL) return S_P_INVALID;
	processNodeADT processNode = getProcessNodeFromNode(node);
	if(processNode != NULL)
		return processNode->priority;
	return S_P_INVALID;
}

t_mode getProcessNodeMode(nodeListADT node) {
	if (currentProcessNode == NULL) return S_M_INVALID;
	processNodeADT processNode = getProcessNodeFromNode(node);
	if(processNode != NULL)
		return processNode->mode;
	return S_M_INVALID;
}

void printQueue(listADT queue, char *title) {
	printString(title, 0, 255, 0);
	printDec(getSizeList(queue), 0, 255, 0);
	newLine();
	printProcessHeaderScheduler();
	newLine();
	printList(queue, printProcessNode);
}

void printProcessNode(void *_processNode) {
	processNodeADT processNode = (processNodeADT)_processNode;
	printProcess(processNode->process);
	printString(" | ", 0, 255, 0);
	printString(getProcessModeString(processNode->mode), 0, 255, 0);
	printString(" | ", 0, 255, 0);
	printString(getProcessPriorityString(processNode->priority), 0, 255, 0);
	newLine();
}

void printProcessHeaderScheduler() {
	printProcessHeader();
	printString(" | MODE | PRIORITY", 0, 255, 0);
}

char *getProcessPriorityString(t_priority priority) {
	switch (priority) {
		case S_P_HIGH: return "HIGH";
		case S_P_LOW: return "LOW";
		default: return "INVALID";
	}
}

char *getProcessModeString(t_mode mode) {
	switch (mode) {
		case S_M_FOREGROUND: return "FOREGROUND";
		case S_M_BACKGROUND: return "BACKGROUND";
		default: {
			return "INVALID";
		}
  }
}

void wakeProcesses() {
	nodeListADT node = getNodeAtIndexList(waitingQueue, 0), nextNode = NULL;
	processNodeADT processNode;
	uint64_t ticks = ticks_elapsed();
	nextProcessActivateOnTicks = 0;

	while (node != NULL) {
		processNode = getProcessNodeFromNode(node);
		if(processNode == NULL)
			return;
		nextNode = getNextNodeList(node);

		if (processNode->activateOnTicks > 0) {
			if (processNode->activateOnTicks <= ticks) {
				processNode->activateOnTicks = 0;
				unlockProcess(getProcessPid(processNode->process), L_TIME);
			} else if (nextProcessActivateOnTicks == 0 || processNode->activateOnTicks < nextProcessActivateOnTicks) {
				nextProcessActivateOnTicks = processNode->activateOnTicks;
			}
		}

		node = nextNode;
	}
}

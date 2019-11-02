#include "processHandler.h"
#include "memManager.h"
#include "scheduler.h"
#include "stdio.h"
#include "time.h"

#define QUANTUM 4

typedef struct processNodeCDT *processNodeADT;

typedef struct processNodeCDT {
    uint64_t executedOnTicks;
    t_mode mode;
	t_process process;
	t_priority priority;
} processNodeCDT;

static const uint64_t quantumSlice[2] = {QUANTUM * 2, QUANTUM};

static nodeListADT currentProcessNode = NULL;
static listADT waitingQueue = NULL;
static listADT readyQueue = NULL;
static uint8_t initialized = 0;
static uint64_t backgroundProcesses = 0;
static uint64_t foregroundProcesses = 0;

static t_process idleProcess = NULL;
static void (*onProcessKill) (t_process process) = NULL;

void idleFunction();

void loadNextProcess(t_stack currentProcessStack);

nodeListADT fetchNextNode();

void dispatchProcess(t_process process, t_stack currentProcessStack);

nodeListADT getNodePid(pid_t pid);

nodeListADT getNode(pid_t pid, listADT queue);

nodeListADT getNodeReadyQueue(pid_t pid);

nodeListADT getNodeWaitingQueue(pid_t pid);

t_priority getProcessNodePriority(nodeListADT node);

void removeProcess(nodeListADT processNode, listADT queue);

void moveNode(nodeListADT processNode, listADT fromQueue, listADT toQueue);

processNodeADT getProcessNodeFromNode(nodeListADT node);

t_process getProcessFromNode(nodeListADT node);

void *duplicateProcessNode(void *_processNode);

void freeProcessNodeReadOnly(void *_processNode);

uint8_t equalsPid(void *_process, void *_pid);

void freeProcessNodeReadOnly(void *_processNode);

// Public
void initializeScheduler() {
	idleProcess = createProcess("Idle Process", processWrapper, SYSTEM_PID, SYSTEM_PID, 0, NULL, (int (*)(int, char**))idleFunction);

	waitingQueue = createList();
	readyQueue = createList();

	initialized = 1;
}

void runScheduler(t_stack currentProcessStack) {
	if (!initialized || getSizeList(readyQueue) == 0) {
		return;
	}

	if (currentProcessNode != NULL) {
		processNodeADT myCurrentProcessNode = getProcessNodeFromNode(currentProcessNode);

		if (getProcessState(myCurrentProcessNode->process) == P_RUNNING && 
				ticks_elapsed() - myCurrentProcessNode->executedOnTicks < quantumSlice[myCurrentProcessNode->priority]) {
			return;
		}
	}

	loadNextProcess(currentProcessStack);
}

uint8_t addProcess(t_process process, t_priority priority, t_mode mode) {
	if (priority == S_P_INVALID || mode == S_M_INVALID) return 0;

	processNodeADT processNode = pmalloc(sizeof(processNodeCDT), SYSTEM_PID);
	addElementToIndexList(readyQueue, processNode, getSizeList(readyQueue));

	processNode->executedOnTicks = 0;
	processNode->process = process;
	processNode->priority = priority;
	processNode->mode = mode;

	if (mode == S_M_FOREGROUND) {
		foregroundProcesses++;
	} else {
		backgroundProcesses++;
	}

	return 1;
}

void killProcess(pid_t pid, t_stack stackFrame) {
	nodeListADT processNode = getNodeReadyQueue(pid);
	if (processNode == NULL) {
		processNode = getNodeWaitingQueue(pid);
		if (processNode == NULL) return;

		removeProcess(processNode, waitingQueue);
		return;
	}

	if (processNode == currentProcessNode) {
		setProcessState(getProcessFromNode(processNode), P_DEAD);
		currentProcessNode = fetchNextNode();
		if (currentProcessNode != NULL)
			dispatchProcess(getProcessFromNode(currentProcessNode), stackFrame);
		else
			dispatchProcess(idleProcess, stackFrame);
	}

	removeProcess(processNode, readyQueue);
}

t_process getCurrentProcess() {
	if (currentProcessNode != NULL) return getProcessFromNode(currentProcessNode);
	return idleProcess;
}

t_priority getCurrentProcessPriority() {
	return getProcessNodePriority(currentProcessNode);
}

t_priority getProcessPriority(pid_t pid) {
	return getProcessNodePriority(getProcessNode(pid));
}

void lockProcess(pid_t pid) {
	nodeListADT processNode = getNodeReadyQueue(pid);
	if (processNode == NULL) return;
	setProcessState(getProcessFromNode(processNode), P_LOCKED);
	
	if (processNode == currentProcessNode) {
		currentProcessNode = fetchNextNode();
	}

	moveNode(processNode, readyQueue, waitingQueue);
	currentProcessNode = fetchNextNode();
	if (currentProcessNode != NULL)
		dispatchProcess(getProcessFromNode(currentProcessNode), stackFrame);
	else
		dispatchProcess(idleProcess, stackFrame);
}

void unlockProcess(pid_t pid) {
	nodeListADT processNode = getNodeWaitingQueue(pid);
	if (processNode == NULL) return;
	setProcessState(getProcessFromNode(processNode), P_READY);
	
	moveNode(processNode, waitingQueue, readyQueue);
}

void setCurrentProcessPriority(t_priority priority) {
	setProcessNodePriority(currentProcessNode, priority);
}

void setProcessPriority(pid_t pid, t_priority priority) {

}

void setProcessNodePriority(nodeListADT node, t_priority priority) {
	if (node == NULL) return;
	getProcessNodeFromNode(node)->priority = priority;
}

t_state getCurrentProcessState() {
	if (currentProcessNode == NULL) return P_INVALID;
	return getProcessState(getProcessFromNode(currentProcessNode));
}

void setCurrentProcessMode(t_mode mode) {
	if (currentProcessNode == NULL) return;
	processNodeADT processNode = getProcessNodeFromNode(currentProcessNode);
	if (processNode->mode == mode) return;
	processNode->mode = mode;

	if (mode == S_M_FOREGROUND) {
		foregroundProcesses++;
		backgroundProcesses--;
	} else {
		foregroundProcesses--;
		backgroundProcesses++;
	}
}

t_mode getCurrentProcessMode() {
	return getProcessNodeMode(currentProcessNode);
}

t_mode getProcessMode(pid_t pid) {
	return getProcessNodeMode(getProcessNode(pid));
}

void setOnProcessKillScheduler(void(_onProcessKill) (t_process process)) {
	onProcessKill = _onProcessKill;
}

// Iterator
listADT createProcessList() {
	listADT newList = duplicateList(readyQueue, duplicateProcessNode);
	return duplicateAndConcatList(newList, waitingQueue, duplicateProcessNode);
}

uint8_t hasNextProcess(listADT list) {
	return hasNextListIterator(list);
}

uint64_t getProcessListLength(listADT list) {
	return getSizeList(list);
}

t_process getNextProcess(listADT list) {
	if (!hasNextProcess(list)) return NULL;
	nodeListADT processNode = getNextNodeListIterator(list);
	if (processNode != NULL) {
		return getProcessFromNode(processNode);
	}
	return NULL;
}

void freeProcessesList(listADT list) {
	freeList(list, freeProcessNodeReadOnly);
}

// Private
void loadNextProcess(t_stack currentProcessStack) {
	nodeListADT nextProcessNode = fetchNextNode();
	if (nextProcessNode == NULL) {		
		if (currentProcessNode != NULL) {
			setProcessState(getProcessFromNode(currentProcessNode), P_READY);
			updateProcessStack(getProcessStackFrame(getProcessFromNode(currentProcessNode)), currentProcessStack);
		}

		dispatchProcess(idleProcess, currentProcessStack);
		return;
	}

	if (nextProcessNode == currentProcessNode) {
		getProcessNodeFromNode(currentProcessNode)->executedOnTicks = ticks_elapsed();
	} else {
		if (currentProcessNode != NULL) {
			setProcessState(getProcessFromNode(currentProcessNode), P_READY);
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
		return currentNode;
	}
	if (getSizeList(readyQueue) == 0 || currentNode == NULL || getProcessState(getProcessFromNode(currentNode)) != P_READY) {
		return NULL;
	}

	return currentNode;
}

void dispatchProcess(t_process process, t_stack currentProcessStack) {
	setProcessState(process, P_RUNNING);
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

void removeProcess(nodeListADT processNode, listADT queue) {
	processNodeADT myProcessNode = getProcessNodeFromNode(processNode);
	removeNodeList(queue, processNode);
	if (myProcessNode->mode == S_M_FOREGROUND) {
		foregroundProcesses--;
	} else {
		backgroundProcesses--;
	}
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
	return (processNodeADT)(getElementList(node));
}

t_process getProcessFromNode(nodeListADT node) {
	if (node == NULL) return NULL;
	return getProcessNodeFromNode(node)->process;
}

uint8_t equalsPid(void *_process, void *_pid) {
	t_process process = (t_process ) process;
	pid_t pid = (pid_t) _pid;
	return getProcessPid(process) == pid;
}

nodeListADT getNodePid(pid_t pid) {
	nodeListADT node = getNodeReadyQueue(pid);
	if (node == NULL)
		return getNodeWaitingQueue(pid);
	return NULL;
}

t_priority getProcessNodePriority(nodeListADT node) {
	if (node == NULL) return S_P_INVALID;
	return getProcessNodeFromNode(node)->priority;
}

t_mode getProcessNodeMode(nodeListADT node) {
	if (currentProcessNode == NULL) return S_M_INVALID;
	return getProcessNodeFromNode(currentProcessNode)->mode;
}

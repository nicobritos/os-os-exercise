#include "processHandler.h"
#include "memManager.h"
#include <stdint.h>
#include "list.h"

#define MAX(x, y) (x > y ? x : y)
#define MIN(x, y) (x < y ? x : y)

typedef struct nodeCDT {
	void *element;
	nodeADT next;
	nodeADT previous;
} nodeCDT;

typedef struct listCDT {
	nodeADT firstNode;
	nodeADT lastNode;
	uint64_t size;
	nodeADT currentNodeIterator;
	uint64_t initializedIterator;
} listCDT;

// Declarations
nodeADT fetchNodeAtIndex(listADT list, uint64_t index);
void addNodeToIndexList(listADT list, nodeADT node, uint64_t index);
void removeNodeListNoFree(listADT list, nodeADT node);
void freeNode(nodeADT node);

// Public
listADT createList() {
	listADT list = pmalloc(sizeof(listCDT), SYSTEM_PID);
	list->firstNode = list->lastNode = list->currentNodeIterator = NULL;
	list->size = list->initializedIterator = 0;
	return list;
}

nodeADT addElementToIndexList(listADT list, void *element, uint64_t index) {
	nodeADT node = pmalloc(sizeof(nodeCDT), SYSTEM_PID);
	node->element = element;
	addNodeToIndexList(list, node, index);
	return node;
}

nodeADT getNodeAtIndexList(listADT list, uint64_t index) {
	if (index >= list->size) return NULL;
	return fetchNodeAtIndex(list, index);
}

void removeNodeAtIndexList(listADT list, uint64_t index) {
	nodeADT node = getNodeAtIndexList(list, index);
	if (node == NULL) return NULL;
	removeNodeList(list, node);
}

void removeNodeList(listADT list, nodeADT node) {
	removeNodeListNoFree(list, node);
	freeNode(node);
}

uint8_t moveNodeToIndexList(listADT destination, listADT source, nodeADT node, uint64_t index) {
	removeNodeListNoFree(source, node);
	addNodeToIndexList(destination, node, index);
}

uint8_t isEmptyList(listADT list) {
	return list->size == 0;
}

uint64_t getSizeList(listADT list) {
	return list->size;
}

nodeADT searchNodeList(listADT list, uint8_t(searchFunction) (void * element)) {
	nodeADT node = list->firstNode;
	while (node != NULL && !searchFunction(node->element)) {
		node = node->next;
	}
	return node;
}

listADT duplicateList(listADT list, void *(duplicateElement) (void * element)) {
	listADT newList = createList();
	if (list->size == 0) {
		return newList;
	}

	nodeADT node = list->firstNode;
	nodeADT newNode;
	while (node != NULL) {
		newNode = pmalloc(sizeof(nodeCDT), SYSTEM_PID);
		newNode->element = duplicateElement(node->element);
		addNodeToIndexList(newList, newNode, newList->size);
		newList->size++;
	}

	return newList;
}

void freeList(listADT list, void(freeElement) (void * element)) {
	nodeADT node = list->firstNode;
	nodeADT auxNode;
	while (node != NULL) {
		auxNode = node->next;
		freeElement(node->element);
		pfree(node, SYSTEM_PID);
		node = auxNode;
	}
	pfree(list, SYSTEM_PID);
}

// Iterator
void prepareListIterator(listADT list) {
	list->currentNodeIterator = NULL;
	list->initializedIterator = 0;
}

uint8_t hasNextListIterator(listADT list) {
	return list->initializedIterator == 0 || list->currentNodeIterator->next != NULL;
}

nodeADT getNextNodeListIterator(listADT list) {
	if (!hasNextListIterator(list)) return NULL;
	if (list->initializedIterator == 0) {
		list->initializedIterator = 1;
		return list->currentNodeIterator = list->firstNode;
	}
	return list->currentNodeIterator = list->currentNodeIterator->next;
}

// Private
nodeADT fetchNodeAtIndex(listADT list, uint64_t index) {
	nodeADT auxNode;

	if (index == 0 || list->size == 0) {
		return list->firstNode;
	} else if (index >= list->size) {
		return list->lastNode;
	} else {
		uint8_t left = index <= list->size / 2;

		if (left) {
			auxNode = list->firstNode;
			while (index) {
				auxNode = auxNode->next;
				index--;
			}
		} else {
			index = list->size - index;
			auxNode = list->lastNode;
			while (index) {
				auxNode = auxNode->previous;
				index--;
			}
		}
	}

	return auxNode;
}

void addNodeToIndexList(listADT list, nodeADT node, uint64_t index) {
	if (list->size == 0) {
		node->previous = NULL;
		node->next = NULL;
		list->firstNode = node;
		list->lastNode = node;
	} else {
		if (index >= list->size) {
			node->previous = list->lastNode;
			node->next = NULL;
			list->lastNode = node;
			node->previous->next = node;
		} else {
			nodeADT auxNode = fetchNodeAtIndex(list, index);

			node->next = auxNode;
			node->previous = auxNode->previous;
			auxNode->previous = node;

			if (node->previous != NULL) {
				node->previous->next = node;
			} else {
				list->firstNode = node;
			}
		}
	}

	list->size++;
}

void removeNodeListNoFree(listADT list, nodeADT node) {
	if (node->previous != NULL) {
		node->previous->next = node->next;
	} else {
		list->firstNode = node->next;
	}

	if (node->next != NULL) {
		node->next->previous = node->previous;
	} else {
		list->lastNode = node->previous;
	}

	list->size--;
}

void freeNode(nodeADT node) {
	pfree(node, SYSTEM_PID);
}

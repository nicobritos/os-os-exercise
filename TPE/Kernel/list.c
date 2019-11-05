//This is a personal academic project. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "processHandler.h"
#include "memManager.h"
#include "list.h"

#define MAX(x, y) (x > y ? x : y)
#define MIN(x, y) (x < y ? x : y)

typedef struct nodeListCDT {
	void *element;
	nodeListADT next;
	nodeListADT previous;
} nodeListCDT;

typedef struct listCDT {
	nodeListADT firstNode;
	nodeListADT lastNode;
	uint64_t size;
	nodeListADT currentNodeIterator;
	uint64_t initializedIterator;
} listCDT;

// Declarations
nodeListADT fetchNodeAtIndex(listADT list, uint64_t index);
void addNodeToIndexList(listADT list, nodeListADT node, uint64_t index);
void removeNodeListNoFree(listADT list, nodeListADT node);
void freeNode(nodeListADT node);

// Public
listADT createList() {
	listADT list = pmalloc(sizeof(listCDT), SYSTEM_PID);
	list->firstNode = list->lastNode = list->currentNodeIterator = NULL;
	list->size = list->initializedIterator = 0;
	return list;
}

nodeListADT addElementToIndexList(listADT list, void *element, uint64_t index) {
	nodeListADT node = pmalloc(sizeof(nodeListCDT), SYSTEM_PID);
	node->element = element;
	addNodeToIndexList(list, node, index);
	return node;
}

nodeListADT getNodeAtIndexList(listADT list, uint64_t index) {
	if (index >= list->size) return NULL;
	return fetchNodeAtIndex(list, index);
}

nodeListADT getNextNodeList(nodeListADT node) {
	if (node != NULL) return node->next;
	return NULL;
}

void *getElementList(nodeListADT node) {
	if (node != NULL) return node->element;
	return NULL;
}


void removeNodeAtIndexList(listADT list, uint64_t index) {
	nodeListADT node = getNodeAtIndexList(list, index);
	if (node == NULL) return;
	removeNodeList(list, node);
}

void removeNodeList(listADT list, nodeListADT node) {
	removeNodeListNoFree(list, node);
	freeNode(node);
}

void moveNodeToIndexList(listADT destination, listADT source, nodeListADT node, uint64_t index) {
	removeNodeListNoFree(source, node);
	addNodeToIndexList(destination, node, index);
}

uint8_t isEmptyList(listADT list) {
	return list->size == 0;
}

uint64_t getSizeList(listADT list) {
	return list->size;
}

nodeListADT searchNodeList(listADT list, void *comparing, uint8_t(searchFunction) (void * element, void * comparing)) {
	nodeListADT node = list->firstNode;
	while (node != NULL && !searchFunction(node->element, comparing)) {
		node = node->next;
	}
	return node;
}

listADT duplicateList(listADT list, void *(duplicateElement) (void * element)) {
	return duplicateAndConcatList(NULL, list, duplicateElement);
}

listADT duplicateAndConcatList(listADT destination, listADT source, void *(duplicateElement) (void * element)) {
	if (destination == NULL) {
		destination = createList();
	}
	
	if (source->size == 0) {
		return destination;
	}

	nodeListADT node = source->firstNode;
	nodeListADT newNode;
	while (node != NULL) {
		newNode = pmalloc(sizeof(nodeListCDT), SYSTEM_PID);
		newNode->element = duplicateElement(node->element);
		addNodeToIndexList(destination, newNode, destination->size);
		destination->size++;
	}

	return destination;
}


void freeList(listADT list, void(freeElement) (void * element)) {
	nodeListADT node = list->firstNode;
	nodeListADT auxNode;
	while (node != NULL) {
		auxNode = node->next;
		if (freeElement != NULL)
			freeElement(node->element);
		pfree(node, SYSTEM_PID);
		node = auxNode;
	}
	pfree(list, SYSTEM_PID);
}

void printList(listADT list, void(printElement) (void * element)) {
	nodeListADT node = list->firstNode;
	while (node != NULL) {
		printElement(node->element);
		node = node->next;
	}
}

// Iterator
void prepareListIterator(listADT list) {
	list->currentNodeIterator = NULL;
	list->initializedIterator = 0;
}

uint8_t hasNextListIterator(listADT list) {
	return list->initializedIterator == 0 || list->currentNodeIterator->next != NULL;
}

nodeListADT getNextNodeListIterator(listADT list) {
	if (!hasNextListIterator(list)) return NULL;
	if (list->initializedIterator == 0) {
		list->initializedIterator = 1;
		return list->currentNodeIterator = list->firstNode;
	}
	return list->currentNodeIterator = list->currentNodeIterator->next;
}

// Private
nodeListADT fetchNodeAtIndex(listADT list, uint64_t index) {
	nodeListADT auxNode;

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

void addNodeToIndexList(listADT list, nodeListADT node, uint64_t index) {
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
			nodeListADT auxNode = fetchNodeAtIndex(list, index);

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

void removeNodeListNoFree(listADT list, nodeListADT node) {
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

void freeNode(nodeListADT node) {
	pfree(node, SYSTEM_PID);
}

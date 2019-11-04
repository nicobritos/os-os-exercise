#ifndef _LIST_DATA_STRUCTURE_H
	#include <stdint.h>
	#define _LIST_DATA_STRUCTURE_H

	typedef struct nodeListCDT *nodeListADT;
	typedef struct listCDT *listADT;

	listADT createList();

	nodeListADT addElementToIndexList(listADT list, void *element, uint64_t index);

	nodeListADT getNodeAtIndexList(listADT list, uint64_t index);

	nodeListADT getNextNodeList(nodeListADT node);

	void *getElementList(nodeListADT node);

	void removeNodeAtIndexList(listADT list, uint64_t index);
	
	void removeNodeList(listADT list, nodeListADT node);

	void moveNodeToIndexList(listADT destination, listADT source, nodeListADT node, uint64_t index);

	uint8_t isEmptyList(listADT list);

	uint64_t getSizeList(listADT list);

	nodeListADT searchNodeList(listADT list, void *comparing, uint8_t(searchFunction) (void * element, void * comparing));

	listADT duplicateList(listADT list, void *(duplicateElement) (void * element));

	listADT duplicateAndConcatList(listADT destination, listADT source, void *(duplicateElement) (void * element));

	void freeList(listADT list, void(freeElement) (void * element));
	
	void printList(listADT list, void(printElement) (void * element));

	// Iterator
	void prepareListIterator(listADT list);

	uint8_t hasNextListIterator(listADT list);

	nodeListADT getNextNodeListIterator(listADT list);

#endif
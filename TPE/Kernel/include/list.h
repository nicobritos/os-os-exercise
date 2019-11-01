#ifndef _LIST_DATA_STRUCTURE_H
	#define _LIST_DATA_STRUCTURE_H

	typedef struct nodeCDT *nodeADT;
	typedef struct listCDT *listADT;

	listADT createList();

	nodeADT addElementToIndexList(listADT list, void *element, uint64_t index);

	nodeADT getNodeAtIndexList(listADT list, uint64_t index);

	void removeNodeAtIndexList(listADT list, uint64_t index);
	
	void removeNodeList(listADT list, nodeADT node);

	uint8_t moveNodeToIndexList(listADT destination, listADT source, nodeADT node, uint64_t index);

	uint8_t isEmptyList(listADT list);

	uint64_t getSizeList(listADT list);

	nodeADT searchNodeList(listADT list, uint8_t(searchFunction) (void * element));

	listADT duplicateList(listADT list, void *(duplicateElement) (void * element));

	void freeList(listADT list, void(freeElement) (void * element));

	// Iterator
	void prepareListIterator(listADT list);

	nodeADT getNextNodeListIterator(listADT list);

	uint8_t hasNextListIterator(listADT list);

#endif
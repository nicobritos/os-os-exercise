#ifndef _MEM_MANAGER_H_
#define _MEM_MANAGER_H_

#include <stdint.h>

#define NULL ((void *) 0)
#define FALSE 0
#define TRUE !FALSE
#define TREE_ADDRESS ((void *) 0x0000000000050000)
#define TREE_END_ADDRESS ((void *) 0x000000000009FFFF)
#define TREE_MAX_SIZE ((uint64_t)((uint64_t)TREE_END_ADDRESS - (uint64_t)TREE_ADDRESS)) // 327680
#define MEM_SIZE 1048576 // 1 MiB (a parte de la usada para el arbol)
#define MAX_NODES 8192 // 2^(floor(log2((TREE_MAX_SIZE / sizeof(Node))))    (MAXIMA CANTIDAD DE NODOS QUE ENTRAN ENTRE TREE_ADDRESS Y TREE_END_ADDRESS)
#define MIN_BLOCK_SIZE (MEM_SIZE / MAX_NODES) // 128
#define MEM_STARTING_ADDRESS ((void *)0x0000000000100000)

typedef char bool;

typedef struct Node{ // SI SE CAMBIA, HAY QUE EL DEFINE DE MAX_NODES
	int size;
	void * address;
	uint64_t pid;
	struct Node * left;
	struct Node * right;   // If both ptrs are NULL, then this is a process, else, its a full or partially full node
    bool isFull;    // To know if the node is partially full, or entirely full (if empty, then there shouldnt be a node)
}Node;

// void printTree();
void initializeMemoryManager();
void * pmalloc(uint64_t size, uint64_t pid);
void * prealloc(void * ptr, uint64_t newSize, uint64_t pid);
void pfree(uint64_t pid, void * address);

#endif
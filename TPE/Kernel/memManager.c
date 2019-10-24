#include "memManager.h"

#define FALSE 0
#define TRUE !FALSE
#define NULL ((void *)0)

#define MEM_SIZE 1048576 // 1 MiB (a parte de la usada para el arbol)

#define TREE_ADDRESS ((void *) 0x0000000000050000)
#define TREE_END_ADDRESS ((void *) 0x000000000009FFFF)
#define TREE_MAX_SIZE ((uint64_t)((uint64_t)TREE_END_ADDRESS - (uint64_t)TREE_ADDRESS)) // 327680
#define MAX_NODES 8192 // 2^(floor(log2((TREE_MAX_SIZE / sizeof(Node))))    (MAXIMA CANTIDAD DE NODOS QUE ENTRAN ENTRE TREE_ADDRESS Y TREE_END_ADDRESS)
#define MIN_BLOCK_SIZE (MEM_SIZE / MAX_NODES) // 128

#define MAX_LIST_NODES 8192  //2^(floor(log2((TREE_MAX_SIZE - sizeof(List))/ sizeof(ListNode)))    (MAXIMA CANTIDAD DE NODOS QUE ENTRAN ENTRE TREE_ADDRESS Y TREE_END_ADDRESS)
#define MIN_PAGE_SIZE (MEM_SIZE / MAX_LIST_NODES) // 128

typedef char bool;

/* BUDDY */
typedef struct Node{ // SI SE CAMBIA, HAY QUE CAMBIAR EL DEFINE DE MAX_NODES
    int size;
    void * address;
    uint64_t pid;
    struct Node * left;
    struct Node * right;   // If both ptrs are NULL, then this is a process, else, its a full or partially full node
    bool isFull;    // To know if the node is partially full, or entirely full (if empty, then there shouldnt be a node)
}Node;

Node createNode(void * address, uint64_t size, uint64_t pid);
void * buddyAlloc(uint64_t size, uint64_t pid);
void * recursiveBuddyAlloc(uint64_t size, uint64_t pid, uint64_t childBlockSize, Node * parent, uint64_t parentBlockSize);
void createLeftChild(Node * parent, uint64_t size, uint64_t pid);
void createRightChild(Node * parent, uint64_t childsBlockSize, uint64_t size, uint64_t pid);
// void recPrint(Node * node, int depth);
Node * nextFreeSpaceForNode();
bool pBuddyFreeRec(uint64_t pid, void * address, Node * current);
void buddyInitializer();

Node * root = TREE_ADDRESS;
bool isOccupiedNodeSpace[MAX_NODES];
uint64_t lastUsedIndex; // Of the isOccupiedNodeSpace array


/* FREE LIST */
typedef struct ListNode // SI SE CAMBIA, HAY QUE CAMBIAR EL DEFINE DE MAX_LIST_NODES
{
    struct ListNode * next;
    struct ListNode * prev;
    void * data;
}ListNode;

typedef struct List // SI SE CAMBIA, HAY QUE CAMBIAR EL DEFINE DE MAX_LIST_NODES
{
    ListNode * head;
    ListNode * last;
}List;

ListNode * nextFreeSpaceForListNode();
void pListFree(void * address);
void addNode(void * address);
void freeListInitializer();

List * list = TREE_ADDRESS;
bool isOccupiedNodeSpace[MAX_LIST_NODES];
uint64_t lastUsedListNodeIndex; // Of the isOccupiedNodeSpace array



void initializeMemoryManager(){
    buddyInitializer();
}

/* Auxiliar, constructor de nodo */

void * pmalloc(uint64_t size, uint64_t pid){
    return buddyAlloc(size, pid); // Marca la direccion como ocupada en el arbol del buddy
}

void pfree(uint64_t pid, void * address){
    pBuddyFreeRec(pid, address, root);
}

void * prealloc(void * ptr, uint64_t newSize, uint64_t pid){
    pfree(pid, ptr);
    return pmalloc(newSize, pid);
}

/* BUDDY IMPLEMENTATION */
void buddyInitializer(){
    isOccupiedNodeSpace[0] = TRUE;
    lastUsedIndex = 0;
    for (uint64_t i = 1; i < MAX_NODES; i++)
    {
        isOccupiedNodeSpace[i] = FALSE;
    }
    
    Node rootNode = createNode(MEM_STARTING_ADDRESS, sizeof(*root), 0);
    memcpy(root, &rootNode, sizeof(*root));
}

Node createNode(void * address, uint64_t size, uint64_t pid){
    Node node;
    node.size = size;
    node.address = address;
    node.pid = pid;
    node.left = NULL;
    node.right = NULL;
    node.isFull = FALSE;
    return node;
}

void * buddyAlloc(uint64_t size, uint64_t pid){
    uint64_t childBlockSize;
    for (childBlockSize = MIN_BLOCK_SIZE; childBlockSize < size; childBlockSize *= 2); // Me fijo cual es la menor potencia de 2 que es mayor al size
    return recursiveBuddyAlloc(size, pid, childBlockSize, root, MEM_SIZE);
}

void * recursiveBuddyAlloc(uint64_t size, uint64_t pid, uint64_t childBlockSize, Node * parent, uint64_t parentBlockSize){
    if(parentBlockSize <= childBlockSize) // Me pasé
        return NULL;
    
    if(parent->left == NULL){
        createLeftChild(parent, size, pid);
        parentBlockSize /= 2;
        Node * parentsParent = parent;
        parent = parent->left;
        while(parentBlockSize > childBlockSize){ // Creo siempre a la izquierda hasta llegar al tamaño
            createLeftChild(parent, size, pid);
            parent = parent->left;
            parentBlockSize /= 2;
        }
        parent->isFull = TRUE;
        if(parentsParent->left == parent)
            parentsParent->isFull = TRUE;
        return parent->address;
    }
    if(!(parent->left->isFull)){
        void * ans = recursiveBuddyAlloc(size, pid, childBlockSize, parent->left, parentBlockSize/2);
        if(ans != NULL){
            if(parent->right != NULL && parent->right->isFull && parent->left->isFull){
                parent->isFull = TRUE;
            }
        }
        return ans;
    }
    if(parent->right == NULL){
        createRightChild(parent, parentBlockSize/2, size, pid);
        parentBlockSize /= 2;
        Node * parentsParent = parent;
        parent = parent->right;
        while(parentBlockSize > childBlockSize){ // Creo siempre a la izquierda hasta llegar al tamaño
            createLeftChild(parent, size, pid);
            parent = parent->left;
            parentBlockSize /= 2;
        }
        parent->isFull = TRUE;
        if(parentsParent->right == parent)
            parentsParent->isFull = TRUE;
        return parent->address;
    }
    if(!(parent->right->isFull)){
        void * ans = recursiveBuddyAlloc(size, pid, childBlockSize, parent->right, parentBlockSize/2); //ACASDASDASDASDASDASDASDASDASDASDA
        if(ans != NULL){
            if((parent->right->left != NULL) && (parent->right->right != NULL) && (parent->right->left->isFull) && (parent->right->right->isFull)){
                parent->right->isFull = TRUE;
                parent->isFull = TRUE; // YA CHEQUE ANTES QUE LEFT ESTABA FULL
            }
        }
        return ans;
    }
    return NULL; // no tengo espacio
}

void createLeftChild(Node * parent, uint64_t size, uint64_t pid){
    Node child = createNode(parent->address, size, pid); //primera mitad
    void * nodeSpace = nextFreeSpaceForNode();
    memcpy(nodeSpace, &child, sizeof(child));
    parent->left = nodeSpace;
}

void createRightChild(Node * parent, uint64_t childsBlockSize, uint64_t size, uint64_t pid){
    Node child = createNode(parent->address + childsBlockSize, size, pid); //segunda mitad
    void * nodeSpace = nextFreeSpaceForNode();
    memcpy(nodeSpace, &child, sizeof(child));
    parent->right = nodeSpace;
}

Node * nextFreeSpaceForNode(){
    uint64_t i;
    for (i = (lastUsedIndex + 1) % MAX_NODES; i != lastUsedIndex; i = (i + 1) % MAX_NODES)
    {
        if(isOccupiedNodeSpace[i] == FALSE){
            isOccupiedNodeSpace[i] = TRUE;
            return root + i;
        }
    }
    if(isOccupiedNodeSpace[i] == FALSE){ // Por si se libero el ultimo espacio reservado
        return root + i;
    }
    return NULL;
}

// void printTree(){
//     recPrint(root, 0);
// }

// void recPrint(Node * node, int depth){
//     printf("address = %p - pid = %" PRId64 " - isFull = %d\n", node->address, node->pid, node->isFull);
    
//     if(node->left != NULL){
//         for (int i = 0; i < depth; i++)
//         {
//             printf("\t");
//         }
//         printf("LEFT CHILD - ");
//         recPrint(node->left, depth + 1);
//     }
    
//     if(node->right != NULL){
//         for (int i = 0; i < depth; i++)
//         {
//             printf("\t");
//         }
//         printf("RIGHT CHILD - ");
//         recPrint(node->right, depth + 1);
//     }
// }

bool pBuddyFreeRec(uint64_t pid, void * address, Node * current){
    if(current == NULL)
        return FALSE;
    if((current->left == NULL) && (current->right == NULL)){
        if((pid == current->pid) && (address == current->address)){
            return TRUE; // liberar
        }
        return FALSE; // no liberar
    }

    if(current->left == NULL){
        if(pBuddyFreeRec(pid, address, current->right)){
            current->right = NULL;
            return TRUE;
        }
    }
    if(current->right == NULL){
        if(pBuddyFreeRec(pid, address, current->left)){
            current->left = NULL;
            return TRUE;
        }
    }
    if(pBuddyFreeRec(pid, address, current->left) == FALSE){
        if(pBuddyFreeRec(pid, address, current->right)){
            current->right = NULL;
        }
    }
    else{
        current->left = NULL;
    }
    if(current->isFull){
        if((current->left == NULL || !(current->left->isFull)) || (current->right == NULL || !(current->right->isFull)))
            current->isFull = FALSE;
    }
    return FALSE;
    
}

void freeListInitializer(){
    // list = malloc(TREE_MAX_SIZE); // CAMBIAR ESTO
    List listHeader;
    listHeader.last = listHeader.head = (ListNode * )(list + 1);
    memcpy(list, &listHeader, sizeof(*list));
    for (uint64_t i = 0; i < MAX_LIST_NODES; i++)
    {
        addNode(MEM_STARTING_ADDRESS + i * MIN_PAGE_SIZE);
    }   
}

void addNode(void * address){
    ListNode node;
    node.prev = list->last;
    node.next = NULL;
    node.data = address;
    list->last = nextFreeSpaceForListNode();
    memcpy(list->last, &node, sizeof(node));
}

ListNode * nextFreeSpaceForListNode(){
    uint64_t i;
    for (i = (lastUsedListNodeIndex + 1) % MAX_LIST_NODES; i != lastUsedListNodeIndex; i = (i + 1) % MAX_LIST_NODES)
    {
        if(isOccupiedNodeSpace[i] == FALSE){
            isOccupiedNodeSpace[i] = TRUE;
            return list->head + i;
        }
    }
    if(isOccupiedNodeSpace[i] == FALSE){ // Por si se libero el ultimo espacio reservado
        return list->head + i;
    }
    return NULL;
}

void pListFree(void * address){
    //addNode(address);

}
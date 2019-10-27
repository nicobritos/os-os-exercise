#include "include/memManager.h"
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

#ifdef MODO_BUDDY
/* -------------------------------BUDDY-------------------------------*/

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
void * recursiveBuddyAlloc(uint64_t size, uint64_t pid, uint64_t blockSizeWanted, Node * current, uint64_t currentLevelSize);

void createLeftChild(Node * parent, uint64_t size, uint64_t pid);
void createRightChild(Node * parent, uint64_t childsBlockSize, uint64_t size, uint64_t pid);
// void recPrint(Node * node, int depth);
Node * nextFreeSpaceForNode();

void pBuddyFree(uint64_t pid, void * address);
bool pBuddyFreeRec(uint64_t pid, void * address, Node * current);
void buddyInitializer();
uint64_t freeMemBuddy();
uint64_t usedMemBuddy();

Node * root = TREE_ADDRESS;
bool isOccupiedNodeSpace[MAX_NODES];
uint64_t lastUsedIndex; // Of the isOccupiedNodeSpace array
uint64_t memUsed;



void buddyInitializer(){
    isOccupiedNodeSpace[0] = TRUE;
    lastUsedIndex = 0;
    for (uint64_t i = 1; i < MAX_NODES; i++)
    {
        isOccupiedNodeSpace[i] = FALSE;
    }
    
    Node rootNode = createNode(MEM_STARTING_ADDRESS, 0, 0);
    memcpy(root, &rootNode, sizeof(*root));
    memUsed = 0;
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
    void * ans = recursiveBuddyAlloc(size, pid, childBlockSize, root, MEM_SIZE);
    if(ans != NULL)
        memUsed += childBlockSize;
    return ans;
}

void * recursiveBuddyAlloc(uint64_t size, uint64_t pid, uint64_t blockSize, Node * current, uint64_t currentLevelSize){
    if((current == NULL) || (currentLevelSize < blockSize) || (current->isFull)){ // estado invalido
        return NULL;
    }
    if(currentLevelSize == blockSize){
        if((current->left == NULL) && (current->right == NULL)){ // este es su lugar en el arbol
            current->isFull = TRUE;
            current->pid = pid;
            current->size = size;
            return current->address;
        }
        else{ // no tiene que ir por esta rama del arbol
            return NULL; 
        }
    }
    void * ans;
    if(current->left == NULL){ // si o si esta en esta rama su lugar
        createLeftChild(current, size, pid);
        ans = recursiveBuddyAlloc(size, pid, blockSize, current->left, currentLevelSize/2);
    }
    else{
        ans = recursiveBuddyAlloc(size, pid, blockSize, current->left, currentLevelSize/2); // me fijo si va en el hijo izquierdo 
        if(ans == NULL){
            if(current->right == NULL){ // si no existe hijo derecho lo creo
                createRightChild(current, currentLevelSize, size, pid);
            }
            ans = recursiveBuddyAlloc(size, pid, blockSize, current->right, currentLevelSize/2); // me fijo si va en el hijo derecho
        }
    }
    if((current->left->isFull) && (current->right != NULL) && (current->right->isFull)){
        current->isFull = TRUE;
    }
    return ans;
}

void createLeftChild(Node * parent, uint64_t size, uint64_t pid){
    Node child = createNode(parent->address, size, pid); //primera mitad
    void * nodeSpace = nextFreeSpaceForNode();
    memcpy(nodeSpace, &child, sizeof(child));
    parent->left = nodeSpace;
}

void createRightChild(Node * parent, uint64_t parentBlockSize, uint64_t size, uint64_t pid){
    Node child = createNode((char *)parent->address + parentBlockSize/2, size, pid); //segunda mitad
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

void pBuddyFree(uint64_t pid, void * address){
    pBuddyFreeRec(pid, address, root);
}

bool pBuddyFreeRec(uint64_t pid, void * address, Node * current){
    if(current == NULL)
        return FALSE;
    if((current->left == NULL) && (current->right == NULL)){ // es memoria ocupada
        if((pid == current->pid) && (address == current->address)){
            uint64_t i;
            for ( i = 1; i < current->size; i*=2);
            memUsed -= i; 
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

uint64_t freeMemBuddy(){
    return MEM_SIZE - usedMemBuddy();
}

uint64_t usedMemBuddy(){
    return memUsed;
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
#endif

#ifdef MODO_FREE_LIST
/* -------------------------------FREE LIST-------------------------------*/
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
    uint64_t listSize;
}List;

typedef struct
{
    void * startingAddress;
    uint64_t blocks;
}TableRow;

typedef TableRow Table[MAX_LIST_NODES];

struct occupiedRow
{
    bool isOccupied;
    ListNode * address;
};

Table table;

ListNode * nextFreeSpaceForListNode(void * address);
void pListFree(void * address);
void addNode(void * address);
void removeNode(ListNode * node);
void freeListInitializer();
void * lookAndRemoveBlocksRec(ListNode * node, uint64_t totalBlocks, uint64_t blocks);
void * lookAndRemoveBlocks(uint64_t blocks);
uint64_t freeTableRow();
void * pListMalloc(uint64_t size);
int64_t lookInTable(void * address);
int64_t findMemIndex(ListNode * node);
uint64_t freeMemList();
uint64_t usedMemList();

List * list = TREE_ADDRESS;
struct occupiedRow isOccupiedNodeSpace[MAX_LIST_NODES];
uint64_t lastUsedListNodeIndex; // Of the isOccupiedNodeSpace array

void freeListInitializer(){ // EL NEXT DEL HEAD ME QUEDA EN NULL POR ALGUNA RAZON
    list->head = list->last = NULL;
    for (uint64_t i = 0; i < MAX_LIST_NODES; i++)
    {
        table[i].startingAddress = NULL;
        table[i].blocks = 0;
        addNode((char *)MEM_STARTING_ADDRESS + i * MIN_PAGE_SIZE);
    }
}

void addNode(void * address){
    if(((char *)address - (char *)MEM_STARTING_ADDRESS)% MIN_PAGE_SIZE != 0){ // No es un address valido
        return;
    }
    if(list->head == NULL){ // list is empty
        list->last = list->head = nextFreeSpaceForListNode(address);
        list->head->next = NULL;
        list->head->prev = NULL;
        list->head->data = address;
    }
    else{ 
        ListNode * node = nextFreeSpaceForListNode(address);
        node->data = address;
        ListNode * current = list->head;
        while((current!= NULL) && (current->data < address)){ // go to the position where it should be inserted
            current = current->next;
        }
        if(current == NULL){ //insert at the end
            node->prev = list->last;
            node->next = NULL;
            list->last->next = node;
            list->last = node;
        }
        else if(current->prev == NULL) //insert at the beggining
        {
            node->prev = NULL;
            node->next = list->head;
            list->head->prev = node;
            list->head = node;
        }
        else //insert between two nodes
        {
            node->prev = current->prev;
            node->next = current;
            current->prev->next = node;
            current->prev = node;
        }
    }
}

ListNode * nextFreeSpaceForListNode(void * address){
    uint64_t i;
    for (i = (lastUsedListNodeIndex + 1) % MAX_LIST_NODES; i != lastUsedListNodeIndex; i = (i + 1) % MAX_LIST_NODES)
    {
        if(isOccupiedNodeSpace[i].isOccupied == FALSE){
            isOccupiedNodeSpace[i].isOccupied = TRUE;
            isOccupiedNodeSpace[i].address = address;
            (list->listSize)++;
            return ((ListNode *)(list + 1)) + i;
        }
    }
    if(isOccupiedNodeSpace[i].isOccupied == FALSE){ // Por si se libero el ultimo espacio reservado
        isOccupiedNodeSpace[i].isOccupied = TRUE;
        isOccupiedNodeSpace[i].address = address;
        (list->listSize)++;
        return ((ListNode *)(list + 1)) + i;
    }
    return NULL;
}

void pListFree(void * address){
    int64_t index = lookInTable(address);
    if(index == -1)
        return;
    for(int i=0; i<table[index].blocks; i++){
        addNode((char *)address + i*MIN_PAGE_SIZE);
    }
    table[index].startingAddress = NULL;
    table[index].blocks = 0;
}

int64_t lookInTable(void * address){
    for (uint64_t i = 0; i < MAX_LIST_NODES; i++)
    {
        if(table[i].startingAddress == address)
            return i;
    }
    return -1;
    
}

void * pListMalloc(uint64_t size){
    uint64_t blocks;
    for (blocks = 0; blocks * MIN_PAGE_SIZE < size; blocks++);
    uint64_t index = freeTableRow();
    if(index == MAX_LIST_NODES + 1)
        return NULL;
    table[index].startingAddress = lookAndRemoveBlocks(blocks);
    if(table[index].startingAddress != NULL){
        table[index].blocks = blocks;
    }
    return table[index].startingAddress;
}

uint64_t freeTableRow(){
    for(uint64_t i = 0; i<MAX_LIST_NODES; i++){
        if(table[i].startingAddress == NULL)
            return i;
    }
    return MAX_LIST_NODES + 1;
}

void * lookAndRemoveBlocks(uint64_t blocks){
    return lookAndRemoveBlocksRec(list->head, blocks, blocks);
}

void * lookAndRemoveBlocksRec(ListNode * node, uint64_t totalBlocks, uint64_t blocks){
    if(node == NULL)
        return NULL;
    if(blocks == 1){
        removeNode(node);
        return node->data;
    }
    if(node->next == NULL)
        return NULL;
    if(node->next->data == (char *)node->data + MIN_PAGE_SIZE){
        void * ans = lookAndRemoveBlocksRec(node->next, totalBlocks, blocks-1);
        if(ans == (char *)node->data + MIN_PAGE_SIZE){
            removeNode(node);
            return node->data;
        }
        else{
            return ans;
        }
    }
    return lookAndRemoveBlocksRec(node->next, totalBlocks, totalBlocks);
}

void removeNode(ListNode * node){
    if(node == NULL)
        return;
    if(node == list->head){
        // cambio de cabeza
        list->head = list->head->next;
        if(list->head != NULL)
            list->head->prev = NULL;
        else
            list->last = NULL;
    }
    else{
        node->prev->next = node->next;
        if(node->next != NULL){
            node->next->prev = node->prev;
        }
        else{
            // cambio de last
            list->last = node->prev;
        }
    }
    isOccupiedNodeSpace[findMemIndex(node)].isOccupied = FALSE;
    (list->listSize)--;
}

int64_t findMemIndex(ListNode * node){
    for(int64_t i=0; i<MAX_LIST_NODES; i++){
        if(isOccupiedNodeSpace[i].address == node->data){
            return i;
        }
    }
    return -1;
}

uint64_t freeMemList(){
    return (list->listSize) * MIN_PAGE_SIZE;
}
uint64_t usedMemList(){
    return (uint64_t)MEM_SIZE - freeMemList();
}

// void printTable(){
//     for (int i = 0; i < MAX_LIST_NODES; i++)
//     {
//         if((table[i].startingAddress != NULL) && (table[i].blocks != 0))
//             printf("%d.  %p - %p - %" PRId64 "\n", i, table[i].startingAddress, (void*)((char*)table[i].startingAddress + table[i].blocks*MIN_PAGE_SIZE),table[i].blocks);
//     }
// }

// void printList(){
//     for (ListNode * current = list->head; current; current = current->next)
//     {
//         printf("%p->", current->data);
//     }
//     printf("\n");
// }
#endif

/* -------------------------------GENERIC-------------------------------*/

void initializeMemoryManager(){
    #ifdef MODO_BUDDY
    buddyInitializer();
    #endif
    #ifdef MODO_FREE_LIST
    freeListInitializer();
    #endif
}

void * pmalloc(uint64_t size, uint64_t pid){
    if(size == 0)
        return NULL;
    #ifdef MODO_BUDDY
    return buddyAlloc(size, pid); // Marca la direccion como ocupada en el arbol del buddy
    #endif
    #ifdef MODO_FREE_LIST
    return pListMalloc(size);
    #endif
}

void pfree(void * address, uint64_t pid){
    if(address == NULL)
        return;
    #ifdef MODO_BUDDY
    pBuddyFree(pid, address);
    #endif
    #ifdef MODO_FREE_LIST
    pListFree(address);
    #endif
    
}

void * prealloc(void * ptr, uint64_t newSize, uint64_t pid){
    #ifdef MODO_BUDDY
    pfree(ptr, pid);
    return pmalloc(newSize, pid);
    #endif
    #ifdef MODO_FREE_LIST
    pListFree(ptr);
    return pListMalloc(newSize);
    #endif
}

uint64_t freeMemoryLeft(){
    #ifdef MODO_BUDDY
    return freeMemBuddy();
    #endif
    #ifdef MODO_FREE_LIST
    return freeMemList();
    #endif
}
uint64_t usedMemory(){
    #ifdef MODO_BUDDY
    return usedMemBuddy();
    #endif
    #ifdef MODO_FREE_LIST
    return usedMemList();
    #endif
}

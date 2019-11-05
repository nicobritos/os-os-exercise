#include "include/phylo.h"
#include "include/newSyscalls.h"
#include "include/stdlib.h"
#include "include/process.h"
#include "include/stdio.h"
#include "include/unistd.h"

#define MAX_PHYLOS 100

void addPhylo();
void createPhylo();
void removePhylo();
int phylo(int argc, char * argv[]);
void printTable();

typedef struct
{
    void * fork;
    pid_t usedBy;
}t_fork;


t_fork forks[MAX_PHYLOS];
int currentQty = 0;

pid_t phylosPids[MAX_PHYLOS];
int phylosIds[MAX_PHYLOS];

void ** argvs[MAX_PHYLOS];

int phyloProblem(int argc, char * argv[]){
    int initQty = argv[0];
    if(initQty > MAX_PHYLOS)
        return -1;
    for (int i = 0; i < initQty; i++){
        createPhylo();
    }
    char c[3];
    //printf("Created\n");
    scanf(c, 2, '\n');
    while((c[0] != 'e') || (c[0] != 'E')){
        printf("\nToy");
        switch (c[0]){
            case 'r': case 'R':
                removePhylo();
                break;
            case 'a': case 'A':
                addPhylo();
                break;
            default:
                printTable();
        }
        scanf(c, 2, '\n');
    }
    printf("Bye bye\n");
    return 0;
}

void addPhylo(){
    if(currentQty >= MAX_PHYLOS)
        return;
    createPhylo();
}

void createPhylo(){
    char semName[8] = "Fork-00";
    semName[5] = currentQty/10 + '0';
    semName[6] = currentQty % 10 + '0';
    forks[currentQty].fork = sys_createSem(semName);
    sys_post_semaphore(forks[currentQty].fork); // para marcar que empieza libre
    forks[currentQty].usedBy = -1;

    char name[9] = "Phylo-00";
    name[6] = currentQty/10 + '0';
    name[7] = currentQty % 10 + '0';
    phylosIds[currentQty] = currentQty;
    // printf("Id: %d\n", phylosIds[currentQty]);
    argvs[phylosIds[currentQty]] = malloc(3 * sizeof(*(argvs[phylosIds[currentQty]])));
    argvs[phylosIds[currentQty]][0] = (void *)&(phylosIds[currentQty]); // puntero al id
    argvs[phylosIds[currentQty]][1] = (void *)&(forks[currentQty]); // puntero al fork de la derecha
    argvs[phylosIds[currentQty]][2] = (void *)&(forks[0]); // puntero al fork de la izquierda
    //printf("\nId phylo send= %d\n", *((int *)(argvs[phylosIds[currentQty]][0])));
    //printf("argv send = %x\n", argvs[phylosIds[currentQty]]);
    phylosPids[currentQty] = sys_newProcess(name, phylo, 3, (char **)argvs[phylosIds[currentQty]], S_M_BACKGROUND);
    // printf("Created %s - %d\n", name, phylosPids[currentQty]);

    if(currentQty != 0){
        char post1, post2;
        post1 = post2 = 0;

        if((forks[currentQty-1].usedBy == currentQty -1)){
            sys_wait_semaphore(forks[currentQty-1].fork);
            post1 = 1;
        }
        if(forks[0].usedBy == currentQty - 1){
            sys_wait_semaphore(forks[0].fork);
            post2 = 1;
        }
        sys_freeProcess(phylosPids[currentQty - 1]);
        // printf("Removed id: %d - %d\n", phylosIds[currentQty - 1], phylosPids[currentQty - 1]);
        name[6] = (currentQty-1)/10 + '0';
        name[7] = (currentQty-1) % 10 + '0';
        phylosIds[currentQty-1] = currentQty -1;
        //printf("free: %x", argvs[phylosIds[currentQty]]);
        free(argvs[phylosIds[currentQty-1]]);
        argvs[phylosIds[currentQty-1]] = malloc(3 * sizeof(*(argvs[phylosIds[currentQty-1]])));
        argvs[phylosIds[currentQty-1]][0] = &(phylosIds[currentQty-1]);
        argvs[phylosIds[currentQty-1]][1] = &(forks[currentQty-1]);
        argvs[phylosIds[currentQty-1]][2] = &(forks[currentQty]);
        //printf("\nId phylo send= %d\n", *((int *)(argvs[phylosIds[currentQty-1]][0])));
        //printf("argv send = %x\n", argvs[phylosIds[currentQty-1]]);
        phylosPids[currentQty - 1] = sys_newProcess(name, phylo, 3, (char **)argvs[phylosIds[currentQty-1]], S_M_BACKGROUND);
        // printf("Created id: %d - %d\n", phylosIds[currentQty-1], phylosPids[currentQty-1]);
        if(post1)
            sys_post_semaphore(forks[currentQty-1].fork);
        if(post2)
            sys_post_semaphore(forks[0].fork);
    }
    currentQty++;
}

void removePhylo(){
    if(currentQty == 0)
        return;
    currentQty--;
    sys_closeSem(forks[currentQty].fork);
    if(forks[0].usedBy == phylosIds[currentQty]){
        forks[0].usedBy = -1;
        sys_freeProcess(phylosPids[currentQty]);
        sys_post_semaphore(forks[0].fork);
    }
    else{
        sys_freeProcess(phylosPids[currentQty]);
    }
    free(argvs[phylosIds[currentQty]]);
}

int phylo(int argc, char * argv[]){
    //for (int i = 0; i < argc; i++)
    //{
    //printf("\nargv recieved %x\n", argv);
    //}
    
    if(argc != 3)
        return 1;
    int id = *((int *)(argv[0]));
    //printf("Id phylo received= %d\n", id);
    t_fork * rightFork = (t_fork *)argv[1];
    t_fork * leftFork = (t_fork *)argv[2];
    free(argv);
    while(1){
        printf("\n%d is thinking...\n", id);
        sleep(5000);
        printf("%d is hungry\n", id);
        sys_wait_semaphore(rightFork->fork);
        rightFork->usedBy = id;
        printf("%d took his right fork\n", id);
        sys_wait_semaphore(leftFork->fork);
        leftFork->usedBy = id;
        printf("%d took his left fork\n", id);
        printf("%d is eating...\n", id);
        sleep(5000);
        printf("%d burped\n", id);
        rightFork->usedBy = -1;
        leftFork->usedBy = -1;
        sys_post_semaphore(rightFork->fork);
        printf("%d left\n", id);
    }
    return 0;
}

void printTable(){
    for(int i = 0; i<currentQty; i++){
        char s[12]="Filosofo 00";
        itoa(forks[i].usedBy, s+9, 10);
        printf("Cubierto %d: USADO POR %s\n", i, (forks[i].usedBy == -1)?"NADIE":s);
        printf("Filosofo %d: %s\n", phylosIds[i], (forks[i].usedBy == phylosIds[i])?((forks[(i+1)%currentQty].usedBy == phylosIds[i])?"EATING":"WAITING FORK"):"THINKING");
    }
}
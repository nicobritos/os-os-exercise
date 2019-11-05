//This is a personal academic project. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "include/phylo.h"
#include "include/newSyscalls.h"
#include "include/stdlib.h"
#include "include/process.h"
#include "include/stdio.h"
#include "include/unistd.h"
#include "include/defines.h"

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
    printf("\nPresione:\n\tE para salir\n\tA para agregar filosofo\n\tR para remover filosofo\n\tO cualquier otra tecla para imprimir el estado de la mesa\n");
    uint64_t initQty = (uint64_t)argv[0];
    if(initQty > MAX_PHYLOS)
        return -1;
    for (int i = 0; i < initQty; i++){
        createPhylo();
    }
    char c[3];
    scanf(c, 2, '\n');
    while(1){
        switch (c[0]){
            case 'e': case 'E':
                for(int i = 0; i< currentQty; i++){
                    killProcess(phylosPids[i]);
                }
                printf("\nBye bye\n");
                return 0;
            case 'r': case 'R':
                removePhylo();
                printf("Filosofo removido\n");
                break;
            case 'a': case 'A':
                addPhylo();
                printf("Filosofo agregado\n");
                break;
            default:
                printTable();
        }
        scanf(c, 2, '\n');
    }
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
    argvs[phylosIds[currentQty]] = malloc(3 * sizeof(*(argvs[phylosIds[currentQty]])));
    if(argvs[phylosIds[currentQty]] == NULL)
        return;
    argvs[phylosIds[currentQty]][0] = (void *)&(phylosIds[currentQty]); // puntero al id
    argvs[phylosIds[currentQty]][1] = (void *)&(forks[currentQty]); // puntero al fork de la derecha
    argvs[phylosIds[currentQty]][2] = (void *)&(forks[0]); // puntero al fork de la izquierda
    phylosPids[currentQty] = sys_newProcess(name, phylo, 3, (char **)argvs[phylosIds[currentQty]], S_M_BACKGROUND);

    if(currentQty != 0){
        char post1, post2;
        post1 = post2 = 0;

        if((forks[currentQty-1].usedBy == currentQty -1)){
            printf("\nEsperando que el filosofo %d suelte el cubierto izquierdo para agregar uno nuevo\n", phylosIds[currentQty-1]);
            sys_wait_semaphore(forks[currentQty-1].fork);
            post1 = 1;
        }
        if(forks[0].usedBy == currentQty - 1){
            printf("\nEsperando que el filosofo %d suelte el cubierto izquierdo para agregar uno nuevo\n", phylosIds[currentQty-1]);
            sys_wait_semaphore(forks[0].fork);
            post2 = 1;
        }
        sys_freeProcess(phylosPids[currentQty - 1]);
        name[6] = (currentQty-1)/10 + '0';
        name[7] = (currentQty-1) % 10 + '0';
        phylosIds[currentQty-1] = currentQty -1;
        free(argvs[phylosIds[currentQty-1]]);
        argvs[phylosIds[currentQty-1]] = malloc(3 * sizeof(*(argvs[phylosIds[currentQty-1]])));
        argvs[phylosIds[currentQty-1]][0] = &(phylosIds[currentQty-1]);
        argvs[phylosIds[currentQty-1]][1] = &(forks[currentQty-1]);
        argvs[phylosIds[currentQty-1]][2] = &(forks[currentQty]);
        phylosPids[currentQty - 1] = sys_newProcess(name, phylo, 3, (char **)argvs[phylosIds[currentQty-1]], S_M_BACKGROUND);
        if(post1)
            sys_post_semaphore(forks[currentQty-1].fork);
        if(post2)
            sys_post_semaphore(forks[0].fork);
    }
    currentQty++;
}

void removePhylo(){
    if(currentQty != 0){
        char post1, post2;
        post1 = post2 = 0;

        if((forks[currentQty-1].usedBy == currentQty -1)){
            printf("Esperando que el filosofo %d suelte el cubierto derecho para removerlo\n", phylosIds[currentQty-1]);
            sys_wait_semaphore(forks[currentQty-1].fork);
            post1 = 1;
        }
        if(forks[0].usedBy == currentQty - 1){
            printf("Esperando que el filosofo %d suelte el cubierto izquierdo para removerlo\n", phylosIds[currentQty-1]);
            sys_wait_semaphore(forks[0].fork);
            post2 = 1;
        }
        sys_freeProcess(phylosPids[currentQty - 1]);
        free(argvs[phylosIds[currentQty-1]]);
        if(post1)
            sys_post_semaphore(forks[currentQty-1].fork);
        if(post2)
            sys_post_semaphore(forks[0].fork);
    }
}

int phylo(int argc, char * argv[]){
    if(argc != 3)
        return 1;
    int id = *((int *)(argv[0]));
    t_fork * rightFork = (t_fork *)argv[1];
    t_fork * leftFork = (t_fork *)argv[2];
    free(argv);
    while(1){
        sleep(5000);
        sys_wait_semaphore(rightFork->fork);
        rightFork->usedBy = id;
        sys_wait_semaphore(leftFork->fork);
        leftFork->usedBy = id;
        sleep(5000);
        rightFork->usedBy = -1;
        leftFork->usedBy = -1;
        sys_post_semaphore(rightFork->fork);
        sys_post_semaphore(leftFork->fork);
    }
    return 0;
}

void printTable(){
    for(int i = 0; i<currentQty; i++){
        char s[12]="Filosofo 00";
        itoa(forks[i].usedBy, s+9, 10);
        printf("\nCubierto %d: USADO POR %s\n", i, (forks[i].usedBy == -1)?"NADIE":s);
        printf("Filosofo %d: %s\n", phylosIds[i], (forks[i].usedBy == phylosIds[i])?((forks[(i+1)%currentQty].usedBy == phylosIds[i])?"EATING":"WAITING FORK"):"THINKING");
    }
}
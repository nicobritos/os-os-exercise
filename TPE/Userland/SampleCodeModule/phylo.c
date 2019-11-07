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
    currentQty = 0;
    uint64_t initQty = (uint64_t)argv[0];
    free(argv);
    if(initQty > MAX_PHYLOS || initQty < 3){
        printf("Tiene que haber entre 3 y 100 filosofos");
        return -1;
    }
    printf("Bienvenido al problema de los filosofos comensales, presione ENTER para continuar\n");
    while(getchar() != '\n');
    printf("Presione:\n\tH para obtener ayuda\n\tE para salir\n\tA para agregar filosofo\n\tR para remover filosofo\n\tCualquier otra tecla para imprimir el estado de la mesa\n");
    for (int i = 0; i < initQty; i++){
        createPhylo();
    }

    while(1){
        switch (getchar()){
            case 'h': case 'H':
                printf("Presione:\n\tH para obtener ayuda\n\tE para salir\n\tA para agregar filosofo\n\tR para remover filosofo\n\tCualquier otra tecla para imprimir el estado de la mesa\n");
                break;
            case 'e': case 'E':
                printf("Saliendo\n");
                printf("Guardando los cubiertos...\n");
                for(int i = 0; i< currentQty; i++){
                    sys_closeSem(forks[i].fork);
                }
                printf("Listo\n");
                printf("Echando a los filosofos de la cocina...\n");
                for(int i = 0; i< currentQty; i++){
                    killProcess(phylosPids[i]);
                    free(argvs[phylosIds[i]]);
                }
                printf("Listo\n");
                printf("\nBye bye\n");
                return 0;
            case 'r': case 'R':
                removePhylo();
                break;
            case 'a': case 'A':
                addPhylo();
                break;
            default:
                printTable();
        }
    }
}

void addPhylo(){
    if(currentQty >= MAX_PHYLOS){
        printf("No se pueden agregar mas filosofos (maximo 100)\n");
    }
    else{
        createPhylo();
    }
}

void createPhylo(){
    char semName[8] = "Fork-00";
    semName[5] = currentQty/10 + '0';
    semName[6] = currentQty % 10 + '0';
    forks[currentQty].fork = sys_createSem(semName);
    sys_post_semaphore(forks[currentQty].fork); // para marcar que empieza libre
    forks[currentQty].usedBy = -1;
    printf("Poniendo un cubierto mas\n");

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
    printf("Filosofo agregado\n");
}

void removePhylo(){
    if(currentQty >= 4){
        char post2 = 0;

        if((forks[currentQty-1].usedBy == currentQty -1)){
            printf("Esperando que el filosofo %d suelte el cubierto derecho para removerlo\n", phylosIds[currentQty-1]);
            sys_wait_semaphore(forks[currentQty-1].fork);
        } else if ((forks[currentQty-1].usedBy == currentQty - 2)){
            printf("Esperando que el filosofo %d suelte el cubierto derecho para remover el cubierto\n", phylosIds[currentQty-2]);
            sys_wait_semaphore(forks[currentQty-1].fork);
        }
        if(forks[0].usedBy == currentQty - 1){
            printf("Esperando que el filosofo %d suelte el cubierto izquierdo para removerlo\n", phylosIds[currentQty-1]);
            sys_wait_semaphore(forks[0].fork);
            post2 = 1;
        }
        printf("Rearmando la mesa\n");
        if(forks[currentQty - 2].usedBy == currentQty - 2){
            printf("Esperando que el filosofo %d suelte su cubierto derecho para reubicarlo y darle otro cubierto\n", phylosIds[currentQty-2]);
            sys_wait_semaphore(forks[currentQty-2].fork);
        }
        sys_freeProcess(phylosPids[currentQty - 2]);
        char name[9] = "Phylo-00";
        name[6] = (currentQty-2)/10 + '0';
        name[7] = (currentQty-2) % 10 + '0';
        phylosIds[currentQty-2] = currentQty -2;
        free(argvs[phylosIds[currentQty-2]]);
        argvs[phylosIds[currentQty-2]] = malloc(3 * sizeof(*(argvs[phylosIds[currentQty-2]])));
        argvs[phylosIds[currentQty-2]][0] = &(phylosIds[currentQty-2]);
        argvs[phylosIds[currentQty-2]][1] = &(forks[currentQty-2]);
        argvs[phylosIds[currentQty-2]][2] = &(forks[currentQty-1]);
        phylosPids[currentQty - 2] = sys_newProcess(name, phylo, 3, (char **)argvs[phylosIds[currentQty-2]], S_M_BACKGROUND);
        sys_freeProcess(phylosPids[currentQty - 1]);
        free(argvs[phylosIds[currentQty-1]]);
        sys_post_semaphore(forks[currentQty-2].fork);
        sys_closeSem(forks[currentQty-1].fork);
        if(post2)
            sys_post_semaphore(forks[0].fork);
        currentQty--;
        printf("Filosofo removido\n");
    }
    else{
        printf("No se pueden remover mas filosofos (minimo 3)\n");
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
    printf("\n-----------------------------------------------------------\n");
    for(int i = 0; i<currentQty; i++){
        char s[12]="Filosofo 00";
        itoa(forks[i].usedBy, s+9, 10);
        printf("Cubierto %d: USADO POR %s\n", i, (forks[i].usedBy == -1)?"NADIE":s);
        printf("Filosofo %d: %s\n", phylosIds[i], (forks[i].usedBy == phylosIds[i])?((forks[(i+1)%currentQty].usedBy == phylosIds[i])?"EATING":"WAITING FORK"):"THINKING");
    }
    printf("-----------------------------------------------------------\n");
}
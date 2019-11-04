#include "include/phylo.h"
#include "include/newSyscalls.h"
#include "include/stdlib.h"
#include "include/time.h"
#include "include/process.h"
#include "include/stdio.h"

#define MAX_PHYLOS 100

void addPhylo();
void createPhylo();
void removePhylo();
int phylo(int argc, char * argv[]);
void printTable();

typedef enum {EATING, WAITING_FORK, THINKING} phylo_state;

typedef struct
{
    void * fork;
    pid_t usedBy;
}t_fork;


t_fork forks[MAX_PHYLOS];
int currentQty = 0;

pid_t phylosPids[MAX_PHYLOS];
int phylosIds[MAX_PHYLOS];

int phyloProblem(int initQty){
    if(initQty > MAX_PHYLOS)
        return -1;
    for (int i = 0; i < initQty; i++){
        createPhylo();
    }
    char c;
    while(((c=getchar()) != 'e') || (c != 'E')){
        switch (c){
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
    name[7] = currentQty/10 + '0';
    name[8] = currentQty % 10 + '0';
    phylosIds[currentQty] = currentQty;
    char * argv[3] = {&(phylosIds[currentQty]), &(forks[currentQty]), &(forks[(currentQty+1)%currentQty])};
    phylosPids[currentQty] = sys_newProcess(name, phylo, 3, argv, S_M_BACKGROUND);

    if(currentQty != 0){
        char post1, post2;
        post1 = post2 = 0;

        if((forks[currentQty-1].usedBy == currentQty -1)){
            wait(forks[currentQty-1].fork);
            post1 = 1;
        }
        if(forks[0].usedBy == currentQty - 1){
            wait(forks[0].fork);
            post2 = 1;
        }
        sys_freeProcess(phylosPids[currentQty - 1]);
        name[7] = (currentQty-1)/10 + '0';
        name[8] = (currentQty-1) % 10 + '0';
        phylosIds[currentQty-1] = currentQty -1;
        char * argv[3] = {&(phylosIds[currentQty-1]), &(forks[currentQty-1]), &(forks[(currentQty)%currentQty])};
        phylosPids[currentQty] = sys_newProcess(name, phylo, 3, argv, S_M_BACKGROUND);
        if(post1)
            sys_post_semaphore(forks[currentQty-1].fork);
        if(post2)
            sys_post_semaphore(forks[0].fork);
    }
    currentQty++;
}

void removePhylo(){
    currentQty--;
    char semName[8] = "Fork-00";
    semName[5] = currentQty/10 + '0';
    semName[6] = currentQty % 10 + '0';
    sys_closeSem(forks[currentQty].fork);
    if(forks[0].usedBy == phylosIds[currentQty]){
        forks[0].usedBy = -1;
        sys_freeProcess(phylosPids[currentQty]);
        sys_post_semaphore(forks[0].fork);
    }
    else{
        sys_freeProcess(phylosPids[currentQty]);
    }
}

int phylo(int argc, char * argv[]){
    if(argc != 3)
        return 1;
    int id = *(argv[0]);
    t_fork * rightFork = (t_fork *)argv[1];
    t_fork * leftFork = (t_fork *)argv[2];
    while(1){
        phylo_state state = THINKING;
        sleep(5);
        state = WAITING_FORK;
        wait(rightFork->fork);
        rightFork->usedBy = id;
        wait(leftFork->fork);
        leftFork->usedBy = id;
        state = EATING;
        sleep(5);
        rightFork->usedBy = -1;
        leftFork->usedBy = -1;
        sys_post_semaphore(rightFork->fork);
    }
    return 0;
}

void printTable(){
    for(int i = 0; i<currentQty; i++){
        printf("Filosofo %d: %s\n", phylosIds[i], (forks[i].usedBy == phylosIds[i])?((forks[(i+1)%currentQty].usedBy == phylosIds[i])?"EATING":"WAITING FORK"):"THINKING");
        char s[12]="Filosofo 00";
        itoa(forks[i].usedBy, s+9, 10);
        printf("Cubierto %d: USADO POR %s\n", i, (forks[i].usedBy == -1)?"NADIE":s);
    }
}
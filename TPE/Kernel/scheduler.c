#include <scheduler.h>

typedef struct nodeADT *node;

typedef struct node {
    process_t process;
    uint64_t time_spent;
    nodeADT previous;
    nodeADT next;
} node;

static node currentProcess;
static node firstProcess;
static node lastProcess;
static uint64_t processQuantity;

void init_scheduler() {
	currentProcess = firstProcess = lastProcess = NULL;
	processQuantity = 0;
}

void run_scheduler() {

}




// Scheduler
// •	Init
// •	Run process
// •	Kill process
// •	Run scheduler
// •	set process state
// •	Get current processes
// •	Get current process
// •	Threads?
// Funcionamiento:
// 1.	Timer tick llama a scheduler (RR). Si ticks >= Quantum entonces desalojamos (backup con dispatcher) y agarramos otro proceso READY. Si están todos bloqueados ni idea. Lo marcamos como RUNNING y llamamos al dispatcher para que lo aloje
// 2.	Run process lo manda a la lista. Si vacia, dispatcher
// 3.	Kill process lo saca de la lista. Si estaba corriendo, dispatcher y se ejecuta siguiente (si es que hay).
// 4.	Set process state: cambia el estado del proceso. Si corria => dispatcher

void run_process(process_t process);
void kill_process(process_t process);
void lock_process(process_t process);
void unlock_process(process_t process);
void get_processes();
void get_current_process();




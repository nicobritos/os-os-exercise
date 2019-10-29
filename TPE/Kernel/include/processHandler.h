#ifndef PROCESS_HANDLER_H_
#define PROCESS_HANDLER_H_
#include <inttypes.h>
#include "process.h"

t_process * createProcess(uint64_t pid, char * name, int(* foo)(int argc, char** argv));

/* Ejecuta la foo que se paso en el createProcess de ese proceso */
int exec(t_process * process);

/* Libera la memoria ocupada por el proceso */
int free(t_process * process);

#endif
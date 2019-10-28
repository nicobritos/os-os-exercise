#ifndef PROCESS_H
#define PROCESS_H

#define PROC_SIZE 4096
#define MAX_PROC 20
#define SYSTEM_PID 0

typedef int64_t pid_t;

typedef enum {RUNNING, READY, WAITING, DEAD, LOCKED, INVALID} t_state;

#endif

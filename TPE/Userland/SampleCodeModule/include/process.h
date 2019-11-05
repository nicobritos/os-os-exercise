#ifndef PROCESS_H
#define PROCESS_H

#include "stdint.h"

#define SYSTEM_PID 0
#define MAX_PROC 20

typedef int64_t pid_t;

typedef enum {S_P_HIGH = 0, S_P_LOW, S_P_INVALID} t_priority;
typedef enum {S_M_FOREGROUND = 0, S_M_BACKGROUND, S_M_INVALID} t_mode;
typedef enum {P_RUNNING = 0, P_READY, P_DEAD, P_LOCKED, P_INVALID} t_state;

#endif

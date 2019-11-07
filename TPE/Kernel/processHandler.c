//This is a personal academic project. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "processHandler.h"
#include "memManager.h"

#define STARTING_PID (SYSTEM_PID + 1)

static t_process *processes;

void _killProcessSyscallKernel(int returnValue);
void _reboot();

void initializeProcessHandler() {
    processes = pmalloc(sizeof(*processes) * MAX_PROC, SYSTEM_PID);
    for (uint64_t i = 0; i < MAX_PROC; ++i) {
        processes[i] = NULL;
    }
}

t_process newProcess(char * name, int(* foo)(int argc, char** argv), int ppid, int argc, char * argv[], t_priority priority, t_mode mode, t_stack stackFrame) {
    char finished = 0;
    pid_t i;
    
    for (i = STARTING_PID; i < MAX_PROC && !finished; i++) {
        if (processes[i] == NULL) {
            finished = 1;
        }
    }
    if (!finished) return NULL;
    i--;

    t_process newProcess = createProcess(name, processWrapper, i, ppid, argc, argv, (void *) foo);
    if (newProcess == NULL) return NULL;
    processes[i] = newProcess;
    addProcess(newProcess, priority, mode, stackFrame);
    
    return newProcess;
}

int8_t execveProcessHandler(t_process process, int argc, char * argv[], int(* startingPoint)(int argc, char** argv)) {
    return execve(process, processWrapper, argc, argv, startingPoint);
}

// This code is NOT executed inside interrupt
// So I need to enter one to get the current stackFrame
int processWrapper(int argc, char * argv[], int(* startingPoint)(int argc, char** argv)) {
    int retValue = startingPoint(argc, argv);
    _killProcessSyscallKernel(retValue);
    while (1);
    return retValue;
}

int8_t killProcessHandler(pid_t pid, t_stack currentProcessStackFrame) {
    int8_t returnValue = 0;

    if (pid != SYSTEM_PID && pid < MAX_PROC) {
        t_process process = processes[pid];
        processes[pid] = 0;
        returnValue = killProcess(pid, currentProcessStackFrame);
        freeProcess(process);
    }

    return returnValue;
}

t_process getProcess(pid_t pid) {
    if (pid >= MAX_PROC || processes[pid] == 0) return NULL;
    return processes[pid];
}

t_state getProcessStatePid(pid_t pid) {
    return getProcessState(getProcess(pid));
}


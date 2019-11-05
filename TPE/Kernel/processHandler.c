//This is a personal academic project. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "processHandler.h"
#include "memManager.h"

#define STARTING_PID (SYSTEM_PID + 1)

static t_process processes[MAX_PROC] = {0};

void _killProcessSyscallKernel();
void _reboot();

t_process newProcess(char * name, int(* foo)(int argc, char** argv), int ppid, int argc, char * argv[], t_priority priority, t_mode mode) {
    char finished = 0;
    pid_t i;
    for (i = STARTING_PID; i < MAX_PROC && !finished; i++) {
        if (processes[i] == 0) {
            finished = 1;
            break;
        }
    }
    if (!finished) return NULL;

    t_process newProcess = createProcess(name, processWrapper, i, ppid, argc, argv, (void *) foo);
    if (newProcess == NULL) {
        return NULL;
    }
    processes[i] = newProcess;

    addProcess(newProcess, priority, mode);
    return newProcess;
}

// This code is NOT executed inside interrupt
// So I need to enter one to get the stackFrame
int processWrapper(int argc, char * argv[], int(* startingPoint)(int argc, char** argv)) {
    int retValue = startingPoint(argc, argv);
    // TODO: add return value if process(ses) are waiting for it to end
    _killProcessSyscallKernel();
    while (1);
    return retValue;
}

void killProcessHandler(pid_t pid, t_stack currentProcessStackFrame) {
    if (pid != SYSTEM_PID && pid < MAX_PROC) {
        t_process process = processes[pid];
        processes[pid] = 0;
        killProcess(pid, currentProcessStackFrame);
        freeProcess(process);
    } else if (pid == SYSTEM_PID) {
        updateProcessStackRegister(currentProcessStackFrame, REGISTER_RIP, (uint64_t) _reboot);
    }
}

t_process duplicateProcessHandler(t_process source) {
    char finished = 0;
    pid_t i;
    for (i = 0; i < MAX_PROC && !finished; i++) {
        if (processes[i] == 0) {
            finished = 1;
        }
    }
    if (!finished) return NULL;

    t_process process = duplicateProcess(source, i);
    processes[i] = process;
    addProcess(process, getCurrentProcessState(), getCurrentProcessMode());

    return process;
}

t_process getProcess(pid_t pid) {
    if (pid >= MAX_PROC || processes[pid] == 0) return NULL;
    return processes[pid];
}

t_state getProcessStatePid(pid_t pid) {
    return getProcessState(getProcess(pid));
}


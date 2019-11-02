#include "processHandler.h"
#include "memManager.h"

static char pids[MAX_PROC] = {0};

t_process newProcess(char * name, int(* foo)(int argc, char** argv), int ppid, int argc, char * argv[], t_priority priority, t_mode mode) {
    char finished = 0;
    pid_t i;
    for (i = 0; i < MAX_PROC && !finished; i++) {
        if (pids[i] == 0) {
            pids[i] = 1;
            finished = 1;
        }
    }
    if (!finished) return NULL;

    t_process newProcess = createProcess(name, processWrapper, i, ppid, argc, argv, (void *) foo);
    if (newProcess == NULL) {
        return NULL;
    }

    addProcess(newProcess, priority, mode);
    return newProcess;
}

int processWrapper(int argc, char * argv[], int(* startingPoint)(int argc, char** argv)) {
    int retValue = startingPoint(argc, argv);
    pushcli();
    killProcess(getProcessPid(getCurrentProcess()));
    pushsti();
    while (1);
    return retValue;
}

void freeProcessHandler(t_process process) {
    if (getProcessPid(process) != SYSTEM_PID) {
        pids[(getProcessPid(process)) - 1] = 0;
        freeProcess(process);
    }
}

t_process duplicateProcessHandler(t_process source) {
    char finished = 0;
    pid_t i;
    for (i = 0; i < MAX_PROC && !finished; i++) {
        if (pids[i] == 0) {
            pids[i] = 1;
            finished = 1;
        }
    }
    if (!finished) return NULL;

    t_process process = duplicateProcess(source, i);
    // addProcess(process, getProcess()getCurrentProcessState(), getCurrentProcessMode());

    return process;
}


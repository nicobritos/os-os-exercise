#ifndef UNISTD_H_
#define UNISTD_H_

void * newProcess(char * name, int(* foo)(int argc, char** argv), int ppid, int argc, char * argv[], void * returnPosition);
void freeProcess(void * process);
int getPid(void * process);
int execute(void * process);

#endif

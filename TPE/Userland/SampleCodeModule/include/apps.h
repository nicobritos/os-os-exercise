#ifndef APPS_H_
#define APPS_H_
#include <stdint.h>

int help(int argc, char **argv);
int kill(int argc, char **argv);
int nice(int argc, char **argv);
int block(int argc, char **argv);
int mem(int argc, char **argv);
int ps(int argc, char **argv);
int loop(int argc, char **argv);
int cat(int argc, char **argv);
int wc(int argc, char **argv);
int filter(int argc, char **argv);
int clear(int argc, char** argv);
int pipe(int argc, char** argv);
int sem(int argc, char** argv);


#endif /* APPS_H_ */

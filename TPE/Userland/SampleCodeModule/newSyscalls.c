#include "includes/newSyscalls.h"

int64_t _systemCall();

int sys_read( int fileDescriptor, char * buff, int length)
{
    return _systemCall(3, fileDescriptor, (void *)buff, length,0,0,0);
}

int sys_write(int fileDescriptor, char * buff, int length)
{
    return _systemCall(4, fileDescriptor, (void *)buff, length, 0, 0,0);
}

int sys_clear()
{
    return _systemCall(5,0,0,0,0,0,0);
}

int sys_draw( int x, int y, unsigned char red, unsigned char green, unsigned char blue)
{
    return _systemCall(6, x, y, (int)red, (int)green, (int)blue,0);
}

int * sys_time(int * dest){
    return (int *)_systemCall(7,dest,0,0,0,0,0);
}

int sys_getPid(void * process)
{
    return _systemCall(8,process,0,0,0,0,0);
}

void * sys_newProcess(char * name, int(* foo)(int argc, char** argv), int ppid, int argc, char * argv[], void * returnPosition)
{
    return (void *)_systemCall(9, name,foo,ppid,argc,argv,returnPosition);
}

void sys_freeProcess(void * process)
{
    _systemCall(10, process,0,0,0,0,0);
}

void sys_free(void * address, uint64_t size)
{
    _systemCall(11,address,size,0,0,0,0);    
}

int sys_ticks(int * ticks)
{
    return _systemCall(12,ticks,0,0,0,0,0);
}

int sys_ticksPerSecond(int * ticks)
{
    return _systemCall(13,ticks,0,0,0,0,0);
}

uint64_t sys_usedMem(void)
{
    return (uint64_t)_systemCall(14,0,0,0,0,0,0);
}

uint64_t sys_freeMem(void)
{
    return (uint64_t)_systemCall(15,0,0,0,0,0,0);
}

void * sys_malloc(uint64_t size, uint64_t pid)
{
    return (void *)_systemCall(16,size,pid,0,0,0,0);
}

int sys_readPipe(void * pipe, char *buffer, uint64_t size){
    return _systemCall(17, pipe, buffer, size, 0,0,0);
}

int sys_writePipe(void * pipe, char *buffer, uint64_t size){
    return _systemCall(18, pipe, buffer, size, 0,0,0);
}

void * sys_createSem(char *name){
    return (void *)_systemCall(19, name, 0,0,0,0,0);
}

void * sys_openSem(char *name){
    return (void *)_systemCall(20, name, 0,0,0,0,0);
}

void sys_closeSem(void * sem){
    _systemCall(21, sem, 0,0,0,0,0);
}

void sys_wait(void * sem, uint64_t pid){
    _systemCall(22, sem, pid, 0,0,0,0);
}

void sys_post(void * sem){
    _systemCall(23, sem, 0,0,0,0,0);
}

void sys_printSems(){
    _systemCall(24, 0,0,0,0,0,0);
}
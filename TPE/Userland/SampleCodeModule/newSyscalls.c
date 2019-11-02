#include "includes/newSyscalls.h"

int _systemCall();

int sys_read( int fileDescriptor, void * buff, int length)
{
    return _systemCall(3, fileDescriptor, buff, length,0,0,0);
}

int sys_write(int fileDescriptor, void * buff, int length)
{
    return _systemCall(4, fileDescriptor, buff, length, 0, 0,0);
}

int sys_clear()
{
    return _systemCall(5,0,0,0,0,0,0);
}

int sys_draw( int x, int y, int red, int green, int blue)
{
    return _systemCall(6, x, y, red, green, blue,0);
}

int * sys_time(){
    return _systemCall(7,0,0,0,0,0,0);
}

int sys_exec(void * process)
{
    return _systemCall(8,process,0,0,0,0,0);
}

int sys_getPid(void * process)
{
    return _systemCall(9,process,0,0,0,0,0);
}

void * sys_newProcess(char * name, int(* foo)(int argc, char** argv), int ppid, int argc, char * argv[], void * returnPosition)
{
    return _systemCall(10,name,foo,ppid,argc,argv,returnPosition);
}

void sys_freeProcess(void * process)
{
    return _systemCall(11,process,0,0,0,0,0);
}

void sys_free(void * address, uint64_t size)
{
    return _systemCall(12,address,size,0,0,0,0);    
}

int sys_ticks(int * ticks)
{
    return _systemCall(13,ticks,0,0,0,0,0);
}

int sys_ticksPerSecond(int * ticks)
{
    return _systemCall(14,ticks,0,0,0,0,0);
}

uint64_t sys_usedMem(void)
{
    return _systemCall(15,0,0,0,0,0,0);
}

uint64_t sys_freeMem(void)
{
    return _systemCall(16,0,0,0,0,0,0);
}

void * sys_malloc(uint64_t size, uint64_t pid)
{
    return _systemCall(17,size,pid,0,0,0,0);
}









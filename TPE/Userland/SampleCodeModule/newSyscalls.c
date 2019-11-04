#include "newSyscalls.h"

uint64_t _systemCall();

uint64_t sys_read( int fileDescriptor, void * buff, int length)
{
    return _systemCall(__SYSTEM_CALL_READ, fileDescriptor, buff, length);
}

uint64_t sys_write(int fileDescriptor, void * buff, int length)
{
    return _systemCall(__SYSTEM_CALL_WRITE, fileDescriptor, buff, length);
}

uint64_t sys_clear()
{
    return _systemCall(__SYSTEM_CALL_CLEAR);
}

uint64_t sys_draw( int x, int y, int red, int green, int blue)
{
    return _systemCall(__SYSTEM_CALL_DRAW, x, y, red, green, blue);
}

uint64_t *sys_time(){
    return (uint64_t*)_systemCall(__SYSTEM_CALL_TIME);
}

pid_t sys_getPid()
{
    return (pid_t)_systemCall(__SYSTEM_CALL_GET_PID);
}

pid_t sys_newProcess(char * name, int(* foo)(int argc, char** argv), int argc, char * argv[], t_mode mode)
{
    return (pid_t)_systemCall(__SYSTEM_CALL_NEW_PROCESS,name,foo,argc,argv, mode);
}

void sys_freeProcess(pid_t pid)
{
    _systemCall(__SYSTEM_CALL_FREE_PROCESS, pid);
}

void sys_free(void * address)
{
    _systemCall(__SYSTEM_CALL_FREE,address);    
}

uint64_t sys_ticks(int * ticks)
{
    return _systemCall(__SYSTEM_CALL_TICKS,ticks);
}

uint64_t sys_ticksPerSecond(int * ticks)
{
    return _systemCall(__SYSTEM_CALL_TICKS_PER_SECOND,ticks);
}

uint64_t sys_usedMem()
{
    return _systemCall(__SYSTEM_CALL_USED_MEM);
}

uint64_t sys_freeMem()
{
    return _systemCall(__SYSTEM_CALL_FREE_MEM);
}

void *sys_malloc(uint64_t size)
{
    return (void*)_systemCall(__SYSTEM_CALL_MALLOC,size);
}

void sys_yield() {
    _systemCall(__SYSTEM_CALL_YIELD);
}

t_mode sys_get_process_mode(pid_t pid) {
    return (t_mode) _systemCall(__SYSTEM_CALL_GET_PROCESS_MODE, pid);
}

void sys_set_process_mode(pid_t pid, t_mode mode) {
    _systemCall(__SYSTEM_CALL_SET_PROCESS_MODE, pid, mode);
}

t_priority sys_get_process_priority(pid_t pid) {
    return (t_priority) _systemCall(__SYSTEM_CALL_GET_PROCESS_PRIORITY, pid);
}

void sys_set_process_priority(pid_t pid, t_priority priority) {
    _systemCall(__SYSTEM_CALL_SET_PROCESS_PRIORITY, pid, priority);
}

t_state sys_get_process_state(pid_t pid) {
    return (t_state) _systemCall(__SYSTEM_CALL_GET_PROCESS_STATE, pid);
}

int sys_readPipe(void * pipe, char *buffer, uint64_t size){
    return _systemCall(__SYSTEM_CALL_READ_PIPE, pipe, buffer, size);
}

int sys_writePipe(void * pipe, char *buffer, uint64_t size){
    return _systemCall(__SYSTEM_CALL_WRITE_PIPE, pipe, buffer, size);
}

void * sys_createSem(char *name){
    return (void *)_systemCall(__SYSTEM_CALL_CREATE_SEM, name);
}

void * sys_openSem(char *name){
    return (void *)_systemCall(__SYSTEM_CALL_OPEN_SEM, name);
}

void sys_closeSem(void * sem){
    _systemCall(__SYSTEM_CALL_CLOSE_SEM, sem);
}

void sys_wait_semaphore(void * sem, uint64_t pid){
    _systemCall(__SYSTEM_CALL_WAIT, sem, pid);
}

void sys_post_semaphore(void * sem){
    _systemCall(__SYSTEM_CALL_POST, sem);
}

void sys_printSems(){
    _systemCall(__SYSTEM_CALL_PRINT_SEMS);
}

int sys_wait_pid(pid_t pid) {
    return _systemCall(__SYSTEM_CALL_WAIT_PID, pid);
}

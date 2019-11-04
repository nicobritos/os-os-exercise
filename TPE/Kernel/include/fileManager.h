#ifndef __FILE_MANAGER_H
#define __FILE_MANAGER_H

uint64_t readFile(uint64_t fd, char *buffer, uint64_t size);
uint64_t writeFile(uint64_t fd, char *buffer, uint64_t size);

#endif

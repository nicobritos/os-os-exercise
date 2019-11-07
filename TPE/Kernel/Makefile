include Makefile.inc

KERNEL=kernel.bin
SOURCES=$(wildcard *.c)
SOURCES_ASM=$(wildcard asm/*.asm)
OBJECTS=$(SOURCES:.c=.o)
OBJECTS_ASM=$(SOURCES_ASM:.asm=.o)
LOADERSRC=loader.asm
MODO_H="./include/modoMemManager.h"

LOADEROBJECT=$(LOADERSRC:.asm=.o)
STATICLIBS=

all: buddy # por default hace buddy

buddy: buddyAux $(KERNEL)

buddyAux:
	sed -i '1d' $(MODO_H)
	echo '#define MODO_BUDDY' >> $(MODO_H)

freeList: freeListAux $(KERNEL)

freeListAux:
	sed -i '1d' $(MODO_H)
	echo '#define MODO_FREE_LIST' >> $(MODO_H)

$(KERNEL): $(LOADEROBJECT) $(OBJECTS) $(STATICLIBS) $(OBJECTS_ASM)
	$(LD) $(LDFLAGS) -T kernel.ld -o $(KERNEL) $(LOADEROBJECT) $(OBJECTS) $(OBJECTS_ASM) $(STATICLIBS)

%.o: %.c
	$(GCC) $(GCCFLAGS) -I./include -c $< -o $@

%.o : %.asm
	$(ASM) $(ASMFLAGS) $< -o $@

$(LOADEROBJECT):
	$(ASM) $(ASMFLAGS) $(LOADERSRC) -o $(LOADEROBJECT)

clean:
	rm -rf asm/*.o *.o *.bin

.PHONY: all clean

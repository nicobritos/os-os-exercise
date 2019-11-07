
all:  bootloader userland kernel

bootloader:
	cd Bootloader; make all

buddy: bootloader userland image
	cd Kernel; make buddy
	cd Image; make all

freeList: bootloader userland image
	cd Kernel; make freeList
	cd Image; make all

kernel:
	cd Kernel; make all
	cd Image; make all

userland:
	cd Userland; make all

clean:
	cd Bootloader; make clean
	cd Image; make clean
	cd Kernel; make clean
	cd Userland; make clean

.PHONY: bootloader image collections kernel userland all clean

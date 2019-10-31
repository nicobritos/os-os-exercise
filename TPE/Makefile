
all:  bootloader kernel userland image

bootloader:
	cd Bootloader; make all

buddy: bootloader userland image
	cd Kernel; make buddy

freeList: bootloader userland image
	cd Kernel; make freeList

kernel:
	cd Kernel; make all

userland:
	cd Userland; make all

image: kernel bootloader userland
	cd Image; make all

clean:
	cd Bootloader; make clean
	cd Image; make clean
	cd Kernel; make clean
	cd Userland; make clean

.PHONY: bootloader image collections kernel userland all clean

CC=gcc
INCLUDES = 
LDFLAGS = -g
ifneq (${KERNELRELEASE},)

# KERNELRELEASE defined: we are being compiled as part of the Kernel
        obj-m := vga_led.o

else

# We are being compiled as a module: use the Kernel build system

	KERNEL_SOURCE := /usr/src/linux
        PWD := $(shell pwd)

default: module hello read_ram
	 rmmod vga_led.ko
	 insmod vga_led.ko

module:
	${MAKE} -C ${KERNEL_SOURCE} SUBDIRS=${PWD} modules

clean:
	${MAKE} -C ${KERNEL_SOURCE} SUBDIRS=${PWD} clean
	${RM} hello read_ram

socfpga.dtb : socfpga.dtb
	dtc -O dtb -o socfpga.dtb socfpga.dts
main: main.o packetgen.o

validator.o: validator.c 

timer.o: timer.c

.PHONY:all
packetgen.o:packetgen.c packetgen.h
        
endif 

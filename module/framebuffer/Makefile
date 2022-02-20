obj-m += framebuffer.o

test:test.c framebuffer.h
	arm-linux-gnueabihf-gcc test.c -Wall -o test -pthread

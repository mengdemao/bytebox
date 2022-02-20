obj-m += wait.o

test:test.c wait.h
	arm-linux-gnueabi-gcc test.c -Wall -o test -pthread

obj-m += rtc.o

test:test.c rtc_private.h
	arm-linux-gnueabihf-gcc test.c -Wall -o test -pthread

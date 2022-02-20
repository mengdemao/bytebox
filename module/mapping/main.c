#include <stdio.h>
#include <unistd.h>

const char banner[32] = "Hello World";

int main(int argc, char *argv[])
{
	(void)argc;
	(void)argv;

	printf("%d\n", getpid());

	while(1) {
		printf("%s\r\n", banner);
		sleep(1);
	}

	return 0;
}

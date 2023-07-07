#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

	int fd = atoi(argv[1]);

	int status = close(fd);
	printf("%d", status);

}

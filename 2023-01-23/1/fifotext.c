#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>


int main(int argc, char *argv[]) {
	
	int PATH_LEN = 80;
	char path_pipe[PATH_LEN];
	int response;
	int fd; 

	strcpy(path_pipe, argv[1]); 
	response = mkfifo(path_pipe, S_IRWXU);

	fd = open(path_pipe, O_RDONLY, NULL);
	printf("fd: %d\n", fd);
	close(fd);

	size_t BUF_LEN = 500;
	char line[BUF_LEN];
	int nread;
	while(true) {
		nread = read(fd, line, BUF_LEN);
		response = lseek(fd, nread, SEEK_CUR);

		if(nread > 0)
			printf("%s read:%d response:%d\n,", line, nread, response);

		if(nread > 0 && line[nread - 1] == '\n') {
			line[nread - 1] = '\0';
		}
		if(!strcmp(line, "FINE"))
			break;
	}
	close(fd);
}


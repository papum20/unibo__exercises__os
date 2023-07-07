#include <unistd.h>
#include <stdlib.h>
#include "fcntl.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
	
	int FILE_LEN;
	char *path = argv[argc - 2];
	char *path_out = argv[argc - 1];
	char *optstring = "j:";

	int fd_in, fd_out;
	int BUF_SIZE = 2048;
	int buf_size_out;
	int buf_count;
	char buf[BUF_SIZE];

	int i;

	/* arg */
	int j = 2;
	int opt;
	while((opt = getopt(argc, argv, optstring)) != -1) 
		if(opt == 'j') j = atoi(optarg);

	if(j <= 0)
		j = 2;

	/* len */
	fd_in = open(path, O_RDONLY);
	FILE_LEN = read(fd_in, buf, BUF_SIZE);
	close(fd_in);

	/* start, end */
	buf_size_out = FILE_LEN / j;
	int start = 0, end = buf_size_out;

	int cpid;
	for(i = 0; i < j - 1; i++) {
		if((cpid = fork()) != 0) {
			start = (i + 1) * buf_size_out;
			end = (i == j - 1) ? FILE_LEN : (start + buf_size_out);
			break;
		}
	}
	printf("%d %d %d, %s\n", cpid, start, end, buf);

	/* copy */
	fd_out = open(path_out, O_CREAT | O_WRONLY, S_IRWXU);
	lseek(fd_out, start, SEEK_SET);
	write(fd_out, buf + start, end - start);
	close(fd_out);

}	

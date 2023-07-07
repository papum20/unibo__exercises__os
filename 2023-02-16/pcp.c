#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
	
	int BUF_SIZE = 2048;
	char buf[BUF_SIZE];
	struct stat statbuf;
	int fd_in, fd_out;

	fd_in = open(argv[1], O_RDONLY); 
	int in_count = read(fd_in, buf, BUF_SIZE);
	close(fd_in);
	printf("%d: %s\n", in_count, buf);

	/* start, end */
	int start = 0, end = in_count / 2;

	/* write half */
	char buf2[BUF_SIZE];
	int i = 0;
	for(i = 0; i < in_count / 2; i++)
		buf2[i] = 'c';
	buf2[i] = '\0';
	fd_out = open(argv[2], O_WRONLY | O_CREAT, S_IRWXU); 
	write(fd_out, buf, in_count / 2);			

	close(fd_out);


	char _buf[BUF_SIZE]; 
	int _fd = open(argv[2], O_RDONLY);
	int _count = read(_fd, _buf, BUF_SIZE);
	close(_fd);
	printf("%d: %s, %s\n", _count, buf2, _buf);

	/* start, end */
	int cpid = fork();	
	if(cpid != 0) {
		start = end;
		end = in_count;
	}
	printf("cpid=%d, start=%d, end=%d, buf=%s\n", cpid, start, end, buf);
	/* copy */
	fd_out = open(argv[2], O_WRONLY | ((cpid == 0) ? 0 : O_APPEND) ); 
	write(fd_out, buf + start, end - start);			

	close(fd_out);
}

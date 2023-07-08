#include <sys/wait.h>
#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>



int main(int argc, char *argv[]) {

	
	if(argc < 2) {
		printf("missing argument PROGRAM");
		exit(1);
	}
	
	// if more arguments given
	/*if(argc - 1 > ARGC) {
		printf("too many arguments");
		exit(1);
	}*/

	int status;
	int pid, pid_wait;
	int child_status;



	while((pid_wait = waitpid(pid, &child_status, WUNTRACED)) == 0 || (pid = fork()) > -1) {
		/* parent */
		if(pid > 0) {
			printf("parent pid: %d, child %d\n", getpid(), pid);
			printf("parent: wait pid %d, child pid %d, child status %d, errno %d,\n", pid_wait, pid, child_status, errno);
			printf("WIFEXITED=%d,WEXITSTATUS=%d\n", WIFEXITED(child_status),WEXITSTATUS(child_status));
			usleep(1000000);
		} else {
			/* child */
			printf("child\n");
			status = execve(argv[1], argv+1, NULL);
			printf("child: status %d, err %d\n",status,errno);
			if(status == -1)
				exit(1);
			else
				exit(0);
		}
	}
	printf("parent: child pid %d, child status %d, errno %d,\n", pid, child_status, errno);
	printf("WIFEXITED=%d,WEXITSTATUS=%d\n", WIFEXITED(child_status),WEXITSTATUS(child_status));

}

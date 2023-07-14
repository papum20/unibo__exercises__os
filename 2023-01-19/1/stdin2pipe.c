#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <fcntl.h>


int ARGLEN = 200, ARGN = 20;



/* str must not end with space or newline */
int fill_args(char *args[], char *str) {
	int curr = 0, start = 0;
	char curr_sep = '\0';
	int i;

	for(i = 0; i <= strlen(str); i++) {
		if(i < strlen(str) && (str[i] == '"' || str[i] == '\'' || str[i] == '`')) {
			if(curr_sep == '\0') {
				/* open */
				curr_sep = str[i];
				start = i + 1;
			}
			else if(curr_sep == str[i]) {
				/* close */
				curr_sep = '\0';
				strncat(args[curr], str + start, i - start);
				start = i + 2;
			}
		}
		else if(i == strlen(str) || (curr_sep == '\0' && str[i] == ' ')) {
			if(i >= start) {
				strncat(args[curr], str + start, i - start);
				start = i + 1;
			}
			curr++;
		}
	}
	

	args[curr] = NULL;
	return curr + 1;
}


int main(int argc, char *argv[]) {

	int pipefd[2];
	FILE *pipef;
	int BUFSIZE = 200;
	char buf[BUFSIZE];
	int i;

	/* input */

	size_t lenfirst = 200, lenscnd = 200;
	char cmdfirst[lenfirst];
	char cmdscnd[lenscnd];
	char *p1 = cmdfirst, *p2 = cmdscnd;
	FILE *f = fopen(argv[1], "r");
	int read1 = getline(&p1, &lenfirst, f); 
	int read2 = getline(&p2, &lenscnd, f); 
	fclose(f);

	if(cmdfirst[read1 - 1] == '\n') cmdfirst[read1 - 1] = '\0';
	if(cmdscnd[read2 - 1] == '\n') cmdscnd[read2 - 1] = '\0';

	printf("cmd1: %s, cmd2: %s\n", cmdfirst, cmdscnd);

	/* get commands and args */

	char *args1[ARGN], *args2[ARGN];

	char _args1[ARGN][ARGLEN], _args2[ARGN][ARGLEN];
	for(int i = 0; i < ARGN; i++) {
		args1[i] = _args1[i];
		args2[i] = _args2[i];
		_args1[i][0] = '\0';
		_args2[i][0] = '\0';
	}

	int args1n = fill_args(args1, cmdfirst);
    int args2n = fill_args(args2, cmdscnd);	

	printf("commands: 1:%s,%s,%s, 2:%s,%s\n", args1[0], args1[1], args1[2], args2[0],args2[1]);
	printf("%d,%d\n", args1[4]==NULL,args2[3]==NULL);
	printf("lens: 1:%d, 2:%d\n", args1n, args2n);
	printf("\n\n");

	/* pipes */
	
	if(pipe(pipefd) == -1) {
		perror("pipe");
		exit(1);
	}

	int cpid = fork();
	if(cpid == -1) {
		perror("fork");
		exit(1);
	}

	if (cpid == 0) { /* child */
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[0]);
		close(pipefd[1]);
		execvp(args1[0], args1);
		fprintf(stderr, "falied to eecute '%s'\n", args1[0]);
		exit(1);
	}
	else
	{ 
    	cpid = fork();

    	if(cpid == 0)
   	 	{
    	    dup2(pipefd[0], STDIN_FILENO);
    	    close(pipefd[0]);
	        close(pipefd[1]);
        	execvp(args2[0], args2);
        	fprintf(stderr, "Failed to execute '%s'\n", args2[0]);
     	   	exit(1);
    	}
    	else
    	{
        	int status;
        	close(pipefd[0]);
        	close(pipefd[1]);
        	waitpid(cpid, &status, 0);
    	}
	}

}

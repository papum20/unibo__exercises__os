#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#define SIGLEN 8

int main(int argc, char *argv[])
{
        union sigval value;
        int pid = atoi(argv[1]);
		int i;
		char c;

      //  value.sival_int = atoi(argv[2]);
//        value.sival_ptr = (void*) strdup(argv[3]);

	for(i = 0; i < SIGLEN; i++) {
		c = argv[2][i];
		value.sival_int = c;

        if(sigqueue(pid, SIGUSR2, value) == 0) {
                printf("signal sent successfully!!\n");
        } else {
                perror("SIGSENT-ERROR:");
        }
	}
}

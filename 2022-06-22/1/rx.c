#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>


#define SIGLEN 8
char sig[SIGLEN + 1];
int i = 0;

void sighand(int signo, siginfo_t *info, void *extra)
{

//       void *ptr_val = info->si_value.sival_ptr;
       int int_val = info->si_value.sival_int;
	   sig[i] = int_val;
	   sig[i + 1] = '\0';
  //     printf("Signal: %d, value: [%d] %s\n", signo, int_val, (char*)ptr_val);
	printf("signal number: %d=%c\n", int_val, int_val);

//	printf("signal string: %s\n", sig);

	i = (i + 1) % SIGLEN;
}

int main()
{
	    struct sigaction action;

        action.sa_flags = SA_SIGINFO;
        action.sa_sigaction = &sighand;

	int pid = getpid();

	printf("my pid: %d\n", pid);


	sig[SIGLEN] = '\0';

        if (sigaction(SIGUSR2, &action, NULL) == -1) {
                perror("sigusr: sigaction");
                return 0;
        }

        printf("Signal handler installed, waiting for signal\n");

        while(1) {
			;
			if(strlen(sig) == SIGLEN) {
				printf("string: %s\n", sig);
				sig[0] = '\0';
			}
		}

        return 0;
}

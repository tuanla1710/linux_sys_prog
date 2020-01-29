#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <time.h>

time_t startTimel, startTimes, startTimep;
pid_t ret_pid;

void handler(int signo){
	printf("\nCaught signal = %d\n", signo);
	if((ret_pid = waitpid(-1, NULL, WNOHANG)) > 0) {
		printf("Terminated child PID = %d\n", ret_pid);
	} else if (errno == ECHILD){
		printf("No Child\n");
	}
}

int main(void){
	pid_t ret1, ret2;
	int i=0;
	
	signal(SIGCHLD, handler);
	switch(ret1 = fork()){
		case -1:		// fork error
			perror("fork");
			exit(1);
			break;
		case 0:						//Child
			printf("Child1 long process --- (%d)\n", getpid());
			for (startTimel = time(NULL); time(NULL) < startTimel + 10; )
					continue;
			exit(0);
			break;
		default:
			switch(ret2 = fork()){
				case -1:
						perror("fork");
						exit(1);
					break;
				case 0:
					printf("Child2 short process---(%d)\n", getpid());
					for (startTimes = time(NULL); time(NULL) < startTimes + 5; )
						continue;
					exit(0);
					break;
			}
			while(i<5){			//asking someting to kernel eats up with lots of cpu time
				printf("Parent process---(%d)\n", getpid());
				for (startTimep = time(NULL); time(NULL) < startTimep + 3; )
					// write(1, "*", 1);
					continue; 
				i++;
			}
			break;
	}
	return 0;
}

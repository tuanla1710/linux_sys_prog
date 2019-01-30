#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>


static int state = 0;

void handler(int signo){
	int ret_pid;
	int status;
	
	printf("Signal Handler starts -----\n");
		
		while(1){
			ret_pid = waitpid(-1, NULL, WNOHANG);
			if(ret_pid == 0)
				break;
			if(errno == ECHILD){
				printf("No Child\n");
				state=1;
				break;
			}
			// printf("PID returned from waitpid = %d\n", ret_pid);
			printf("\e[31mPID %d child process is dead\e[0m\n", ret_pid);
		}
		
		printf("Signal Handler ends -----\n");
}

int main(void)
{
	pid_t ret1, ret2, ret_pid;
	int i=0;
	int j=0;
	int child1=0;
	int	child2 = 0;
	int repeat1=0;
	
	signal(SIGCHLD, handler);

	switch(ret1 = fork()){
		case -1:		// fork error
			perror("fork");
			exit(1);
			break;
		case 0:						//Child
			for(i=0; i<10; i++){
				printf("\tChild1 long process --- (%d)\n", getpid());
				sleep(1);
			}
				exit(0);
			break;
		default:
			switch(ret2 = fork()){
				case -1:
						perror("fork");
						exit(1);
					break;
				case 0:
					for(i=0; i<5; i++) {
						printf("\t\tChild2 short process---(%d)\n", getpid());
						sleep(1);
					}
					exit(0);
					break;
				default: 
					while(1){
						// while((ret_pid = waitpid(-1, NULL, WNOHANG)) > 0) {
							// printf("PID returned from waitpid = %d\n", ret_pid);
						// }
						// if(errno == ECHILD){
							// printf("No Child\n");
							// break;
						// }
						// if(errno == EINTR) {
							// printf("INTR\n");
							// break;
						// }
						if(state)
							break;
						printf("Parent process ...(%d)\n", getpid());
						sleep(1);
					}
					break;
			}
		}
		return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <signal.h>

static int state = 0;

void handler(int signo){
	int ret;
	int status;
	
	printf("Signal Handler starts -----\n");
	for(;;){
		ret = waitpid(-1, &status, WNOHANG);
		if(ret == 0){
			break;
		}
		if(ret == -1 && errno == ECHILD){
			printf("No Child --\n");
			state=1;
			break;
		}
		if(ret == -1){
			perror("child waitpid");
			abort();
		}
		printf("\e[31mPID %d child process is dead\e[0m\n", ret);
		
	}
	printf("Signal Handler ends -----\n");
	
}

int main(){
	pid_t pid1, pid2, ret_pid;
	
	int i=0;
	int j=0;
	
	int child1=0;
	int child2=0;
	int repeat=0;
	
	signal(SIGCHLD, handler);
	
	switch(pid1=fork()){
		case -1:
			perror("fork");
			exit(1);
		case 0:			//child
			printf("Child1 process -- %d\n", getpid());
			while(1){
				if(child1 == 50000){
					write(1, "*", 1);
					child1 = 0;
				}
				child1++;
				repeat++;
				if(repeat == 5000000){
					break;
				}
			}
			exit(0);
		default:
			switch(pid2 = fork()){
				case -1:
					perror("fork");
					exit(1);
				case 0:
					for(i=0; i<3; i++){
						printf("\tChild2 process -- %d\n", getpid());
						usleep(50000);
					}
					exit(0);
			}	
			while(1){
				
				// if((ret_pid = waitpid(-1, NULL, WNOHANG)) >0){
					// printf("Returned PID = %d\n", ret_pid);
				// }
				// if(errno == ECHILD){
					// printf("NO child\n");
					// break;
				// }
				if(state) break;
				
				if(j==50000){
					write(1, ".", 1);
					j=0;
				}
				j++;
			}
				
	}
	return 0;
}
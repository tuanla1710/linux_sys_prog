#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void)
{
	pid_t pid;
	int status;
	int i;

	switch(pid = fork()){
		case -1:		// fork error
			perror("fork");
			exit(1);
		case 0:			//Child
			for(i=0; i<3; i++){
				printf("Child process --- (%d)\n", getpid());
				sleep(1);
			}
			// printf("Child process --- (%d)\n", getpid());
			system("ps -l");
			exit(2);
			break;
		default:		//Parent (main)
			wait(&status);
			if(WIFEXITED(status)){
				printf("\e[31mChild is terminated by exit(%x)\e[0m\n",status);
			}else if(WIFSIGNALED(status)){
				printf("Chiled is terminated by signal(%d)\n", status);
			}
			printf("\t\tReturned pid = %d\n", pid);
			for(i=0; i<5; i++){
				printf("\t\tParent process ====(%d)\n", getpid());
				sleep(1);
			}
			system("ps -l");
			break;
	}
	return 0;
}

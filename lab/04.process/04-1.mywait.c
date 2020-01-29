#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[]){
	pid_t pid;
	int a=10;
	int status;
	
	if((pid = fork()) == -1){
		perror("fork");
		exit(1);
	}
	if(pid == 0){		//Child process
		printf("CHILD PROCESS---- (%d)\n", getpid());
		printf("INT=%d\n", a);
		sleep(3);
		printf("Child output\n");
		system("ps -f");
		getchar();
		exit(0);
	} else {
		printf("I am Parent Process ---(%d)\n", getpid());
		printf("Returned PID = %d\n", pid);
		wait(&status);
		if(WIFEXITED(status)){
			printf("Child is terminated by exit(%x)\n",status);
		}else if(WIFSIGNALED(status)){
			printf("Chiled is terminated by signal(%d)\n", status);
		}
		sleep(5);
		printf("Parent output\n");
		system("ps -l");
		exit(0);
	}
	return 0;
}
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>

int main(int argc, char *argv[]){
	pid_t pid;
	int a=10;
	
	if((pid = fork()) == -1){
		perror("fork");
		exit(1);
	}
	if(pid == 0){		//Child process
		printf("\e[31mCHILD PROCESS---- (%d)\e[00m\n", getpid());
		printf("\e[31mINT=%d\n", a);
		sleep(3);
		printf("Child output\n");
		system("ps -f");
		exit(0);
	} else {
		printf("I am Parent Process ---(%d)\n", getpid());
		printf("Returned PID = %d\n", pid);
		sleep(5);
		printf("\e[00mParent output\n");
		system("ps -l");
		exit(0);
	}
	return 0;
}
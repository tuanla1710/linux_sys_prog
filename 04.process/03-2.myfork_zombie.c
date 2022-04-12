#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <time.h>

int main(int argc, char *argv[]){
	pid_t pid;
	time_t startTimec, startTimep;
	
	if((pid = fork()) < 0){
		perror("fork");
		exit(1);
	}else if(pid == 0){		//Child process
		printf("\e[31mCHILD PROCESS---- (%d)\e[00m\n", getpid());
		for (startTimec = time(NULL); time(NULL) < startTimec + 8;){
				for(int i=0; i<100000000; i++);
				write(1, "+", 1);
		}
		exit(0);
	}else{					//Parent process
		printf("\e[00mPARENT PROCESS ---(%d)\n", getpid());
		for (startTimep = time(NULL); time(NULL) < startTimep + 10;){
				for(int i=0; i<100000000; i++);
				write(1, "*", 1);
		}
		sleep(100);
	}
	return 0;
}


#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

int repeat = 0;

void handler(int signo){
	fprintf(stdout, "Signal number %d is caught\n", signo);
	sleep(2);
}

int main(int argc, char *argv[]){
	signal(SIGINT, handler);
	signal(SIGQUIT, handler);
	signal(SIGSTOP, handler);
	while(1){
		printf("signal interrupt test --- %d\n", repeat);
		sleep(1);
	}
	
	return 0;
}


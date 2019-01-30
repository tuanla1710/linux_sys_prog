#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

int repeat = 0;

void handler(int signo){
	printf("Signal number %d is caught $d times\n", signo, ++repeat);
	
}

int main(){
	signal(SIGINT, handler);
	signal(SIGQUIT, handler);
	signal(SIGSTOP, handler);
	// signal(SIGINT, SIG_IGN);
	// signal(SIGINT, SIG_DFL);
	while(1){
		printf("signal test\n");
		sleep(1);
	}
	
	return 0;
}
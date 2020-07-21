#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void handler(int sig){
	for(int i=1; i<=3; i++) {
		printf("handler_%d!!\n", i);
		sleep(2);
	}
}
	
int main(void){
	struct sigaction act, oldact;
	sigset_t set;
	
	act.sa_handler = handler;
	sigemptyset(&act.sa_mask);
	sigaddset(&act.sa_mask,SIGQUIT);
	
	act.sa_flags=SA_NODEFER;
	// act.sa_flags=SA_RESTART;
	act.sa_flags=SA_RESETHAND;
	sigaction(SIGINT, &act, &oldact);
	
	while(1){
		printf("signal test\n");
		sleep(1);
	}
	return 0;
}


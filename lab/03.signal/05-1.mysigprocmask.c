#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void handler(int signo){
	printf("Signo[%d] is caught\n", signo);
}

int main(void) {
	sigset_t set1, set2;
	signal(2, handler);
	sigemptyset(&set1);						
	sigemptyset(&set2);
	sigaddset(&set1, 1);   			
	sigaddset(&set2, 2);
	sigprocmask(SIG_BLOCK, &set1, NULL);    //Signal #1 block
	printf("signo #1 blocked\n");
	sleep(5);								
	sigprocmask(SIG_BLOCK, &set2, NULL); 	//signal #2  block   
	printf("signo #2 blocked..... \n");
	sleep(5);
	for(int i=0; ; i++) {    
		printf("Hello Signal ---- %d\n", i);
		if (i==5){
			printf("signo #2 unblocked\n");
			sigprocmask(SIG_UNBLOCK, &set2, NULL);    //Signal #1 block
		}
		sleep(1);  
	}
	return 0;
}

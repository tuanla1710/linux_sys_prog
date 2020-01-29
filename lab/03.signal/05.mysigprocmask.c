#include <stdio.h>
#include <signal.h>
#include <unistd.h>

int main(void) {
	sigset_t set1, set2;
	
	sigemptyset(&set1);						
	// sigemptyset(&set2);
	sigaddset(&set1, 1);   			
	sigaddset(&set1, 2);
	// sigprocmask(SIG_BLOCK, &set1, NULL);    //Signal #1 block
	sigprocmask(SIG_BLOCK, &set1, &set2);    //Signal #1 block
	printf("signo #1 & #2 blocked\n");
	sleep(10);								
	// sigprocmask(SIG_BLOCK, &set2, NULL); 	//signal #2  block   
	// printf("signo #2 blocked..... \n");
	// sleep(5);
	for(int i=0; ; i++) {    
		printf("Hello Signal ---- %d\n", i);
		if (i==5){
			printf("signo #2 unblocked\n");
			sigprocmask(SIG_UNBLOCK, &set1, NULL);    //Signal #1 block
			// sigprocmask(SIG_SETMASK, &set2, NULL);    //Signal #1 block
		}
		sleep(1);  
	}
	return 0;
}

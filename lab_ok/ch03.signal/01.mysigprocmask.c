#include <stdio.h>
#include <signal.h>
#include <unistd.h>

int main(void) {
	sigset_t set1, set2, set3, set4;
	
	sigemptyset(&set1);						
	sigemptyset(&set2);
	sigemptyset(&set3);
	sigemptyset(&set4);
	sigemptyset(&set5);
	
	sigaddset(&set1, 1);   			
	sigaddset(&set2, 2);
	sigaddset(&set3, 3);
	sigaddset(&set4, 3);
	
	sigaddset(&set5, 4);
	sigaddset(&set5, 5);

	sigprocmask(SIG_BLOCK, &set1, NULL);    //Signal #1 block
	printf("signal #1 blocked\n");
	sleep(5);								

	sigprocmask(SIG_BLOCK, &set2, NULL); 	//signal #2  block   
	printf("signal #2 blocked..... \n");	
	sleep(5);
	
	sigprocmask(SIG_BLOCK, &set3, NULL);
	printf("signal #3 blocked..... \n");
	sleep(5);
	
	sigprocmask(SIG_UNBLOCK, &set4, NULL);
	printf("signal #3 unblocked ... \n");
	
	sigprocmask(SIG_SETMASK, &set5, NULL);
	printf("Blocked signals changed to set5 ... \n");
	
	while(1) {    
		printf("Hello Signal\n");    
		sleep(1);  
	}

	return 0;
}

#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include "signalprint.h"

// void print_sigset_t(sigset_t *set);

void handler(int signo){
	printf("Signo[%d] is caught\n", signo);
	sleep(5);
}

int main(void) {
	sigset_t set1, set2;
	
	signal(SIGINT, handler);
	
	sigemptyset(&set1);	
	sigaddset(&set1, 2);	
	sigprocmask(SIG_SETMASK, &set1, NULL);    		
	printf("SIGINT(2) blocked\n");
	print_sigset_t(&set1);
	sleep(5);									
	
	sigemptyset(&set2);							
	sigaddset(&set2, SIGQUIT);   				
	sigprocmask(SIG_BLOCK, &set2, NULL);			
	printf("SIGQUIT(3) blocked but SIGINT(2) still remains blocked..... \n");		
	print_sigset_t(&set2);	
	
	sigprocmask(SIG_SETMASK, NULL, &set1);			
	printf("currently blocked signal are set to set1 \n");		
	print_sigset_t(&set1);
	sleep(5);
	
	sigprocmask(SIG_UNBLOCK, &set1, NULL);			
	printf("SIGINT(2) & SIGQUIT(3) unblocked\n");
		
	while(1) {    
		printf("Hello Signal\n");    
		sleep(1);  
	}

	return 0;
}

#include <stdio.h> 
#include <signal.h> 
#include <unistd.h>
#include <stdlib.h>
#include "signalprint.h"

static void handler(int signo) { 
	printf("\ninterrupt received by signal #(%d)\n", signo); 
} 

int main() { 
	sigset_t mask1,mask2; 
	signal(SIGINT, handler); 
	
	sigemptyset(&mask1); 
	sigaddset(&mask1,SIGINT); 
	sigfillset(&mask2); 
	sigdelset(&mask2, SIGINT);
	
	sigprocmask(SIG_BLOCK,&mask1,NULL); 
	print_sigset_t(&mask1);
	print_sigset_t(&mask2);
	
	printf("\ncritical region 1\n"); 
	sleep(5); 
	printf("\ncritical region 1 ends\n"); 
#if 1
	sigsuspend(&mask2);
	printf("After suspend");
#else
	sigprocmask(SIG_SETMASK, &mask2, NULL); 	
	pause();
	printf("After pause");
#endif
	printf("\ncritical region 2\n"); 
	sleep(10); 
	printf("\ncritical region 2 ends\n"); 
	exit(0); 
}
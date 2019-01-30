#include <stdio.h> 
#include <signal.h> 
#include <unistd.h>
#include <stdlib.h>

static void handler(int signo) { 
	printf("\ninterrupt received by signal #(%d)\n", signo); 
} 

int main() { 
	sigset_t mask1,mask2; 
	signal(SIGINT, handler); 
	signal(3, handler);
	
	sigemptyset(&mask1); 
	sigaddset(&mask1,SIGINT); 
	sigaddset(&mask1,3);
	
	sigprocmask(SIG_BLOCK,&mask1,&mask2); 
	
	printf("\ncritical region 1\n"); 
	sleep(5); 
	printf("\ncritical region 1 ends\n"); 
	
	sigsuspend(&mask2); 
	printf("\ncritical region 2\n"); 
	sleep(5); 
	printf("\ncritical region 2 ends\n"); 
	
	sigprocmask(SIG_SETMASK,&mask2,NULL); 
	exit(0); 
}
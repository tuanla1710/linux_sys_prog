#include <stdio.h> 
#include <signal.h> 
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

static void handler(int signo) { 
	printf("signal handler caught a signal #[%d]\n", signo); 
} 

int main() { 
	sigset_t mask1,mask2; 
	time_t startTime;
	
	signal(SIGINT, handler); 
	sigemptyset(&mask1); 
	sigaddset(&mask1,SIGINT); 
	sigprocmask(SIG_BLOCK,&mask1,&mask2); 
	printf("critical region 1\n"); 
	for (startTime = time(NULL); time(NULL) < startTime + 4; )
		continue;
	printf("critical region 1 ends\n"); 
	sigsuspend(&mask2); 
	sigprocmask(SIG_BLOCK,&mask1,&mask2); 
	printf("critical region 2\n"); 
	for (startTime = time(NULL); time(NULL) < startTime + 4; )
		continue;
	printf("critical region 2 ends\n"); 
	sigprocmask(SIG_SETMASK,&mask2,NULL); 
	exit(0); 
}
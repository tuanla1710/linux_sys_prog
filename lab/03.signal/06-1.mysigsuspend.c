#include <stdio.h> 
#include <signal.h> 
#include <unistd.h>
#include <stdlib.h>

static void handler(int signo) { 
	printf("\ninterrupt received by signal #(%d)\n", signo); 
} 

void print_sigset_t(sigset_t *set){
	int i;

	i = SIGRTMAX;
	do{
		int x = 0;
		i -= 4;
		if (sigismember(set, i+1)) x |= 1;
		if (sigismember(set, i+2)) x |= 2;
		if (sigismember(set, i+3)) x |= 4;
		if (sigismember(set, i+4)) x |= 8;
		printf("%x", x);
	}while (i >= 4); 
	printf("\n");
}

int main() { 
	sigset_t mask1,mask2; 
	signal(SIGINT, handler); 
	
	sigemptyset(&mask1); 
	sigemptyset(&mask2);
	sigaddset(&mask1,SIGINT); 
	sigaddset(&mask1,SIGQUIT); 
	
	// sigprocmask(SIG_BLOCK,&mask1,NULL); 
	print_sigset_t(&mask2);
	
	printf("\ncritical region 1\n"); 
	sleep(5); 
	printf("\ncritical region 1 ends\n"); 
	
	// sigsuspend(&mask2); 
	pause();
	printf("After pause");
	// sigprocmask(SIG_UNBLOCK,&mask1,NULL); 
	printf("\ncritical region 2\n"); 
	sleep(5); 
	printf("\ncritical region 2 ends\n"); 
	
	// sigprocmask(SIG_SETMASK,&mask2,NULL); 
	exit(0); 
}
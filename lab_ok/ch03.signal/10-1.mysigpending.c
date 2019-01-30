#include <stdio.h>
#include <unistd.h>
#include <signal.h>

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

static void handler(int signo) { 
	printf("Signal #(%d) received\n", signo); 
}

int main( void){
	sigset_t sigset, oldset;
	sigset_t pendingset;
	int i = 0;
	
	for(i=1; i<=64; i++){
		signal(i, handler);
	}
	
	// 모든 시그널을 블록화
	sigfillset(&sigset);
	// sigdelset(&sigset, SIGTSTP);
	// sigprocmask(SIG_SETMASK, &sigset, NULL);
	sigprocmask(SIG_BLOCK, &sigset, &oldset);
	i=1;
	while(i<=64){
		printf( "Count__: %d\n", i++);
		sleep(1);
		if (sigpending(&pendingset) == 0){
			print_sigset_t(&pendingset);
#if 1
			if (sigismember(&pendingset, SIGINT)){
				printf( "Pressed Ctrl-C,,, end of loop.\n");
				break;
			}
			if(sigismember(&pendingset, SIGTSTP)){
				printf( "Pressed Ctrl-Z,,, end of loop.\n");
				break;
			}
#endif
		}
   }
   sigprocmask(SIG_SETMASK, &oldset, NULL);
   // sleep(5);
   return 0;
}
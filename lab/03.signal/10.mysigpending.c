#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void print_sigset_t(sigset_t *set);

int main( void){
	sigset_t sigset, oldset;
	sigset_t pendingset;
	
	// 모든 시그널을 블록화
	sigfillset(&sigset);
	// sigprocmask(SIG_SETMASK, &sigset, NULL);
	sigprocmask(SIG_BLOCK, &sigset, &oldset);
	
	for(int i=1; i<32; i++){
		if(i==9 || i==19)
				continue;
		raise(i);
		printf( "Signal : %d\n", i);
		
		if (sigpending(&pendingset) == 0){
			print_sigset_t(&pendingset);
			sleep(1);
		}
   }
   return 0;
}
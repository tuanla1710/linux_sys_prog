#include <stdio.h>
#include <unistd.h>
#include <signal.h>

#if 1
void handler(int sig){
	for(int i=1; i<=3; i++) {
		printf("handler_%d!!\n", i);
		sleep(2);
	}
}
#else
void handler (int sig, siginfo_t *siginfo, void *context){
	printf ("Sending PID: %ld, UID: %ld\n",
			(long)siginfo->si_pid, (long)siginfo->si_uid);
}
#endif
	
int main(void){
	struct sigaction act, oldact;
	sigset_t set;
#if 1	
	act.sa_handler = handler;
	sigemptyset(&act.sa_mask);
	sigaddset(&act.sa_mask,SIGINT);
	sigaddset(&act.sa_mask,SIGQUIT);
	// sigemptyset(&set);
	// sigaddset(&set,SIGINT);
	// sigaddset(&set,SIGQUIT);
	
	act.sa_flags=SA_RESTART;
	// act.sa_flags=SA_NODEFER;
	// act.sa_flags=SA_RESETHAND;
#else
	sigemptyset(&set);
	sigaddset(&set,SIGINT);
	sigaddset(&set,SIGQUIT);	
	act.sa_mask = set;
	act.sa_sigaction = handler;
	act.sa_flags = SA_SIGINFO;
#endif	
	sigaction(SIGTSTP, &act, &oldact);
	while(1){
		printf("signal test\n");
		sleep(1);
	}
	sigaction(SIGINT,&oldact, NULL);
	return 0;
}


#define _GNU_SOURCE /* Get strsignal() declaration from <string.h> */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <time.h>
#include <errno.h>
static volatile sig_atomic_t gotSigquit = 0;
static void handler(int sig){
	printf("Caught signal %d (%s)\n", sig, strsignal(sig));
	/* UNSAFE (see Section 21.1.2) */
	if (sig == SIGQUIT)
	gotSigquit = 1;
}
int main(int argc, char *argv[]){
	int loopNum;
	time_t startTime;
	sigset_t origMask, blockMask;
	sigemptyset(&blockMask);
	
	sigaddset(&blockMask, SIGINT);
	sigaddset(&blockMask, SIGQUIT);
	
	if (sigprocmask(SIG_BLOCK, &blockMask, &origMask) == -1){
		perror("sigprocmask()");
		exit(1);
	}
	signal(SIGINT, handler);
	signal(SIGQUIT, handler);
	
	for (loopNum = 1; !gotSigquit; loopNum++) {
		printf("=== LOOP %d\n", loopNum);
		/* Simulate a critical section by delaying a few seconds */
		for (startTime = time(NULL); time(NULL) < startTime + 10; )
			continue; /* Run for a few seconds elapsed time */
		if (sigsuspend(&origMask) == -1 && errno != EINTR){
			perror("sigsuspended()");
			exit(1);
		}
		pause();
	}
	if (sigprocmask(SIG_SETMASK, &origMask, NULL) == -1){
		perror("sigprocmask()");
		exit(1);
	}
	/* Do other processing... */
	exit(0);
}
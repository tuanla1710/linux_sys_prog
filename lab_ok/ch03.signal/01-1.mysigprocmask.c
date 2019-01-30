#include <stdio.h>
#include <signal.h>
#include <unistd.h>

int main(void) {
	sigset_t set1, set2;

	sigfillset(&set1);						//set1(64bits)을 1로 설정
	sigprocmask(SIG_BLOCK, &set1, NULL);    //모든 시그널 블록 설정
	printf("signal block start \n");
	sleep(5);								//5초 동안 모든 신호의 수신이 pending된다
	
	sigemptyset(&set2);						//set2(64bits)
	sigaddset(&set2, SIGINT);   			//set2(64bits) 중 SIGINT(bit 1, signal 2) 1로 설정

	sigprocmask(SIG_UNBLOCK, &set2, NULL); 	// SIGINT 만 제외하고 모든 신호 BLOCK  
	printf("SIGINT unblocked..... \n");		// 이전(5초 동안) 블럭되었던 신호도 1회 전달된다
	
	// pause();
	sigprocmask(SIG_SETMASK, &set2, NULL);	//ONLY SIGINT blocked
	
	while(1) {    
		printf("Hello Signal\n");    
		sleep(1);  
	}

	return 0;
}

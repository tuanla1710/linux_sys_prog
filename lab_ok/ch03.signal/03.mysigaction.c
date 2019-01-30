#include <stdio.h>
#include <unistd.h>
#include <signal.h>
int count=0;
void handler(int signo)
{
	int i;
	count++;
	for(i=1; i<=3; i++) {
		printf("handler_%d!!\n", i);
		sleep(1);
	}
}
int main(void)
{
	int i=0;
	struct sigaction act, oldact;
	
	act.sa_handler = handler;
	sigemptyset(&act.sa_mask);
	sigaddset(&act.sa_mask,SIGINT);
	sigaddset(&act.sa_mask,SIGQUIT);
	act.sa_flags=SA_RESTART;
	// act.sa_flags=SA_NODEFER;
	sigaction(SIGINT,&act,&oldact );	//SIGINT 수신시 act.sa_handler가 수행
	// sigaction(SIGQUIT, &act, &oldact);
	while(i<10)
	{
		printf("signal test\n");
		sleep(1);
		i++;
	}
	sigaction(SIGINT,&oldact, NULL);
	printf("count = %d\n",count);
	return 0;
}


#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>

static int alarm_flag = 0;

void alarm_handler(int signo){
	printf("\e[31mAlarm Handler ----\e[0m\n");
	alarm_flag = 1;
}

int main(){
	signal(SIGALRM, alarm_handler);
	alarm(5);
	pause();
	if(alarm_flag){
		printf("Alarm test completed\n");
	}
}
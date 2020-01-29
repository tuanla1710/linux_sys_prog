#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pthread.h>

typedef struct alarm_tag {
	int seconds;
	char message[64];
} alarm_t;

void * alarm_thread(void *arg)
{
	alarm_t *alarm = (alarm_t*)arg;
	int status;

printf("alarm_thread-->self:%d\n", (unsigned int)pthread_self());
#if 0
	status = pthread_detach(pthread_self());
	if(status != 0) {
		perror("pthread_detach() error");
		return (void*)3;
	}
#endif
	sleep(alarm->seconds);
	printf("(%d) %s\n", alarm->seconds, alarm->message);
	free(alarm);
	return NULL;
}
	

int main(int argc, char *argv[])
{
	int seconds;
	char line[128];
	alarm_t *alarm;
	pthread_t tid;
	int status;
	
	while(1) {
		printf("Alarm> ");
		if(fgets(line, sizeof(line), stdin) == NULL) exit(0);
		if(strlen(line) <= 1) continue;
		if(!strncmp(line, "exit", 4)) exit(0);
		//if(!strncmp(line, "exit", 4)) pthread_exit(NULL);

		alarm = (alarm_t*)malloc(sizeof(alarm_t));
		if(alarm == NULL) {
			perror("malloc() error");
			exit(1);
		}
		
		if(sscanf(line, "%d %64[^\n]", &alarm->seconds, alarm->message) < 2) {
			fprintf(stderr, "Bad command\n");
			free(alarm);
		} else {
			status = pthread_create(&tid, NULL, alarm_thread, alarm);
			if(status != 0) {
				perror("pthread_create() error");
				exit(2);
			} 
		} // end of if-else
printf("tid:%d, self:%d\n", (unsigned int)tid, (unsigned int)pthread_self());
	} //end of while
}

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

//#define _GNU_SOURCE         /* See feature_test_macros(7) */
#include <unistd.h>
#include <string.h>
#include <sys/syscall.h>

void *thread_function(void *arg);

int main() {
	int status, i;
	pthread_t tid;
	void *thread_result;

	status = pthread_create(&tid, NULL, thread_function, "hello thread");
	if(status !=0){
		perror("pthread_create");
		exit(1);
	}
	
	for(i=1; i<=10; i++){
		printf("Parent thread %d!!\n", i);
#if 1
		if(i==3){
			pthread_cancel(tid);
		}
#endif
		for(int j=0; j<200000000; j++) {}
	}
	return 0;
}

void *thread_function(void *arg){
	int i;
	pid_t tpid, pid;
	int ret, unused;
#if 0
	ret = pthread_setcancelstate (PTHREAD_CANCEL_DISABLE, &unused);
#else
	pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);
#endif

	for(int i=1; i<=10; i++){
		printf("\t\e[31mChild thread %d\e[0m\n", i);
		for(int k=0; k<300000000; k++) {}
		if(i==5){
			pthread_setcancelstate (PTHREAD_CANCEL_ENABLE, &unused);
		}
	}
	char *s = (char *) arg;
	return (void *) strlen(s);
	// exit(0);
	// pthread_exit((void *) strlen(s));
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <sys/types.h>
#include <errno.h>

//#define _GNU_SOURCE         /* See feature_test_macros(7) */
#include <unistd.h>
#include <sys/syscall.h> 


void * thread_function(void *);

int Counter=0;
#ifndef NOMUTEX
pthread_mutex_t mutex_id;
#endif

int main(void)
{
	pthread_t tid1, tid2;
	void *thread_result;

#ifndef NOMUTEX
	if(pthread_mutex_init(&mutex_id, NULL) != 0){
		perror("pthread_mutex_init");
		exit(errno);
	}
#endif

	if(pthread_create(&tid1, NULL, thread_function, "thread1")!=0) {
		perror("pthread_create");
		exit(1);
	}
	
	if(pthread_create(&tid2, NULL, thread_function, "thread2")!=0) {
		perror("pthread_create");
		exit(1);
	}
	
	if(pthread_join(tid1, &thread_result)!=0) {
		perror("pthread_join");
		exit(1);
	}
	if(pthread_join(tid2, &thread_result)!=0) {
		perror("pthread_join");
		exit(1);
	}
	
#ifndef NOMUTEX
	pthread_mutex_destroy(&mutex_id);
#endif

	printf(" thread result : %s\n", (char *) thread_result);
	return 0;
}

void * thread_function(void * arg)
{
	int temp;
	int i, j;
	char buffer[80];

#ifdef DEBUG
	pid_t os_tid;
	printf("\e[34mthread_function called\e[0m\n");
	
	os_tid = syscall(SYS_gettid);
	printf("\e[31mTID: %d\e[0m\n",os_tid);
#endif
	
	for(i=0; i<8; i++) {
#ifndef NOMUTEX
		pthread_mutex_lock(&mutex_id);
#endif
		sprintf(buffer, "%s: CountRelay: from %d to ", (char*)arg, Counter);
		write(1, buffer, strlen(buffer));

		temp=Counter;

// delay
		for(j=0; j<50000000; j++);

		Counter=temp+1;

		sprintf(buffer, "\e[31m%d\e[0m\n", Counter);
		write(1, buffer, strlen(buffer));
		
#ifndef NOMUTEX
		pthread_mutex_unlock(&mutex_id);
#endif

	}
	// getchar();
	pthread_exit("thread end");
}

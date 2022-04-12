#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <sys/types.h>

#define _GNU_SOURCE         /* See feature_test_macros(7) */
#include <unistd.h>
#include <sys/syscall.h> 

pthread_mutex_t Lock;

void * thread_function(void *);

int Counter=0;

int main(void){
	pthread_t tid1, tid2;
	void *thread_result;

	if(pthread_create(&tid1, NULL, thread_function, "thread1")!=0) {
		perror("pthread_create");
		exit(1);
	}
	for(int j=0; j<1000000; j++);
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

	printf("thread result : %s\n", (char *) thread_result);
	return 0;
}

void * thread_function(void * arg){
	int temp;
	int i, j;
	char buffer[80];

	for(i=0; i<8; i++) {
#ifdef SYNC
		pthread_mutex_lock(&Lock);
#endif
		sprintf(buffer, "%s: CountRelay: from %d to ", (char*)arg, Counter);
		write(1, buffer, strlen(buffer));

		for(j=0; j<10000000; j++);
		Counter++;
		
		sprintf(buffer, "\e[31m%d\e[0m\n", Counter);
		write(1, buffer, strlen(buffer));
#ifdef SYNC
		pthread_mutex_unlock(&Lock);
#endif
	}
	// getchar();
	pthread_exit("thread end");
}

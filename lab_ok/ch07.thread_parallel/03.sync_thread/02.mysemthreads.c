#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <sys/types.h>
#include <errno.h>
#include <semaphore.h>

//#define _GNU_SOURCE         /* See feature_test_macros(7) */
#include <unistd.h>
#include <sys/syscall.h> 


void * thread_function(void *);

int Counter=0;
#ifndef NOSEM
sem_t semid;
#endif

int main(void)
{
	pthread_t tid1, tid2;
	void *thread_result;
	int ret;

#ifndef NOSEM
	ret = sem_init(&semid, 0, 1);	//0: 프로세스 내의 쓰레드간 세마포어 공유, 초기값 1
	if(ret != 0){
		perror("sem_init");
		exit(1);
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
	
#ifndef NOSEM
	sem_destroy(&semid);
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
#ifndef NOSEM
		sem_wait(&semid);
#endif
		sprintf(buffer, "%s: CountRelay: from %d to ", (char*)arg, Counter);
		write(1, buffer, strlen(buffer));

		temp=Counter;

// delay
		for(j=0; j<500000; j++);

		Counter=temp+1;

		sprintf(buffer, "\e[31m%d\e[0m\n", Counter);
		write(1, buffer, strlen(buffer));
		
#ifndef NOSEM
		sem_post(&semid);
#endif

		for(j=0; j<50000000; j++);

	}
	// getchar();
	pthread_exit("thread end");
}

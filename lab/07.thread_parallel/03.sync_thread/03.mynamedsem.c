#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <sys/types.h>
#include <errno.h>
#include <semaphore.h>

#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>


#define _GNU_SOURCE         /* See feature_test_macros(7) */
#include <unistd.h>
#include <sys/syscall.h> 


void * thread_function(void *);

int Counter=0;
sem_t *semp, semid;

int main(void){
	pthread_t tid1, tid2;
	void *thread_result;
	int ret;
	int flags;
	mode_t perms;

#ifndef NOSEM
	flags = O_CREAT | O_EXCL;
	// flags = O_CREAT;
	perms = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH;	//rw-rw-rw-
	semp = sem_open("mysem", flags, perms, 1);
	if (semp == SEM_FAILED){
		perror("sem_open");
		exit(2);
	}
	semid = *semp;
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
	sem_close(semp);
	sem_unlink("mysem");
	// sem_unlink((const char *)semp);
	exit(EXIT_SUCCESS);
#endif

	printf(" thread result : %s\n", (char *) thread_result);
	return 0;
}

void * thread_function(void * arg){
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

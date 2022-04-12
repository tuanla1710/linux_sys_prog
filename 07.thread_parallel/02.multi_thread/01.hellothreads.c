#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/syscall.h>

#define NUM_THREAD	3
void *hello_thread(void *arg){
	int tnum = (long) arg;
	pid_t tid = syscall(SYS_gettid);
	for(int i=11; i<=13; i++) {
		printf("Thread #%d[%d]: Hello, World(%d)!\n", tnum ,tid, i);
		for(int j=0; j<10000000; j++){}
	}
	return arg;
}

int main(void){
	pthread_t tid;;
	int status;
	long i;
	for(i=0; i<NUM_THREAD; i++) {
		status = pthread_create(&tid, NULL, hello_thread, (void *)i);
		printf("Thread id = [%u]\n", (unsigned int) tid);
		if(status != 0) {
			perror("thread create");
			exit(1);
		}
		// for(int j=0; j<100000000; j++){}
	}
	printf("\e[31mMain Thread End!!\e[0m\n");
	pthread_exit(NULL);
}

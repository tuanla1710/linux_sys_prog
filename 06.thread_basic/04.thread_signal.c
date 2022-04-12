#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/syscall.h>
#include <pthread.h>
#include <signal.h>
 
void *thread1(void *p){
	while(1){
		printf("thread1 with tpid=%ld\n", syscall(SYS_gettid));
		sleep(2);
	}
	return 0;
}
 
void *thread2(void *p){
	while(1){
		printf("thread2 with tpid=%ld\n", syscall(SYS_gettid));
		sleep(2);
	}
	return 0;
}
 
void *thread3(void *p){
	while(1){
		printf("thread3 with tpid=%ld\n", syscall(SYS_gettid));
		sleep(2);
	}
	return 0;
}
 
 
void handler(int signo, siginfo_t *info, void *extra) {
	pid_t *tpid;
	tpid=malloc(sizeof(pid_t));
	*tpid=syscall(SYS_gettid);
	printf("SIGNO=%d, sig#%d, sig_err#=%d, CODE=%d\n", signo, info->si_signo, info->si_errno, info->si_code);
	pthread_exit ((void *)tpid);
}
 
void sig_handler(void){
        struct sigaction action;
 
        action.sa_flags = SA_SIGINFO; 
        action.sa_sigaction = handler;
 
        if (sigaction(SIGINT, &action, NULL) == -1) { 
            perror("sigusr: sigaction");
            _exit(1);
        }
}
 
int main(){
	pthread_t tid1,tid2,tid3;
	void * ret;
	sigset_t set1;
	
	sigfillset(&set1);
	sigdelset(&set1, SIGINT);
	pthread_sigmask(SIG_SETMASK, &set1, NULL);
	// sigprocmask(SIG_SETMASK, &set1, NULL);
	
	sig_handler();
	pthread_create(&tid1,NULL,thread1,NULL);
	printf("Thread1 created with tid=%ld\n", tid1);
	pthread_create(&tid2,NULL,thread2,NULL);
	printf("Thread2 created with tid=%ld\n", tid2);
	pthread_create(&tid3,NULL,thread3,NULL);
	printf("Thread3 created with tid=%ld\n", tid3);
	pthread_join(tid1, &ret);
	printf("Thread1 exited with tpid=%d\n", *((pid_t *)ret));
	pthread_join(tid2, &ret);
	printf("Thread2 exited with tpid=%d\n", *((pid_t *)ret));
	pthread_join(tid3, &ret);
	printf("Thread3 exited with tpid=%d\n", *((pid_t *)ret));
	for(;;){
		printf("I am main\n");
		sleep(2);
	}
	return 0;
}
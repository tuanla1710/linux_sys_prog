#define _GNU_SOURCE         /* See feature_test_macros(7) */
#include <unistd.h>
#include <sys/syscall.h>
#include <pthread.h>
#include <stdio.h>

main(){
	pthread_t tpid;
	// pid_t tpid;
	// tpid = syscall(SYS_gettid);
	tpid = pthread_self();
	printf("\e[32mParent PTID: %lu, Parent PID: %d\e[0m\n", (unsigned long)tpid, getpid());
}

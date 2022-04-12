#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>

void handler(int signo) {
	pid_t exit_pid;
	printf("\nhandler_pid [%d], handler_ppid [%d]\n", getpid(), getppid());
	exit_pid = waitpid(-1, NULL, WNOHANG);
	if(exit_pid == -1)
		// printf("waitpid error with ERRNO=%d meaning %s\n", errno,  strerror(errno));
		perror("waitpid");
	else
		printf("Terminated child PID = %d\n", exit_pid);
}

int main() {
	signal(SIGCHLD, handler);
	pid_t pid=fork();
	if(pid == 0){
		printf("child pid [%d] with ppid [%d] started\n", getpid(), getppid());
		switch(fork()) {
			case 0:
				printf("grand-child pid [%d] of ppid [%d] started\n", getpid(), getppid());
				int ret=system("sleep 5");
				exit(0);
			default:
				printf("original child pid [%d] of ppid [%d] continued\n", getpid(), getppid());
				sleep(10);
				exit(0);
		}
	}else{
		printf("main pid [%d] of ppid [%d] continued\n", getpid(), getppid());
		sleep(15);
		printf("\n");
	}
}
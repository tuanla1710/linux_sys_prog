#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

pid_t cpid, w;
int status=0;

void handler(int signo){
	printf("Caught signal = %d\n", signo);
	if((waitpid(-1, &status, WUNTRACED | WCONTINUED)) == -1){
        perror("waitpid");
        exit(EXIT_FAILURE);
    }
	if (WIFEXITED(status)) {
        printf("exited, status=%d\n", WEXITSTATUS(status));
		_exit(0);
    } else if (WIFSIGNALED(status)) {
        printf("killed by signal %d\n", WTERMSIG(status));
		exit(3);
    } else if (WIFSTOPPED(status)) {
        printf("stopped by signal %d\n", WSTOPSIG(status));
    } else if (WIFCONTINUED(status)) {
        printf("continued\n");
    }
}

int main(int argc, char *argv[]){
   
	signal(SIGCHLD, handler);
	cpid = fork();
    if (cpid == -1) {
        perror("fork");
        _exit(EXIT_FAILURE);
    }
	if(cpid == 0){            /* Code executed by child */
        printf("Child PID is %ld\n", (long) getpid());
        if (argc == 1)
            pause();                    /* Wait for signals */
        _exit(atoi(argv[1]));
	}else{                    /* Code executed by parent */
		while(1)
			continue;
        exit(EXIT_SUCCESS);
    }
}
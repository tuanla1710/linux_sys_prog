#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>

int main(int argc, char *argv[]){
	
	int i, cnt;
	pid_t pid;
	printf("Main started (pid: %d) by (ppid: %d)\n", getpid(), getppid());
	pid = fork();

	printf("After fork --- (pid: %d) by (ppid: %d), (pid: %d)\n", getpid(), getppid(), pid);

	printf("hello ----- %d\n", getpid());
	
	switch(pid){
		case 0:
			/* cnt = atoi(argv[1]);
			for(i=0; i<cnt; i++){
				printf("MyTask....%d\n", i);
				sleep(1);
			}
				exit(0);
			break; */
			execl("./mytask", "mytask", "10", NULL);
			perror("execl");
			exit(1);
		default:
			for(i=0; i<20; i++){
			// while(1){
				if(pid > 0){
				printf("hello ----%d --- %d\n", i, getpid());
				sleep(1);
				} else {
					perror("fork");
					exit(1);
				}
			}
			
			break;
	}
	return 0;
}
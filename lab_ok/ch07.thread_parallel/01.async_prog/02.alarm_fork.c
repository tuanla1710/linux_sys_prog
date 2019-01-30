#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void handler(int signo){
	pid_t pid;
	for(int i=0; i<2; i++){
		pid = waitpid(-1, NULL, WNOHANG);
		
		if(pid == -1) {
			printf("No Child is running--\n");
			// break;
		}
		if(pid == 0) {
			printf("Might be another child is running\n");
			// break;
		}
		
		if(pid > 0) {
			printf("dead child = %d\n", pid);
			// break;
		}
	}		//for 
	
}

int main(int argc, char *argv[])
{
	int seconds;
	char line[128];
	char message[64];
	pid_t pid;
	int status;
	
	signal(SIGCHLD, handler);
	
	while(1) {
		printf("Alarm> ");
		if(fgets(line, sizeof(line), stdin) == NULL) exit(0);
		if(strlen(line) <= 1){
			continue;
		} 
		if(!strncmp(line, "exit", 4)) exit(0);
		
		if(sscanf(line, "%d %64[^\n]", &seconds, message) < 2) {
			fprintf(stderr, "Bad command\n");
			continue;
		} else {
			pid = fork();
			switch(pid) {
			case -1 :
				perror("fork() error");
				break;
			case 0 :
				printf("child (%d) is running\n", getpid());
				sleep(seconds);
				printf("(%d) %s\n", seconds, message);
				exit(0);
				
			default :
				printf("Parent (%d) is running\n", getpid());
				continue;
			} // end of switch
		} // end of if-else
	} //end of while
}

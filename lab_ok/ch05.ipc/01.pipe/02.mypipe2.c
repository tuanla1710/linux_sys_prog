#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define MSGSIZE	64

int main(void){
	int pd[2];
	pid_t ret;
	char buf[MSGSIZE];
	int i, len;
	
	if(pipe(pd) == -1){
		perror("pipe");
		exit(1);
	}
	
	switch(fork()){
		case -1:
			perror("fork");
			close(pd[0]);
			close(pd[1]);
			exit(1);
			break;
		case 0:
			close(pd[0]);
			for(i=0; i<10; i++) {
				sprintf(&buf[0], "Hello, World #%d", i+1);
				write(pd[1], buf, strlen(buf));
				sleep(1);
			}
			close(pd[1]);
			exit(0);
			break;
		default:
			close(pd[1]);
			for(i=0; i<10; i++) {
				memset(&buf[0], 0, MSGSIZE);
				len = read(pd[0], buf, MSGSIZE);
				buf[len] = '\0';
				printf("PARENT: %s\n", buf);
			}
			close(pd[0]);
			break;
	}
	
	return 0;
}

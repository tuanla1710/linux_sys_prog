#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <errno.h>


int main(int argc, char *argv[]){
	
	if(argc != 2){
		fprintf(stderr, "Usage: %s <pid no>\n", argv[0]);
		exit(1);
	}
	
	if((kill(atoi(argv[1]), SIGTERM)) == -1){
		if(errno == EINVAL){
			printf("Invalid signal\n");
		}else if(errno == EPERM){
			printf("No Permission\n");
		}else if(errno == ESRCH){
			printf("No such process\n");
		}
	}
	return 0;
}
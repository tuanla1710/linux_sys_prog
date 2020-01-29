#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void handler(int signo){
	printf("Received Signal no - %d\n", signo);
	while(1){
		printf("Press Control-C\n");
		sleep(1);
	}
}

int main(int argc, char *argv[]){
	int a,b;
	if(argc < 3){
		fprintf(stderr, "Usage: %s <num1> <num2>\n", argv[0]);
		exit(1);
	}
	signal(SIGFPE, handler);	//it will be terminated by float point exception
								//if it is not handled
	a = atoi(argv[1]);
	b = atoi(argv[2]);
	if(b == 0) raise(SIGFPE);
	printf("divide....\n");
	a = a/b;
	return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	int i;
	pid_t pid, ppid;
	pid=getpid();
	ppid=getppid();
	
	printf("%s PID = %d\n", argv[0], pid);
	printf("%s PPID = %d\n", argv[0], ppid);
	
	for(i=1; i<=atoi(argv[1]); i++) {
		printf("MyTask_%d!!\n", i);
		sleep(1);
	}
	return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[]){
	int i, ret;
	pid_t pid, ppid;
	
	printf("%s PID = %d\n", argv[0], getpid());
	printf("%s PPID = %d\n", argv[0],getppid());
#if 0	
	ret = execl ("/bin/ps", "ps", "-f", NULL);
	if (ret == -1)
		perror ("execl");
#else
#if 0
	char *args[] = {"ps", "-f", NULL};
	ret = execv ("/bin/ps", args);
	if (ret == -1)
		perror ("execv");
#else
	char *args[] = {"ps", "-f", NULL};
	ret = execvp ("ps",  args);
	if (ret == -1)
		perror ("execvp");
#endif
#endif
	
	return 0;
}

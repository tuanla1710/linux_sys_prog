#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <wait.h>

int a=1000;
int b;

int main(void) {
	pid_t pid;
	int status;
	int c=10000, c2;
	char *d = "parent";
	char *name;
	
	name = malloc(50);

	switch (pid=fork()) {
		case -1:
			perror("fork failed");
			break;
		case 0:				// child process
			printf("CHILD PROCESS : %d\n", getpid());
#if 0
			execl("./00.process", "00.process", (char *)0);
#else
			char *args[] = {"01.mytask", "10", NULL};
			if(execv("./01.mytask", args) == -1)
				perror("execv");
#endif
		default:
			printf("PARENT PROCESS : %d\n", getpid());
			printf("%s[%d] of ppid[%d]\n", d, getpid(), getppid());
			printf("paddr(TEXT)=> \tmain:%p\n", main);
			printf("paddr(CONST)=> d:%p, d_value:%s\n", d, d);
			printf("paddr(DATA)=> a:%p, a_value:%d\n", &a, *(&a));
			printf("paddr(BSS)=> b:%p, b_value:%d\n", &b, *(&b));
			printf("paddr(HEAP)=> name:%p\n", name);
			printf("paddr(STACK)=> c:%p, c_value:%d, d:%p, d_value:%p\n", &c, *(&c), &d, *(&d));
			sleep(1);
			system("ps -lf");
			pid = wait(&status);
			printf("parent : waited (%d) and completed!\n", pid);
			exit(0);
	}
	return 0;
}


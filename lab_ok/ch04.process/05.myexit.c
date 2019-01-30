#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void)
{
	int status;

	switch(fork())
	{
		case -1:
				perror("fork");
				exit(1);
				break;
		case 0:
				system("ps -l");
				sleep(5);
				//exit(0);
				exit(2);
				break;
		default:
				wait(&status);
				printf("status : %x\n", status);
				if(WIFEXITED(status)) {
					printf("exit code of child process : %x\n",WEXITSTATUS(status));
				}
	}
}

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char *argv[]) {
	int fd1, fd2;
	char *buf = "This is a dup2() demonstration\n";
	
	if((fd1 = open(argv[1], O_WRONLY |O_CREAT|O_TRUNC, 0644)) == -1){
		perror("open");
		exit(1);
	}
	
	// if((fd1 = open("/dev/pts/9", O_WRONLY |O_CREAT|O_TRUNC)) == -1){
		// perror("open");
		// exit(1);
	// }
	printf("FD1 = %d\n", fd1);
	fd2 = dup2(fd1, 1);
	// close(fd1);
	printf("FD2 = %d\n", fd2);
	write(fd2, buf, strlen(buf));
	close(fd1);
	printf("Hello World ~~~\n");
	fprintf(stdout, "This is the output to stdout\n");
	close(fd1);
	getchar();
	
	return 0;
}

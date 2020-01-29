#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define BUF_SIZE	1024

int main(int argc, char *argv[]){
	
	char buf[BUF_SIZE];
	int fd1, fd2, ret, openflags, numRead;
	mode_t perms;
	
	if(argc != 3) {
		printf("Usage: %s <source filename> <destination filename>\n", argv[0]);
		exit(1);
	}
	
	if((fd1 = open(argv[1], O_RDONLY)) == -1){
		perror("file open1 error");
		exit(2);
	}
	
	openflags = O_WRONLY|O_CREAT|O_TRUNC;
	perms = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH;	//rw-rw-rw-
	
	if((fd2 = open(argv[2], openflags, perms)) == -1){
		perror("file open2 error");
		close(fd1);
		exit(2);
	}
	
	while ((numRead = read(fd1, buf, BUF_SIZE)) > 0){
		if(write(fd2, buf, numRead) != numRead){
			perror("write()");
			break;
		}
	}
	close(fd1);
	close(fd2);
	return 0;
}

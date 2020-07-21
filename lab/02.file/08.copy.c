#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define BUF_SIZE	1024

int main(int argc, char *argv[]){
	
	char buf[BUF_SIZE];
	int fd1, fd2, openflags, numRead;
	mode_t perms;
	struct stat ret;
	
	if(argc != 3) {
		printf("Usage: %s <source filename> <destination filename>\n", argv[0]);
		exit(1);
	}
	
	if((fd1 = open(argv[1], O_RDONLY)) == -1){
		perror("file open1 error");
		exit(2);
	}
	
	lstat(argv[1], &ret);
	perms = ret.st_mode & (S_IRWXU | S_IRWXG | S_IRWXO);
	openflags = O_WRONLY|O_CREAT;
	
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

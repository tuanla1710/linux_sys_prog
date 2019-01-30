#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define BUF_SIZE	4096

int main(int argc, char *argv[]){
	
	char buf[BUF_SIZE];
	int fd1, fd2, ret;
	
	if(argc != 3) {
		printf("Usage: %s <source filename> <destination filename>\n", argv[0]);
		exit(1);
	}
	
	if((fd1 = open(argv[1], O_RDONLY)) == -1){
		perror("file open1 error");
		exit(2);
	}
	
	if((fd2 = open(argv[2], O_WRONLY|O_CREAT, S_IRWXU|S_IRWXG|S_IRWXO)) == -1){
		perror("file open2 error");
		close(fd1);
		exit(2);
	}
	
	// if(read(fd, data, sizeof(INFO)*data_no) != sizeof(INFO)*data_no) {
	
	while(1){
		ret = read(fd1, buf, BUF_SIZE);
		if(ret == 0)
			break;
		if(write(fd2, buf, ret) != ret){
			perror("write()");
			break;
		}
	}
	
	close(fd1);
	close(fd2);
	return 0;
}

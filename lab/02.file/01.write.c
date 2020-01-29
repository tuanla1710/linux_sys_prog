#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[])
{
	int fd;
	int i;
	char data[]="This is Linux System Programming\n";
	
	// if((fd=open(argv[1], O_WRONLY|O_TRUNC)) == -1){
	if((fd=open(argv[1], O_WRONLY|O_CREAT|O_APPEND, 0664)) == -1){
	// if((fd=open(argv[1], O_WRONLY|O_CREAT|O_EXCL)) == -1){
		perror("open");
		exit(1);
	}
	if(write(fd, &data, strlen(data)) == -1){
		perror("write");
		close(fd);
		exit(2);
	}
	if(fsync(fd) == -1){
		perror("fsync()");
	}
	close(fd);
	return 0;
}

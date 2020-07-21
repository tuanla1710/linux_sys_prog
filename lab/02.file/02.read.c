#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

#define BUF_SIZE	4096

int main(int argc, char *argv[]){
	int fd;
	int ret;
	char buf[BUF_SIZE];
	if(argc < 2){
		printf("Usage: %s <filename>\n", argv[0]);
		exit(1);
	}
	fd = open(argv[1], O_RDONLY);
	if(fd == -1){
		perror("open()");
		exit(1);
	}
	errno=0;
	while((ret=read(fd, buf, sizeof(buf))) !=0){
		if(ret == -1){
			if(errno == EINTR)
				continue;
			perror("read");
			break;
		}
		buf[ret] = '\0';
		// printf("%s\n", buf);
		for(int i=0; i<ret; i++){
			printf("%c", buf[i]);
		}
	}
	close(fd);
	return 0;
}
#include <stdio.h>         // puts()
#include <string.h>        // strlen(), memset()
#include <fcntl.h>         // O_RDWR, O_CREAT
#include <unistd.h>        // write(), close(), dup()

#define  BUFF_SIZE   1024

int main()
{
	int   fd1;
	int   fd2;
	char  buff[BUFF_SIZE];
	char *str   = "This is the test of dup2\n";

	fd1 = open("./test.txt", O_RDWR|O_CREAT|O_TRUNC, 0644);
	fd2 = dup2(fd1, 100);
	// fd2 = dup(fd1);
	printf("fd1= %d  fd2= %d\n", fd1, fd2); 
	if(write(fd1, str, strlen(str)) == -1)
		perror("write");
	close(fd1);                        // fd1 닫음
	
	// write(fd2, str, strlen(str));
	lseek(fd2, 0, SEEK_SET);
	memset(buff, '\0', BUFF_SIZE);
	read(fd2, buff, BUFF_SIZE);

	// printf("%s\n", buff);
	
	getchar();

	close(fd2);                        // fd2 닫음

	return 0;
}
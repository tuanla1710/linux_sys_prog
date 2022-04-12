#include <stdio.h>
#include <unistd.h>  
#include <sys/mman.h>
#include <sys/stat.h>       
#include <fcntl.h>
#include <string.h>

#define  MEM_SIZE    128

int main() {
	int fd;
	void *shm_addr;
	const char *message0= "Welcome to ";
	const char *message1= "Linux Systems ";
	const char *message2= "Programming!";
	
	//�޸� ��ü ����
	fd = shm_open("/mydata", O_RDWR | O_CREAT, 0666);
	
	//�޸� ��ü ũ�� ����
	ftruncate(fd, MEM_SIZE);
		
	//�޸� ��ü ����
	shm_addr = mmap(0, MEM_SIZE, PROT_WRITE, MAP_SHARED, fd, 0);
	printf( "Map addr is %p\n", shm_addr );
#if 1	
	write(fd, message0, strlen(message0));
	write(fd, message1, strlen(message1));
	write(fd, message2, strlen(message2));
#else
	memcpy(shm_addr, message0, strlen(message0));
	shm_addr += strlen(message0);
	sprintf(shm_addr, message1, strlen(message1));
	shm_addr += strlen(message1);
	memcpy(shm_addr, message2, strlen(message2));
	shm_addr += strlen(message2);
#endif
	printf("Press enter when read ");
	getchar();
	munmap(shm_addr, MEM_SIZE);
	shm_unlink("/mydata");
	close(fd);
	return 0;
}


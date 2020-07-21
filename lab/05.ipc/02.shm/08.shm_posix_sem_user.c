#include <semaphore.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/mman.h>

#include <stdlib.h> 
#include <stdio.h>

#define KEY_NUM     0x2222
#define	MEM_SIZE	1024
        
const char *countFile = "count.db";
int main(int argc, char **argv){       
	int count = 100;
	int fd; 
	int res;
	sem_t *mysem;
	
	int shm_id, shm;
	void *shm_addr;
	

	printf("Started --------------------\n");
	if((shm_id = shmget((key_t)KEY_NUM,MEM_SIZE,IPC_CREAT|0666)) == -1){
		perror("shmget");
		exit(1);
	}

	if((shm_addr = shmat(shm_id, NULL, 0)) == (void *)-1){
		perror("shmat");
		exit(1);
	}
	
#ifdef NAMED
	if((mysem = sem_open("mysem", O_CREAT, 0777, 1)) == SEM_FAILED)
	{
			perror("Sem Open Error");
			return 1;
	}
#else
	printf("semaphore ---------------\n");
	if ((shm = shm_open("myshm", O_RDWR | O_CREAT, S_IRWXU)) < 0) {
		perror("shm_open");
		exit(1);
	}

	if (ftruncate(shm, sizeof(sem_t)) < 0 ) {
		perror("ftruncate");
		exit(1);
	}
	if ((mysem = mmap(NULL, sizeof(sem_t), PROT_READ | PROT_WRITE, MAP_SHARED, shm, 0)) == MAP_FAILED) {
		perror("mmap");
		exit(1);
	}	
	if(sem_init(mysem, 1, 0) ==-1)
    {
        perror("Sem init Error");
        return 1;
    }
#endif
	

	for(int i=0; i<500; i++){  
#ifdef SEM	
		sem_wait(mysem);
#endif
		sprintf((char *)shm_addr, "%d", getpid());
		for(int j=0; j<3000000; j++){}
		if(getpid() == atoi(shm_addr))
			putchar('0');
		else
			putchar('X');
		fflush(stdout);
#ifdef SEM
		sem_post(mysem);
#endif
                
	}  
	if(shmdt(shm_addr) !=0){
		perror("shmdt");
		exit(2);
	}
#ifndef NAMED
	sem_destroy(mysem);
#endif
}               
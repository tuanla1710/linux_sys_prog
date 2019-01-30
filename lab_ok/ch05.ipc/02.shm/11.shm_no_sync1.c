#include <stdio.h>
#include <unistd.h>   
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>

#define  KEY_NUM     0x2222
#define  MEM_SIZE    1024

int main() {
	int shm_id;
	void *shm_addr, *shm_addr_dt;
	int i, j;
	
	if((shm_id = shmget((key_t)KEY_NUM,MEM_SIZE,IPC_CREAT|0666)) == -1){
		perror("shmget");
		exit(1);
	}
	
	if((shm_addr = shmat(shm_id, NULL, 0)) == (void *)-1){
		perror("shmat");
		exit(1);
	}
	
	for(i=0; i<300; i++){
		sprintf((char *)shm_addr, "%d", getpid());
		for(j=0; j<3000000; j++){}
		if(getpid() == atoi(shm_addr))
			putchar('0');
		else
			putchar('X');
		fflush(stdout);
	}
	
	if(shmdt(shm_addr) !=0){
		perror("shmdt");
		exit(2);
	}
	
	if(shmctl(shm_id, IPC_RMID, NULL) == -1){
		perror("shmctl");
		exit(2);
	}
	
	return 0;
}
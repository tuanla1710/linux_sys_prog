#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>

#define KEY_NUM     0x2222
#define	MEM_SIZE	1024
static int	semid;

void lock(){
	struct sembuf pbuf;			//set of semaphore *sops
	pbuf.sem_num = 0;			//세마포어 번호
	pbuf.sem_op = -1;			//세마포어 연산
	pbuf.sem_flg = SEM_UNDO;	//프로세스가 종료되면 시스템에서 세마포어 설정을 원래상태로 복귀
	if(semop(semid, &pbuf, 1) == -1){
		perror("p()-semop");
	}
}

void unlock(){
	struct sembuf vbuf;			//set of semaphore *sops
	vbuf.sem_num = 0;			//세마포어 번호
	vbuf.sem_op = 1;			//세마포어 연산
	vbuf.sem_flg = SEM_UNDO;	//프로세스가 종료되면 시스템에서 세마포어 설정을 원래상태로 복귀
	if(semop(semid, &vbuf, 1) == -1){
		perror("v()-semop");
	}
}

int main() {
	int shm_id;
	void *shm_addr;
	int i, j;
	struct shmid_ds shm_stat;
	union senum {
		int val;
		struct semid_ds *buf;
		unsigned short int *array;
	} sem_ctrl;
	
	int sem_val;
	//struct sembuf sem_ops;
	
	printf("Started --------------------\n");
	if((shm_id = shmget((key_t)KEY_NUM,MEM_SIZE,IPC_CREAT|0666)) == -1){
		perror("shmget");
		exit(1);
	}
	
	if((semid = semget((key_t)0x1234,1,IPC_CREAT|0666)) == -1){
		perror("shmget");
		exit(1);
	}

#if 1 
	sem_val=semctl(semid, 0, GETVAL, sem_ctrl);
	printf(" sema:%d\n ", sem_val);
	sem_ctrl.val=sem_val;
	semctl(semid, 0, SETVAL, sem_ctrl);
#endif
	
	if((shm_addr = shmat(shm_id, NULL, 0)) == (void *)-1){
		perror("shmat");
		exit(1);
	}
	
	for(i=0; i<500; i++){
#ifdef SEM
		lock();
#endif
		sprintf((char *)shm_addr, "%d", getpid());
		for(j=0; j<5000000; j++){}
		if(getpid() == atoi(shm_addr))
			putchar('0');
		else
			putchar('X');
		fflush(stdout);
#ifdef SEM
		unlock();
#endif
#if 0
	sem_val=semctl(semid, 0, GETVAL, sem_ctrl);
	printf(" sema:%d ", sem_val);
#endif
	}
	
	if(shmdt(shm_addr) !=0){
		perror("shmdt");
		exit(2);
	}
	
	// if(shmctl(shm_id, IPC_RMID, NULL) == -1){
		// perror("shmctl");
		// exit(2);
	// }
	
	return 0;
}
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <time.h>

#define  KEY_NUM     0x2222
#define  MEM_SIZE    1024
#define		MAX_ACCESS	1

static int	sem_id;
void p(){
	struct sembuf pbuf;
	pbuf.sem_num = 0;			//세마포어 번호
	pbuf.sem_op = -1;			//세마포어 증감값
	pbuf.sem_flg = SEM_UNDO;	//프로세스가 종료되면 시스템에서 세마포어 설정을 원래상태로 복귀
	if(semop(sem_id, &pbuf, 1) == -1){
		perror("p()-semop");
	}
}

void v(){
	struct sembuf vbuf;
	vbuf.sem_num = 0;			//세마포어 번호
	vbuf.sem_op = 1;			//세마포어 증감값
	vbuf.sem_flg = SEM_UNDO;	//프로세스가 종료되면 시스템에서 세마포어 설정을 원래상태로 복귀
	if(semop(sem_id, &vbuf, 1) == -1){
		perror("v()-semop");
	}
}

union senum {
		int val;
		struct semid_ds *buf;
		unsigned short int *array;
}sem_ctrl;

int main() {
	int shm_id, sem_val, i, j;
	time_t timer;
	void *shm_addr;
	
	if((shm_id = shmget((key_t)KEY_NUM,MEM_SIZE,IPC_CREAT|0666)) == -1){
		perror("shmget");
		exit(1);
	}
	
	if((sem_id=semget((key_t) 0x1234, 1, IPC_CREAT|0666)) == -1 )  {
		perror("shmget failed !!");         
		exit(1);
	}
	
	sem_val = semctl(sem_id, 0, GETVAL, sem_ctrl);
	printf("Semctl val: %d\n", sem_val);
	
	if (sem_val == 0)
		sem_ctrl.val = 1;
	
	if(semctl(sem_id, 0, SETVAL, sem_ctrl) == -1) {
		perror("semctl");
		exit(1);
	}
	
	if((shm_addr = shmat(shm_id, NULL, 0)) == (void *)-1){
		perror("shmat");
		exit(1);
	}
	
	for(i=0; i<20; i++){
		p();
		sprintf((char *)shm_addr, "%d", getpid());
		for(j=0; j<50000000; j++){}
		// for(timer=time(NULL); time(NULL) < timer + 0.000001;)
			// continue;
		if(getpid() == atoi(shm_addr))
			putchar('0');
		else
			putchar('X');
		fflush(stdout);
		v();
#if 1
	printf(" sema:%d ", sem_val);
#endif
	}
	if(shmdt(shm_addr) !=0){
		perror("shmdt");
		exit(2);
	}
	return 0;
}
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
	pbuf.sem_num = 0;			//�������� ��ȣ
	pbuf.sem_op = -1;			//�������� ����
	pbuf.sem_flg = SEM_UNDO;	//���μ����� ����Ǹ� �ý��ۿ��� �������� ������ �������·� ����
	if(semop(semid, &pbuf, 1) == -1){
		perror("p()-semop");
	}
}
void unlock(){
	struct sembuf vbuf;			//set of semaphore *sops
	vbuf.sem_num = 0;			//�������� ��ȣ
	vbuf.sem_op = 1;			//�������� ����
	vbuf.sem_flg = SEM_UNDO;	//���μ����� ����Ǹ� �ý��ۿ��� �������� ������ �������·� ����
	if(semop(semid, &vbuf, 1) == -1){
		perror("v()-semop");
	}
}

int main() {
	int shm_id;
	void *shm_addr;
	int i, j;
	
	printf("Started --------------------\n");
	shm_id = shmget((key_t)KEY_NUM,MEM_SIZE,IPC_CREAT|0666);
	semid = semget((key_t)0x1234,1,IPC_CREAT|0666);
	shm_addr = shmat(shm_id, NULL, 0);
	
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
	}
	shmdt(shm_addr);
	return 0;
}


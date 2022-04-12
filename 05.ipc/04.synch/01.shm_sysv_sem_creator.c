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
	int ret;
	struct sembuf lockop;		//set of semaphore *sops
	lockop.sem_num = 0;			//�������� ��ȣ
	lockop.sem_op = -1;			//�������� ����
	lockop.sem_flg = SEM_UNDO;	//���μ����� ����Ǹ� �ý��ۿ��� �������� ������ �������·� ����
	if(semop(semid, &lockop, 1) == -1){
		perror("lock()-semop");
	}
}
void unlock(){
	struct sembuf unlockop;			//set of semaphore *sops
	unlockop.sem_num = 0;			//�������� ��ȣ
	unlockop.sem_op = 1;			//�������� ����
	unlockop.sem_flg = SEM_UNDO;	//���μ����� ����Ǹ� �ý��ۿ��� �������� ������ �������·� ����
	if(semop(semid, &unlockop, 1) == -1){
		perror("unlock()-semop");
	}
}

#if 1
union senum {
		int val;
		struct semid_ds *buf;
		unsigned short int *array;
} sem_ctrl;
#endif

int main() {
	int shm_id;
	void *shm_addr;
	int i, j;
	struct shmid_ds shm_stat;
	
	printf("Started --------------------\n");
	shm_id = shmget((key_t)KEY_NUM,MEM_SIZE,IPC_CREAT|0666);
	shm_addr = shmat(shm_id, NULL, 0);
	semid = semget((key_t)0x1234,1,IPC_CREAT|0666);
	for(i=0; i<500; i++) {
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
	shmctl(shm_id, IPC_RMID, NULL);
	return 0;
}



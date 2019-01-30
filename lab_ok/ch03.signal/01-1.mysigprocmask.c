#include <stdio.h>
#include <signal.h>
#include <unistd.h>

int main(void) {
	sigset_t set1, set2;

	sigfillset(&set1);						//set1(64bits)�� 1�� ����
	sigprocmask(SIG_BLOCK, &set1, NULL);    //��� �ñ׳� ��� ����
	printf("signal block start \n");
	sleep(5);								//5�� ���� ��� ��ȣ�� ������ pending�ȴ�
	
	sigemptyset(&set2);						//set2(64bits)
	sigaddset(&set2, SIGINT);   			//set2(64bits) �� SIGINT(bit 1, signal 2) 1�� ����

	sigprocmask(SIG_UNBLOCK, &set2, NULL); 	// SIGINT �� �����ϰ� ��� ��ȣ BLOCK  
	printf("SIGINT unblocked..... \n");		// ����(5�� ����) ���Ǿ��� ��ȣ�� 1ȸ ���޵ȴ�
	
	// pause();
	sigprocmask(SIG_SETMASK, &set2, NULL);	//ONLY SIGINT blocked
	
	while(1) {    
		printf("Hello Signal\n");    
		sleep(1);  
	}

	return 0;
}

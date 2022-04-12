#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

int main(void){
	char buf[1024];
	ssize_t n;
	int msqid;
	struct msgbuf {
		long m_type;
		char m_text[1024];
	}recvbuf;
	msqid = msgget(0x222, IPC_CREAT | 0666);		//���� �޼��� ť�� ���ϰų� ���ο� �޼��� ť ��ü ����
	if(msqid == -1){
		perror("msgget error");
		exit(1);
	}
	while(1){
		n = msgrcv(msqid, &recvbuf, 1024, 0, 0);
		recvbuf.m_text[n] = '\0';
		printf("\e[31mRx: %s\e[0m", recvbuf.m_text);
		if(!strncmp(recvbuf.m_text,"end", 3)){
			break;
		}
	}
	if(msgctl(msqid, IPC_RMID, 0) == -1){		//�޼��� ť ��ü ����
		perror("msgctl error");
		exit(1);
	}
	return 0;
}

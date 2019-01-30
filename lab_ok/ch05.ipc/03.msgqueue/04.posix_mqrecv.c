#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>

int main(int argc, char *argv[]){
	
	struct mq_attr attr;
	attr.mq_maxmsg = 5;
	attr.mq_msgsize = 4;
	int value;
	
	mqd_t mqd;
	
	printf("MQ Receiver program start -----\n");
	
	//메세지 큐 열기/생성
	mqd = mq_open("/my_queue", O_RDWR | O_CREAT, 0666, &attr);
	if(mqd == -1){
		perror("mq_open error");
		exit(1);
	}
	
	while(1){
		//메시지 전송
		if((mq_receive(mqd, (char *)&value, attr.mq_msgsize, NULL)) == -1){
			perror("mq_receive error");
			mq_close(mqd);
			exit(1);
		}
		printf("\e[31mReceived data %d\e[0m\n", value);
		if(value++ == atoi(argv[1])){
			break;
		}
	}
	mq_close(mqd);
	
	//POSIX 메세지 큐 제거
	mq_unlink("/my_queue");
	printf("MQ Receiver is out");
	
	return 0;
}

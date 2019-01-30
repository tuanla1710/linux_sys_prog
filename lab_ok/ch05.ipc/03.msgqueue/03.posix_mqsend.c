#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>

int main(int argc, char *argv[]){
	
	struct mq_attr attr;
	attr.mq_maxmsg = 5;
	attr.mq_msgsize = 4;
	int value = 1;
	
	mqd_t mqd;
	
	printf("MQ Sender program start -----\n");
	
	//메세지 큐 열기/생성
	mqd = mq_open("/my_queue", O_WRONLY, 0666, &attr);
	if(mqd == -1){
		perror("mq_open error");
		exit(1);
	}
	
	while(1){
		//메시지 전송
		if((mq_send(mqd, (char *)&value, attr.mq_msgsize, 1)) == -1){
			perror("mq_send error");
			mq_close(mqd);
			exit(1);
		}
		printf("Send data %d\n", value);
		if(value++ == atoi(argv[1])){
			break;
		}
		sleep(1);
	}
	mq_close(mqd);
	printf("MQ Sender is out");
	
	return 0;
}

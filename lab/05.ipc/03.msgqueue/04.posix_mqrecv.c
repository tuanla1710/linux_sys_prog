#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>
#include <string.h>

int main(int argc, char *argv[]){
	struct mq_attr attr;
	int value=1;
	char msg[128] = {0};
	mqd_t mqd;
	
	mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH;

    memset( &attr, 0x00, sizeof(struct mq_attr) );
    attr.mq_maxmsg = 10;
    attr.mq_msgsize = 128;
    attr.mq_flags = 0;
    attr.mq_curmsgs = 0;
	
	
	mqd = mq_open("/myqueue", O_RDWR|O_CREAT, mode, &attr);	//�޼��� ť ����/����
	if(mqd == -1){
		perror("mq_open error");
		exit(1);
	}
	
	mq_getattr(mqd, &attr);
	printf("# of messages currently on queue: %ld\n", attr.mq_curmsgs);
	
	while(1){
		if((mq_receive(mqd, (char *)msg, (size_t)attr.mq_msgsize, NULL)) == -1){	//�޽��� ����
			perror("mq_receive error");
			mq_close(mqd);
			exit(1);
		}
		printf("\e[31mReceived data : %s[%d]\e[0m\n", msg, value);
		if(value++ == atoi(argv[1]))
			break;
	}
	mq_close(mqd);
	// mq_unlink("/myqueue");					//POSIX �޼��� ť ����
	// printf("MQ Receiver is out\n");
	return 0;
}

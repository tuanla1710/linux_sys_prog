#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <time.h>

int main(void) {
	int pd[2], read_fd, write_fd;
	pid_t pid;
	time_t timer1, timer2;
	char tx_buf[100], rx_buf[100];
	if ( pipe(pd) == -1 ) {
		perror("pipe");    
		exit(1);    
	}
	read_fd = pd[0];    
	write_fd = pd[1];
  
	switch(pid=fork()) {
		case 0:    
			strcpy(tx_buf, "Hello Parent !!! Pipe Connected...");
			write(write_fd, tx_buf, strlen(tx_buf)+1);
			for(timer1=time(NULL); time(NULL)<timer1 + 2;)
				continue;
			read(read_fd, rx_buf, sizeof(rx_buf));
			printf("--------> CHILD: %s from Parent\n", rx_buf);
			exit(0);
		default:    
			read(read_fd, rx_buf, sizeof(rx_buf));
			printf("PARENT: %s from Child\n", rx_buf);
			strcpy(tx_buf, "Ok, Good~~~");
			write(write_fd, tx_buf, strlen(tx_buf)+1);
			for(timer2=time(NULL); time(NULL)<timer2 + 4;)
				continue;   	
			exit(0);
	}
}

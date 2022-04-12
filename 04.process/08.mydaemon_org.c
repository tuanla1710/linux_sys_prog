#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <syslog.h>
#include <fcntl.h>
#include <stdlib.h>

int main(void) {
	pid_t pid, sid;
	int fd, cnt=0;
	const char pidfile[] = "/var/run/mydaemon.pid";
	if((pid = fork()) != 0) {
		if ((fd = open(pidfile, O_WRONLY | O_CREAT | O_TRUNC, 0666)) == -1){
			perror("open failed"); return 1;
		}
		dup2(fd, 1);				/* write pid to file */
		fprintf(stdout, "%d\n", pid);
		fflush(stdout);
		close(fd);					/* close the file pointer */
		exit(0);					//parent exit
	}
	sid=setsid();
	close(0); close(1); close(2);
	if(chdir("/") !=0 ) {
		perror("chdir");
		exit(1);
	}
	syslog(LOG_INFO|LOG_DAEMON, "Test Daemon Process Start(%d)...\n", getpid());
	while(1) {
		sleep(5);
		syslog(LOG_INFO|LOG_DAEMON, "Test Daemon Process(%d)...\n", ++cnt);
	}
	return 0;
}

/* 
	syslog file will be on /var/log/syslog 
*/
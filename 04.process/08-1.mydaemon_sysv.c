#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <syslog.h>
#include <fcntl.h>
#include <stdlib.h>
#include <time.h>
#include <syslog.h>
#include <string.h>

int main(int argc, char * argv[]) {
	pid_t pid, sid;
	int fd, fd0, fd1, fd2;
	time_t now;
	const char daemonlog[]="/tmp/mydaemon.log";
	char *cmd;
	FILE *fp;
	
	if ((cmd = strrchr(argv[0], '/')) == NULL)
		cmd = argv[0];
	else
		cmd++;
		
	if((pid = fork()) != 0) {
		exit(0);					//parent exit and child continues
	}
	sid=setsid();

/*
	Under System V–based systems, some people recommend calling fork again at this point, 
	terminating the parent(child), and continuing the daemon in the child (grand-child).
	This guarantees that the daemon is not a session leader, which prevents it from 
	acquiring a controlling terminal under the System V rules
*/
	
	if((pid = fork()) != 0) {
		exit(0);					//parent(child) exits and child(grand-child) continues
	}
	
	umask(0022); 			
	if(chdir("/") !=0 ) {
		perror("chdir");
		exit(1);
	}
	
	close(STDIN_FILENO); close(STDOUT_FILENO); close(STDERR_FILENO);
	fd0=open("/dev/null", O_RDONLY); 		/* 0 = stdin */
	fd1=open("/dev/null", O_WRONLY); 		/* 1 = stdout */
	fd2=open("/dev/null", O_RDWR); 			/* 2 = stderr */
	
	openlog(cmd, LOG_CONS, LOG_DAEMON);
	if (fd0 != 0 || fd1 != 1 || fd2 != 2) {
		syslog(LOG_ERR, "file open error with FD0=%d FD1=%d FD2=%d", fd0, fd1, fd2);
		exit(1);
	}
	
#if 0	
	while(1) {
		sleep(5);
		time(&now);
		syslog(LOG_INFO|LOG_DAEMON, "Mydaemon Process alives at %s\n", ctime(&now));
	}
#else
	if ((fp = fopen(daemonlog, "w")) == NULL){
		perror("Can't open daemonlog");
		return 1;
	}
	while(1){
		time(&now);
		fprintf(fp, "Mydaemon alive at %s", ctime(&now));
		fflush(fp); /* flush the stream */
		sleep(5);
	}
#endif
	return 0;
}


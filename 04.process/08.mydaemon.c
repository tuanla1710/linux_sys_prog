#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <syslog.h>
#include <fcntl.h>
#include <stdlib.h>
#include <time.h>
#include <syslog.h>

int main(void) {
	pid_t pid, sid;
	int fd, fd0, fd1, fd2;
	time_t now;
	
	if((pid = fork()) != 0) {
		exit(0);					//parent exit
	}
	
	sid=setsid();
	
	umask(0022); 			
	if(chdir("/") !=0 ) {
		perror("chdir");
		exit(1);
	}
	
	close(STDIN_FILENO); close(STDOUT_FILENO); close(STDERR_FILENO);
	
	fd0=open("/dev/null", O_RDONLY); 		/* 0 = stdin */
	fd1=open("/dev/null", O_WRONLY); 		/* 1 = stdout */
	fd2=open("/dev/null", O_RDWR); 			/* 2 = stderr */
	
	openlog("08.mydaemon", LOG_CONS, LOG_DAEMON);
	if (fd0 != 0 || fd1 != 1 || fd2 != 2) {
		syslog(LOG_ERR, "file open error with FD0=%d FD1=%d FD2=%d", fd0, fd1, fd2);
		exit(1);
	}
	
#if 0	
	while(1) {
		sleep(5);
		time(&now);
		syslog(LOG_INFO|LOG_DAEMON, "Daemon Process alives at %s\n", ctime(&now));
	}
#else
	if((fd = open("/tmp/mydaemon.log", O_WRONLY | O_CREAT | O_APPEND, 0666)) == -1){
      perror("Can't open daemonlog");
      return 1;
	}
	dup2(fd, 1); dup2(fd, 2);
	while(1){
		/* get the current time and write it to the "daemonfile" that we opened above */
		time(&now);
		fprintf(stdout, "Mydaemon alive at %s", ctime(&now));
		fflush(stdout); /* flush the stream */
		sleep(5);
	}
#endif
	return 0;
}


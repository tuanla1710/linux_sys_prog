#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/unistd.h>
#include <syslog.h>

int main(void)
{
	pid_t pid;
	unsigned long cnt=0;

	if((pid = fork()) != 0) exit(0);		//parent exit
/* 
setsid() is giving the daemon a new process group and session, both of which
have it as leader. This also ensures that the process has no associated controlling
terminal (as the process just created a new session and will not assign one
*/
	setsid();
/*
chdir ("/")
This is done because the inherited working directory can be anywhere on the filesystem. 
Daemons tend to run for the duration of the system’s uptime, and you don’t want to keep 
some random directory open and thus prevent an administrator from unmounting the
filesystem containing that directory.

After executing daemon process, go to /proc/<pid>.
And then check cwd directory to see where the process is running
*/

/* redirect fd's 0,1,2 to /dev/null */
	open ("/dev/null", O_RDWR); /* stdin */
	dup (1); /* stdout */
	dup (2); /* stderror */
	
/* do its daemon thing... */

	if(chdir("/") !=0 ) {
		perror("chdir");
		exit(1);
	}

	syslog(LOG_INFO|LOG_DAEMON, "Test Daemon Process Start(%d)...\n", getpid());
	while(1) {
		sleep(1);
		syslog(LOG_INFO|LOG_DAEMON, "Test Daemon Process(%d)...\n", ++cnt);
	}

	return 0;
}
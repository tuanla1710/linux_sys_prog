#include <stdio.h>
#include <stdlib.h>
#include <sys/sysmacros.h>
#include <sys/stat.h>
#include <errno.h>
#include <time.h>
#include <string.h>

int main(int argc, char *argv[])
{
	struct stat buf;
	char *msg;
	int option;           		/* True if "-l" specified (i.e., use lstat) */
    int fname;                  /* Location of filename argument in argv[] */

    option = (argc > 1) && strcmp(argv[1], "-l") == 0; /* Simple parsing for "-l" */
    fname = option ? 2 : 1;
	
    if (fname >= argc || (argc > 1 && strcmp(argv[1], "--help") == 0))
        printf("%s [-l] file\n"
                "        -l option uses lstat() instead of stat()\n", argv[0]);

    if (option) {
        if (lstat(argv[fname], &buf) == -1)
            exit(1);
    } else {
        if (stat(argv[fname], &buf) == -1)
            exit(1);
    }
	
	if(S_ISREG(buf.st_mode)) msg = "regular file";
	else if(S_ISDIR(buf.st_mode)) msg = "directory";
	else if(S_ISCHR(buf.st_mode)) msg = "chracter special file";
	else if(S_ISBLK(buf.st_mode)) msg = "block special file";
	else if(S_ISFIFO(buf.st_mode)) msg = "pipe of FIFO";
	else if(S_ISLNK(buf.st_mode)) msg = "symbolic link";
	else if(S_ISSOCK(buf.st_mode)) msg = "socket";
	
	printf("\"%s\" is %s.\n", argv[fname], msg);
	printf("File Mode: %lo (octal)\n",(unsigned long)buf.st_mode);
	
	return 0;
}

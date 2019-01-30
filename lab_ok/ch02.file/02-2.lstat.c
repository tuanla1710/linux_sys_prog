#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <time.h>
#include <string.h>

#define STR_SIZE sizeof("rwxrwxrwx")

#define FP_SPECIAL 1

char *          /* Return ls(1)-style string for file permissions mask */
filePermStr(mode_t perm, int flags)
{
    static char str[STR_SIZE];

    /* If FP_SPECIAL was specified, we emulate the trickery of ls(1) in
       returning set-user-ID, set-group-ID, and sticky bit information in
       the user/group/other execute fields. This is made more complex by
       the fact that the case of the character displayed for this bits
       depends on whether the corresponding execute bit is on or off. */

    snprintf(str, STR_SIZE, "%c%c%c%c%c%c%c%c%c",
        (perm & S_IRUSR) ? 'r' : '-', (perm & S_IWUSR) ? 'w' : '-',
        (perm & S_IXUSR) ?
            (((perm & S_ISUID) && (flags & FP_SPECIAL)) ? 's' : 'x') :
            (((perm & S_ISUID) && (flags & FP_SPECIAL)) ? 'S' : '-'),
        (perm & S_IRGRP) ? 'r' : '-', (perm & S_IWGRP) ? 'w' : '-',
        (perm & S_IXGRP) ?
            (((perm & S_ISGID) && (flags & FP_SPECIAL)) ? 's' : 'x') :
            (((perm & S_ISGID) && (flags & FP_SPECIAL)) ? 'S' : '-'),
        (perm & S_IROTH) ? 'r' : '-', (perm & S_IWOTH) ? 'w' : '-',
        (perm & S_IXOTH) ?
            (((perm & S_ISVTX) && (flags & FP_SPECIAL)) ? 't' : 'x') :
            (((perm & S_ISVTX) && (flags & FP_SPECIAL)) ? 'T' : '-'));

    return str;
}


int main(int argc, char *argv[])
{
	struct stat sb;
	char *msg;
	int statLink;           /* True if "-l" specified (i.e., use lstat) */
    int fname;                  /* Location of filename argument in argv[] */

    statLink = (argc > 1) && strcmp(argv[1], "-l") == 0; /* Simple parsing for "-l" */
    fname = statLink ? 2 : 1;
	
    if (fname >= argc || (argc > 1 && strcmp(argv[1], "--help") == 0))
        printf("%s [-l] file\n"
                "        -l option uses lstat() instead of stat()\n", argv[0]);

    if (statLink) {
        if (lstat(argv[fname], &sb) == -1)
            exit(1);
    } else {
        if (stat(argv[fname], &sb) == -1)
            exit(1);
    }
	
	printf("File type:                ");
	
	if(S_ISREG(sb.st_mode)) msg = "regular file";
	else if(S_ISDIR(sb.st_mode)) msg = "directory";
	else if(S_ISCHR(sb.st_mode)) msg = "chracter special file";
	else if(S_ISBLK(sb.st_mode)) msg = "block special file";
	else if(S_ISFIFO(sb.st_mode)) msg = "pipe of FIFO";
	else if(S_ISLNK(sb.st_mode)) msg = "symbolic link";
	else if(S_ISSOCK(sb.st_mode)) msg = "socket";
	
	// printf("%s is %s.\n", argv[1], msg);
	printf("%s\n",msg);
	
	printf("Device containing i-node: major=%ld   minor=%ld\n",
                (long) major(sb.st_dev), (long) minor(sb.st_dev));

    printf("I-node number:            %ld\n", (long) sb.st_ino);
	
	printf("Mode:                     %lo (%s)\n",
            (unsigned long) sb.st_mode, filePermStr(sb.st_mode, 0));


    if (sb.st_mode & (S_ISUID | S_ISGID | S_ISVTX))
        printf("    special bits set:     %s%s%s\n",
                (sb.st_mode & S_ISUID) ? "set-UID " : "",
                (sb.st_mode & S_ISGID) ? "set-GID " : "",
                (sb.st_mode & S_ISVTX) ? "sticky " : "");

    printf("Number of (hard) links:   %ld\n", (long) sb.st_nlink);

    printf("Ownership:                UID=%ld   GID=%ld\n",
            (long) sb.st_uid, (long) sb.st_gid);

    if (S_ISCHR(sb.st_mode) || S_ISBLK(sb.st_mode))
        printf("Device number (st_rdev):  major=%ld; minor=%ld\n",
                (long) major(sb.st_rdev), (long) minor(sb.st_rdev));

    printf("File size:                %lld bytes\n", (long long) sb.st_size);
    printf("Optimal I/O block size:   %ld bytes\n", (long) sb.st_blksize);
    printf("512B blocks allocated:    %lld\n", (long long) sb.st_blocks);

    printf("Last file access:         %s", ctime(&sb.st_atime));
    printf("Last file modification:   %s", ctime(&sb.st_mtime));
    printf("Last status change:       %s", ctime(&sb.st_ctime));
		
	return 0;
}

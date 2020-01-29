#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]){
	char cmd_buf[256];
	int ret;
	
	if(argc !=2){
		fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
		exit(1);
	}
	
	printf("--------------system start--------------\n");
#if 0
	strcpy(cmd_buf, "ls -l ");
	strcat(cmd_buf, argv[1]);
#else
	strcpy(cmd_buf, "ps -f");
#endif
	ret = system(cmd_buf);
	printf("--------------system end-----------%d-----\n", ret);
	 
	return 0;
}
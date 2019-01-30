#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	int seconds;
	char line[128];
	char message[64];
	
	while(1) {
		printf("Alarm> ");
		if(fgets(line, sizeof(line), stdin) == NULL) exit(0);
		if(strlen(line) <= 1) continue;
		if(!strncmp(line, "exit", 4)) exit(0);
		
		if(sscanf(line, "%d %64[^\n]", &seconds, message) < 2) {
			fprintf(stderr, "Bad command\n");
		} else {
			sleep(seconds);
			printf("(%d) %s\n", seconds, message);
		}
	}
}

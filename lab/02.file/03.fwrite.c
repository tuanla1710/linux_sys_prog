#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
	char data[]="Welcome to Linux System Programming\nhello world\n";
	FILE *fp;
	int i;
	if((fp=fopen(argv[1], "w"))==NULL) {
		perror("fopen");
		exit(1);
	}
	if(fwrite(&data, sizeof(data), 1, fp) != 1) {
		perror("fwrite");
		fclose(fp);
		exit(2);
	}
	fclose(fp);
	return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char * argv[]){
	FILE *fp;
	int i;
	char data[128]={0,};	
	if((fp = fopen(argv[1], "r")) == NULL){
		perror("fopen");
		exit(1);
	}
	memset(data, 0, sizeof(data)); 
	while(feof(fp) == 0) {
		fread(data, sizeof(data),1, fp);
		// printf("%s\n", data);
		puts(data);
		memset(data, 0, sizeof(data));  
	}
	// printf("%s\n", data);
	fclose(fp);
	return 0;
					
}

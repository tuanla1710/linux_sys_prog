#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	int ret_val;   int  i;
	
	printf("File %s is : ", argv[1]);
	if((access (argv[1], F_OK)) != 0){
		printf("not exist\n");
		exit(1);
	}
		
	if((access(argv[1], R_OK)) == 0)
		printf("readable, ");
	else 
		printf("not readable, ");
	if((access(argv[1], W_OK)) == 0)
		printf("writable, ");
	else 
		printf("not writable, ");
	if((access(argv[1], X_OK)) == 0)
		printf("executable, ");
	else 
		printf("not executable, ");
	
	printf("\n");
}

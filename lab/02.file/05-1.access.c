#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
int main(int argc, char *argv[]) {
	int ret_val;   int  i;
	int mode_array[4] = {F_OK, R_OK, W_OK, X_OK};
	const char *mode_str[4] = {"existent", "readable", "writable", "executable"};
	const char *mode_err[4] = {"Existence check", "Readability check", 
							"Writability check", "Executability check"};
	if(argc == 1){
		printf("Usage : %s <pathname>\n", argv[0]);
		exit(1);
	}
	printf("File %s : \n", argv[1]);
	for(i=0; i<4; i++) {
		ret_val = access(argv[1], mode_array[i]);
		if(ret_val == 0) {
			printf("%s \n", mode_str[i]);
		} else if(ret_val == -1) {
			perror(mode_err[i]);
		}	
	}
	printf("\n");
}


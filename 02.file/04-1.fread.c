#include <stdio.h>
#include <stdlib.h>

typedef struct INFO {
	char	name[20];
	int		age;
	float	height;
} INFO;

#define DATA_SIZE	5

int main(int argc, char * argv[]){
	FILE *fp;
	
	// INFO *data;					/* first if is 1 and second if is 1 */
	INFO data;					/* first if is 1 and sedond if is 0 */
	// INFO data[DATA_SIZE];		/* first if is 0 */
	
	if((fp = fopen(argv[1], "rb")) == NULL){
		perror("fopen");
		exit(1);
	}
#if 1
#if 0	
	while(1) {
		data=malloc(sizeof(INFO));
		fread(data, sizeof(INFO), 1, fp);
		if(feof(fp)){
			break;
		}
		printf("name:%s, age:%d, height:%.1f\n", data->name, data->age, data->height);
	}
#else
	while(1) {
		fread(&data, sizeof(INFO), 1, fp);
		if(feof(fp)){
			break;
		}
		printf("name:%s, age:%d, height:%.1f\n", data.name, data.age, data.height);
	}
#endif
#else
	for(int i=0; i<sizeof(data)/sizeof(INFO); i++){
		fread(data, sizeof(INFO), 1, fp);
		printf("name:%s, age:%d, height:%.1f\n", data->name, data->age, data->height);
	}
#endif
	fclose(fp);
	return 0;
					
}

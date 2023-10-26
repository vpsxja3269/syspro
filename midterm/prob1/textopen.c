#include <stdio.h>
#define MAX_LENGTH 128

int main(){
	int num = 1;
	int num_2 = 2;
	int line_count = 0;
	char buffer[MAX_LENGTH];
	FILE *p_file = NULL;

	p_file = fopen("data.txt", "rt");
	if(p_file != NULL) {
		while (fgets(buffer, MAX_LENGTH, p_file) != NULL){
			line_count++;
		
			if(line_count == num ){
				printf("%s", buffer);
			}

			if(line_count == num_2){
				printf("%s", buffer);
				break;
			}
		}
		fclose(p_file);
	}
	return 0;
}

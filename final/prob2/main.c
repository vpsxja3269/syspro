#include <stdio.h>
#include <signal.h>
#include <sys/types.h>

int main(){
	int pid[8], i = 0;

	for(i = 0 ; i < 4 ; i++){
		pid[i] = fork();
		
		if(pid[i] == 0){
			printf("Helol\n");
			exit(0);
		}
	}
	for(i = 3 ; i < 5 ; i++){
		pid[i] = fork();
		if(pid[i] == 0){
			printf("Hello\n");
                        exit(0);
                }
        }
	for(i = 4 ; i < 6 ; i++){
		pid[i] = fork();
		if(pid[i] == 0){
			printf("Hello\n");
			exit(0);
		}
	}
		
    	return 0;
}

#include <stdio.h>
#include <stdlib.h>

int main(){
	int pid1, pid2;
	pid1 = fork();
	if(pid1 == 0){
		printf("[Child 1] : Helol, world pid = %d\n", getpid());
		exit(0);
	}
	pid2 = fork();
	if(pid2 == 0){
		printf("[Child 2] : Helol, world pid = %d\n", getpid());
		exit(0);
	}
	printf("[PARENT] : Helol, world pid = %d\n", getpid());
}

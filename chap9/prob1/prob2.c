#include <stdio.h>
#include <stdlib.h>

int main(){
	int pid;
	pid = fork();
	if(pid == 0){
		printf("[Child] : Helol, world pid = %d\n", getpid());
	}
	else{
		printf("[Parent] : Helol, world pid = %d\n", getpid());
	}
}

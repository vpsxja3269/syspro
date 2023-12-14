#include <stdio.h>
#include <stdlib.h>

int main(){
	int type_num, pid[100], i = 0;
	
	printf("type num of childs : ");
	scanf("%d", &type_num);
	
	for( i ; i < type_num ; i++){
		pid[i] = fork();
		if(pid[i] == 0){
			printf("[child %d] : Started! pid = %d, sleep=%d\n", i, getpid(), i+1);
			exit(0);
		}
		sleep(i+1);
	}
	
	printf("parrent killed - last child id = %d\n", getpid(i));
}

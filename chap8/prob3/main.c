#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
	char *ptr;

	ptr = getenv("home");
	printf("SHELL = %s \n", ptr);

	ptr = getenv("SHELL");
	printf("SHELL = %s \n", ptr);

	ptr = getenv("PATH");
	printf("PATH = %s \n", ptr);

	exit(0);
}

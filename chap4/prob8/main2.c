#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    FILE *fp;

    if (!strcmp(argv[1], "stdin")) {
        fp = stdin;
        printf("Enter one letter:");
        if (getchar() == EOF) perror("getchar");
    } else if (!strcmp(argv[1], "stdout")) {
        fp = stdout;
        printf("Stream = %s, ", argv[1]);
        
        if (setvbuf(fp, NULL, _IOFBF, 512) == 0) {
            printf("Fully buffered");
        } else {
            perror("setvbuf");
            exit(1);
        }
        
        printf(", Buffer size = %d\n", 512);
    } else if (!strcmp(argv[1], "stderr")) {
        fp = stderr;
        printf("Stream = %s, ", argv[1]);
        
        if (setvbuf(fp, NULL, _IOFBF, 512) == 0) {
            printf("Fully buffered");
        } else {
            perror("setvbuf");
            exit(1);
        }
        
        printf(", Buffer size = %d\n", 512);
    } else if ((fp = fopen(argv[1], "r")) == NULL) {
        perror("fopen");
        exit(1);
    } else if (getc(fp) == EOF) perror("getc");

    exit(0);
}

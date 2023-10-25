#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    FILE *fp;
    int c;
    int line_number = 1; 

    if (argc < 2) {
        fprintf(stderr, "Usage: %s [OPTION] [FILE]...\n", argv[0]);
        return 1;
    }

    
    int opt = 0;
    if (argc >= 3 && argv[1][0] == '-') {
        if (argv[1][1] == 'n') {
            opt = 1;
            argc--;
            argv++;
        }
    }

    for (int i = 1; i < argc; i++) {
        fp = fopen(argv[i], "r");

        if (fp == NULL) {
            fprintf(stderr, "Error opening file: %s\n", argv[i]);
            return 2;
        }

        c = getc(fp);
        if (opt) {
            printf("%4d  ", line_number);
        }

        while (c != EOF) {
            putc(c, stdout);
            if (c == '\n' && opt) {
                line_number++;
                printf("%4d  ", line_number);
            }
            c = getc(fp);
        }

        fclose(fp);
    }

    return 0;
}

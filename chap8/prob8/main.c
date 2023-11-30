#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

extern char **environ;

int main(int argc, char *argv[]) {
    char **ptr;

    for (int i = 1; i < argc; i++) {
        if (argv[i][0] == '-' && argv[i][1] == 'e') {
            
            if (argv[i + 1] != NULL && argv[i + 1][0] != '-') {
                char *env_value = getenv(argv[i + 1]);
                if (env_value != NULL) {
                    printf("%s=%s\n", argv[i + 1], env_value);
                }
                i++;
            } else {
                for (ptr = environ; *ptr != 0; ptr++)
                    printf("%s \n", *ptr);
            }
        } else {
            switch (argv[i][1]) {
                case 'u':
                    printf("실제 사용자 ID: %d\n", getuid());
                    printf("유효 사용자 ID: %d\n", geteuid());
                    break;
                case 'g':
                    printf("실제 그룹 ID: %d\n", getgid());
                    printf("유효 그룹 ID: %d\n", getegid());
                    break;
                case 'i':
                    printf("프로세스 ID: %d\n", getpid());
                    break;
                case 'p':
                    printf("부모 프로세스 ID: %d\n", getppid());
                    break;
            }
        }
    }

    return 0;
}

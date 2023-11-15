#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <time.h>
#include <grp.h>
#include <pwd.h>
#include <string.h>

char type(mode_t);
char *perm(mode_t);
void printStat(char *, char *, struct stat *);

/* 디렉터리 내용을 자세히 리스트한다. */
int main(int argc, char **argv)
{
    DIR *dp;
    char *dir;
    struct stat st;
    struct dirent *d;
    char path[BUFSIZ + 1];

    if (argc == 1)
        dir = ".";
    else
        dir = argv[1];

    if ((dp = opendir(dir)) == NULL) // 디렉터리 열기
        perror(dir);

    while ((d = readdir(dp)) != NULL)
    { // 디렉터리의 각 파일에 대해
        sprintf(path, "%s/%s", dir, d->d_name); // 파일경로명 만들기
        if (lstat(path, &st) < 0)                 // 파일 상태 정보 가져오기
            perror(path);
        else
            printStat(path, d->d_name, &st); // 상태 정보 출력
    }

    closedir(dp);
    exit(0);
}

/* 파일 상태 정보를 출력 */
void printStat(char *pathname, char *file, struct stat *st)
{
    printf("%5ld ", st->st_blocks);                   // 수정: st_blocks는 long 형이므로 %ld 사용
    printf("%c%s ", type(st->st_mode), perm(st->st_mode));
    printf("%3ld ", (long)st->st_nlink);              // 수정: st_nlink는 long 형이므로 %ld 사용
    printf("%s %s ", getpwuid(st->st_uid)->pw_name, getgrgid(st->st_gid)->gr_name);
    printf("%9ld ", st->st_size);                     // 수정: st_size는 long 형이므로 %ld 사용
    char time_str[20];
    strftime(time_str, sizeof(time_str), "%b %d %H:%M", localtime(&st->st_mtime)); // 수정: ctime을 strftime로 변경
    printf("%s ", time_str);
    printf("%s\n", file);
}

/* 파일 타입을 반환 */
char type(mode_t mode)
{
    if (S_ISREG(mode))
        return ('-');
    else if (S_ISDIR(mode))
        return ('d');
    else if (S_ISCHR(mode))
        return ('c');
    else if (S_ISBLK(mode))
        return ('b');
    else if (S_ISLNK(mode))
        return ('l');
    else if (S_ISFIFO(mode))
        return ('p');
    else if (S_ISSOCK(mode))
        return ('s');
    else
        return ('?'); // 수정: 정의되지 않은 파일 타입에 대한 처리
}

/* 파일 접근권한을 반환 */
char *perm(mode_t mode)
{
    static char perms[11]; // 수정: 배열 크기 변경
    strcpy(perms, "---------");

    for (int i = 0; i < 3; i++)
    {
        if (mode & (S_IRUSR >> i * 3))
            perms[i * 3] = 'r';
        if (mode & (S_IWUSR >> i * 3))
            perms[i * 3 + 1] = 'w';
        if (mode & (S_IXUSR >> i * 3))
            perms[i * 3 + 2] = 'x';
    }
    return (perms);
}

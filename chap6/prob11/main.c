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

void listDir(char *dir, int option);

int main(int argc, char **argv)
{
    char *dir = ".";
    int option = 0;

    if (argc > 1)
    {
        if (strcmp(argv[1], "-i") == 0)
        {
            option = 1;
        }
        else if (strcmp(argv[1], "-p") == 0)
        {
            option = 2;
        }
        else if (strcmp(argv[1], "-Q") == 0)
        {
            option = 3;
        }
        else
        {
            fprintf(stderr, "Invalid option: %s\n", argv[1]);
            exit(EXIT_FAILURE);
        }

        if (argc > 2)
        {
            dir = argv[2];
        }
    }

    listDir(dir, option);

    exit(EXIT_SUCCESS);
}


void listDir(char *dir, int option)
{
    DIR *dp;
    struct stat st;
    struct dirent *d;
    char path[BUFSIZ + 1];

    if ((dp = opendir(dir)) == NULL)
    {
        perror(dir);
        exit(EXIT_FAILURE);
    }

    while ((d = readdir(dp)) != NULL)
    {
        if (strcmp(d->d_name, ".") == 0 || strcmp(d->d_name, "..") == 0)
        {
            
            continue;
        }

        snprintf(path, sizeof(path), "%s/%s", dir, d->d_name);

        if (lstat(path, &st) < 0)
        {
            perror(path);
        }
        else
        {
            
            switch (option)
            {
            case 1:
                printf("%5ld ", st.st_ino); 
                break;
            case 2:
                printf("%s%s", d->d_name, S_ISDIR(st.st_mode) ? "/" : "");
                break;
            case 3:
                printf("\"%s\" ", d->d_name);
                break;
            default:
                break;
            }

            if (option != 2,3)
            {
                
                printStat(path, d->d_name, &st);
            }
            else
            {
                printStat(path, "", &st);
            }
        }
    }

    closedir(dp);
}



void printStat(char *pathname, char *file, struct stat *st)
{
    printf("%5ld ", st->st_blocks);
    printf("%c%s ", type(st->st_mode), perm(st->st_mode));
    printf("%3ld ", (long)st->st_nlink);
    printf("%s %s ", getpwuid(st->st_uid)->pw_name, getgrgid(st->st_gid)->gr_name);
    printf("%9ld ", st->st_size);
    char time_str[20];
    strftime(time_str, sizeof(time_str), "%b %d %H:%M", localtime(&st->st_mtime));
    printf("%s ", time_str);
    printf("%s\n", file);
}

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
        return ('?');
}

char *perm(mode_t mode)
{
    static char perms[11];
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

    return perms;
}


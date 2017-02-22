#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <errno.h>
#include <string.h>
#include "fsctlib.h"
#include "fsctchecks.h"
#include "fsctstack.h"


int isadir(char* name)
{
    struct stat info;
    return (stat(name, &info) != -1 && (info.st_mode & S_IFMT) == S_IFDIR);
}

void print_usage() 
{
    printf("Usage: filename [--maxdepth num][--pathmax num]"
           "[--badchars str][--nocasesens]\n");
}

long atoi_safe(char* str) 
{
    char* endptr = NULL;
    long ret = 0;
    errno = 0;
    ret = strtol(str, &endptr, 10);
    if (endptr == str) {
        fprintf(stderr, "Not a digit.\n");
        exit(1);
    }
    return ret;
}

void fsct_dfs(char* filename, int maxdepth, int maxchars, char* badchars)
{
    DIR* dirp;
    struct dirent* direntp;
    dirp = opendir(filename);

    if (dirp == NULL) {
        fprintf(stderr, "cannot open a directory\n");
        exit(1);
    }

    while ((direntp = readdir(dirp)) != NULL) {
        struct stat info;
        struct check* checks;
         
        checks = make_checks(direntp->d_name, badchars);
        /*printf("NEWFILE\n");
        printf("depth: %d\n", checks->depth > maxdepth);
        printf("mchar: %d max: %d\n", checks->num_char, maxchars);
        printf("badchar: %d\n", checks->bad_char);
        */
        lstat(direntp->d_name, &info);

        
        if ((maxdepth < 0? 0:checks->depth > maxdepth) 
            || (maxchars < 0? 0:checks->num_char > maxchars) 
            || (badchars < 0? 0:checks->bad_char == 1)) { //include case sens check

            char *cwdbuf;
            cwdbuf = malloc(sizeof(char)*100);

            char *pathp;
            
            if ((pathp = getcwd(cwdbuf, sizeof(char)*100)) == NULL) {
                fprintf(stderr, "Cant get current working directory.\n");
                free(cwdbuf);
                exit(1);
            }

            size_t pathlen = strlen(pathp);
            size_t flen = strlen(direntp->d_name);
            int arr_size = (pathlen + flen);
            char rets[arr_size+2];              /*+1 for '\0', +1 for '/'*/
            strconcat(pathp, direntp->d_name, rets, arr_size);               

            if (S_ISREG(info.st_mode)) {
                printf("%s\n", rets);
            }
            
            if (S_ISDIR(info.st_mode)) {
                add_dir(rets);
            }                        
            free(cwdbuf);

        }
        free(checks);
    }
    print_dir();
    closedir(dirp);
}

void strconcat(char* path, char* fname, char* rets, int arr_size) 
{
    int i = 0;
    int path_len = strlen(path);
    for (i = 0; i < path_len; i++) 
        rets[i] = path[i];

    rets[path_len] = '/';
    rets[path_len+1] = '\0';

    strcat(rets, fname);
}


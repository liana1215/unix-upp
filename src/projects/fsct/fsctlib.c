#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <errno.h>
#include "fsctlib.h"
#include "fsctchecks.h"

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
        printf("NEWFILE\n");
        printf("depth: %d\n", checks->depth > maxdepth);
        printf("mchar: %d max: %d\n", checks->num_char, maxchars);
        printf("badchar: %d\n", checks->bad_char);

        lstat(direntp->d_name, &info);

        
        if (S_ISREG(info.st_mode)) {
            if ((maxdepth < 0? 0:checks->depth > maxdepth) 
                || (maxchars < 0? 0:checks->num_char > maxchars) 
                || (badchars < 0? 0:checks->bad_char == 1)) { //include case sens check
                //get pwd
                //concat with direntp->d_name
                //print string
                char *cwdbuf;
                cwdbuf = malloc(sizeof(char)*100);

                char *pathp;
                pathp = getcwd(cwdbuf, sizeof(char)*100);
                printf("BAD filename: %s\n ", direntp->d_name);
                printf("cwd: %s\n ", pathp);
                free(cwdbuf);
            }
        } else {
        //S_ISDIR() to check if directory, if so add to stack
        //TODO: create stack structure to hold dir, need to figure out what
        //information to store, inode? file name? path to file?
            printf("notreg file: %s\n", direntp->d_name);
        }
    }
    closedir(dirp);
}

    //check each file/dir in parent dir.
        //for each file, call check()
            //if dir and check() is ok then add dir to stack(data structure)
        //once checked all files in current dir, then pop dir off stack and
        //start again.

    //store inode and dev_id in struct



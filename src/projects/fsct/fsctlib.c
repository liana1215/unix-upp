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


#define _XOPEN_SOURCE

void print_usage() 
{
    printf("Usage: filename [--maxdepth num][--pathmax num]"
           "[--badchars str][--nocasesens]\n");
}

long atoi_safe(const char* str) 
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

void fsct_dfs(char* dirname, int maxdepth, int maxchars, char* badchars)
{
    DIR* dirp;
    struct dirent* direntp;
    dirp = opendir(dirname);

    if (dirp == NULL) {
        fprintf(stderr, "Cannot open a directory %s: %s\n",
                dirname, strerror(errno));
        exit(1);
    }

    /*indicator for if dir found*/
    int nodir = 0; 

    while ((direntp = readdir(dirp)) != NULL) {
        struct stat info;
        lstat(direntp->d_name, &info);
               
        char* retsp = strconcat(dirname, direntp->d_name);               

        /*create tmp for consumption by make_checks*/
        char* tmp = malloc(strlen(retsp)+1); 
        strcpy(tmp, retsp);

        struct check* checks = {0};
        checks = make_checks(tmp, badchars);

        if ((maxdepth < 0? 0:checks->depth > maxdepth) 
            || (maxchars < 0? 0:checks->num_char > maxchars) 
            || (badchars < 0? 0:checks->bad_char == 1)) { //include case sens check
            fprintf(stdout, "%s/%s\n", dirname, direntp->d_name);
        }
 
        if (direntp->d_type & DT_DIR) {
            if ((strcmp(direntp->d_name, ".") != 0)
            && (strcmp(direntp->d_name, "..") != 0)) {
            add_dir(retsp, dirname, direntp->d_name);
            nodir = 1;
            }
        }                        
        free(retsp);
        free(tmp);
        free(checks);
    }
    closedir(dirp);

    treenode_t* dirinfo;
    dirinfo = pop_dir();
    if ((dirinfo->dirpath != NULL)) {
        char path[1024];
        if (nodir != 1) {
            strcpy(path, dirinfo->fullpath);
        } else {
            strcpy(path, dirinfo->dirpath);
        }

        if (chdir(path) != 0) {
            fprintf(stderr, "Could not change to %s: %s.\n", 
                    dirinfo->fullpath, strerror(errno));
            exit(1);
        }
        fsct_dfs(dirinfo->fullpath, maxdepth, maxchars, badchars);
    }
    free(dirinfo);
}

char* strconcat(const char* path, const char* fname) 
{
    char* newpath = malloc(strlen(path)+strlen(fname)+2);
    strcpy(newpath, path);
    strcat(newpath, "/");
    strcat(newpath, fname);
    return newpath;
}


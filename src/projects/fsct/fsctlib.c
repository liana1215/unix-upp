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
int dirclosed = 0;

void print_usage() 
{
    printf("Usage: filename [-maxdepth num][-pathmax num]"
           "[-badchars str][-nocasesens]\n");
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

void opendir_check(DIR* dirp, char* dirname)
{
    if (dirp == NULL) {
        fprintf(stderr, "Cannot open a directory %s: %s\n",
                dirname, strerror(errno));
        exit(1);
    }
}

int dname_check(struct dirent* direntp)
{
    return ((strcmp(direntp->d_name, ".") != 0)
            && (strcmp(direntp->d_name, "..") != 0)
            && (direntp->d_name[0] != '.'))?1:0;
}

int path_checks(struct check* cks, int maxd, int maxc, char* badc)
{
    return ((maxd < 0?0:cks->depth > maxd)
        || (maxc < 0?0:cks->num_char > maxc) 
        || (badc == NULL?0:cks->bad_char == 1))?1:0;
}

void fsct_dfs(char* dirname, char* badc, int maxd, int maxc, int nocasesens)
{
    DIR* dirp;
    struct dirent* direntp;
    dirp = opendir(dirname);
    opendir_check(dirp, dirname);
    init_node();
    while ((direntp = readdir(dirp)) != NULL) {
        struct stat info;
        int ret = 0;

        if((ret = lstat(dirname, &info))==-1) 
            fprintf(stderr, "lstat err at %s: %s\n", dirname, strerror(errno));
                
        if (dirclosed) {
            dirclosed = 0;        
            init_node();
        }

        add_node(direntp->d_name);        
        char* retsp = strconcat(dirname, direntp->d_name);               
        char* tmp = malloc(strlen(retsp)+1); 
        struct check* checks = {0};
        strcpy(tmp, retsp);
        checks = make_checks(tmp, badc);

        if (dname_check(direntp)) {
            if (path_checks(checks, maxd, maxc, badc))
                fprintf(stdout, "%s/%s\n", dirname, direntp->d_name);
            
            char* found = find_node(direntp->d_name);   
            if (found != NULL && (nocasesens == 1)) { 
                fprintf(stdout, "%s/%s\n", dirname, direntp->d_name);
                fprintf(stdout, "%s/%s\n", dirname, found);
            }
            if (direntp->d_type & DT_DIR) 
                fsct_dfs(retsp, badc, maxd, maxc, nocasesens);
        }
        free(retsp);
        free(tmp);
        free(checks);
    }   

    clear_node();
    closedir(dirp);
    dirclosed = 1;
}

char* strconcat(const char* path, const char* fname) 
{
    char* newpath = malloc(strlen(path)+strlen(fname)+2);
    strcpy(newpath, path);
    strcat(newpath, "/");
    strcat(newpath, fname);
    return newpath;
}

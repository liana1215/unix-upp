/**
 * fsctlib.c - main library housing utility functions and algorithm to search
 * the directory tree.
 * date: 3/2/2017
 * author: surfertas
 */
#define _BSD_SOURCE
#include "fsctlib.h"
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


static int dirclosed = 0;

/* Prints the usage details to the command line */
void print_usage() 
{
    printf("Usage: filename [-maxdepth num][-pathmax num]"
           "[-badchars str][-nocasesens]\n");
}

/* Prints out an error message if not a integer, and returns -1
 * @arg: str - string to check and convert to integer. 
 * @ret: ret - returns long integer, or -1 if not a digit.
*/
long atoi_safe(const char* str) 
{
    char* endptr = NULL;
    long ret = 0;
    errno = 0;
    ret = strtol(str, &endptr, 10);
    if (*str == '\0' || *endptr != '\0') {
        fprintf(stderr, "Not a numeric character: %c\n", *endptr);
        return -1;
    }
    return ret;
}

/* Checks if directory was successfully opened.
 * @arg: dirp - pointer to DIR object.
 * @arg: dirname - name of directory.
 */
void opendir_check(DIR* dirp, char* dirname)
{
    if (dirp == NULL) {
        fprintf(stderr, "Cannot open a directory %s: %s\n",
                dirname, strerror(errno));
        exit(1); //TODO: should not exit, should keep going, need to fix.
    }
}

/* Checks directory name for symbolic link.
 * @arg: direntp - a pointer to dirent struct.
 * @ret: returns 1 if symbolic link, else 0.
 */
int dname_check(struct dirent* direntp)
{
    return ((strcmp(direntp->d_name, ".") != 0)
            && (strcmp(direntp->d_name, "..") != 0));
}

/* Checks path if passes criteria defined by max path, max number of chars and
 * bad chars.
 * @arg: cks - pointer to check struct defined in fsctchecks.h.
 * @arg: maxd - max depth criteria.
 * @arg: maxc - max number of characters allowed.
 * @arg: badc - a string of bad chars.
 * @ret: returns 1 if path name doesnt meet criteria.
 */
int path_checks(struct check* cks, int maxd, int maxc, char* badc)
{
    return ((maxd >= 0 && cks->depth > maxd)
        || (maxc >= 0 && cks->num_char > maxc) 
        || (badc && cks->bad_char));
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

/* Combines path name with file name, with "/" in between.
 * @arg: path - name of path.
 * @arg: fname - file name.
 * @ret: newpath - concat string: pathname + / + filename.
 */
char* strconcat(const char* path, const char* fname) 
{
    char* newpath = malloc(strlen(path)+strlen(fname)+2);
    strcpy(newpath, path);
    strcat(newpath, "/");
    strcat(newpath, fname);
    return newpath;
}

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include "fsctlib.h"


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

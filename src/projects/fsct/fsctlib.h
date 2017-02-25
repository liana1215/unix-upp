#ifndef FSCTLIB_H
#define FSCTLIB_H

#include <dirent.h>

void print_usage();
long atoi_safe(const char*);
void opendir_check(DIR*, char*);
void fsct_dfs(char*, char*, int, int, int);
char* strconcat(const char*, const char*);

#endif

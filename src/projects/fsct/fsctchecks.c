#include <stdio.h>
#include <string.h>
#include "fsctchecks.h"


struct check* make_checks(char* name) 
{
    struct check* checks = {0};
    const char* delim = "/";
    char* token;
    int depth_count = 0;
    int char_count = 0;
    
    
    token = strtok(name, delim);

    while (token != NULL) {
        char_count += strlen(token);
        depth_count += 1;
        token = strtok(NULL, delim);
    }
    checks->depth = depth_count;
    checks->num_char = char_count;

    return checks; 
}
    
    


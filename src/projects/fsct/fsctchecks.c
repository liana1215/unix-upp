#include <stdio.h>
#include <string.h>
#include "fsctchecks.h"


struct check* make_checks(char* name, char* badchars) 
{
    struct check* checks = {0};
    checks = malloc(sizeof(checks)); //TODO: need to be freed

    const char* delim = "/";
    char* token;
    int depth_count = 0;
    int char_count = 0;
    int char_found = 0; 

    token = strtok(name, delim);
    while (token != NULL) {
        char_count += strlen(token) + 1;
        depth_count += 1;

        if (badchars != NULL) {
            char* ptr = token;          
            while (*ptr) {
                if (check_badchar(*ptr, badchars)) {
                    char_found = 1;
                    break;
                }
                ptr++;
            }
        } 
  
        token = strtok(NULL, delim);
    }
    checks->depth = depth_count;
    checks->num_char = char_count;
    checks->bad_char = char_found;
    return checks; 
}

int check_badchar(char c, char* badchars) 
{
    char* ptr = badchars;
    while (*ptr) {
        if (*ptr == c) {
            return 1;
        }
        ptr++;
    }
    return 0;    
}

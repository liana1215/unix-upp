/**
 * fsctchecks.c defines the function used to check for bad chars, and also is a
 * helper function to calculate the depth of a given path, and number of
 * characters found.
 * date: 2/28/2017
 * author: surfertas
 */
#include "fsctchecks.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * make_checks() takes in the path name, and string of bad chars and checks the
 * path against bad chars, while also calculating the depth and number of
 * characters found in the path.
 * @arg: name - Full path name.
 * @arg: badchars - String of bad chars specified by caller.
 * @ret: checks - A pointer to struct check.
 *
 * Note: strtok() called on name, and destructive as a side effect.
 */
struct check* make_checks(char* name, char* badchars) 
{
    struct check* checks = malloc(sizeof(struct check));
    if (checks == NULL) {
        perror("Failed as malloc of checks.\n");
        exit(1);
    }

    const char* delim = "/";
    char* token;
    int depth_count = 0;
    int char_count = 0;
    int char_found = 0; 

    token = strtok(name, delim);
    while (token != NULL) {
        char_count += strlen(token);
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
    checks->num_char = char_count + depth_count - 1;
    checks->bad_char = char_found;
    return checks; 
}

int check_badchar(char c, char* badchars) 
/* A helper function to check if c is in badchars.
 * @arg: c - a char found in path to be checked.
 * @arg: badchars - string of bad chars 
 */
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

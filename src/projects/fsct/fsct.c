/**
 * fsct.c is the main file of a program the outputs directories and files that
 * do not meet certain criteria passed to the program as arguments. The criteria
 * that the program optionally checks for includes maximum depth of path, the
 * maximum number of characters, characters defined under ASCII that are deemed
 * "bad", and for case related name clashes.
 * date: 2/28/2017
 * author: surfertas
 */
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <errno.h>
#include "fsctchecks.h"
#include "fsctlib.h"
#include "fsctstack.h"

int main(int argc, char** argv)
{
    int opt = 0;
    int maxdepth = -1;      /* -1 if not in args, else max path depth */
    int maxchars = -1;      /* -1 if not in args, else max # of chars */
    int nocasesens = 0;     /* 0 if case sensitivity is not turned on */
    char* badchars = NULL;  /* chars not allowed, NULL if not specified */
    char* file = NULL;

    if (argc < 2) {
        print_usage();
        exit(1);
    } 
    
    file = argv[1];
    
    int opt_ind = 0;
    static struct option long_option[] = {
        {"maxdepth", required_argument, 0, 'm'},
        {"pathmax", required_argument, 0, 'p'},
        {"badchars", required_argument, 0, 'b'},
        {"nocasesens", no_argument, 0, 'n'}
    };

    while ((opt = getopt_long_only(argc, argv, "m:p:b:n",
                long_option, &opt_ind)) != -1) {
        switch(opt) {
            case 'm': 
                if ((maxdepth = atoi_safe(optarg)) < 1) {
                    print_usage(); 
                    exit(EXIT_FAILURE);
                }
                break;
            case 'p': maxchars = atoi_safe(optarg);
                break;
            case 'b': badchars = optarg;
                break;
            case 'n': nocasesens = 1;
                break;
            case '?': 
                print_usage();
                exit(EXIT_FAILURE);
            default:
                break;
        }
    }
    
    fsct_dfs(file, badchars, maxdepth, maxchars, nocasesens);

    return 0;
}

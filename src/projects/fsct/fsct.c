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
    int max_depth = -1;
    int max_chars = -1;
    int nocases = -1;
    char* badchars = NULL;
    char* file = NULL;


    if (argc < 2) {
        print_usage();
        exit(1);
    } else {
        file = argv[1];
    }

    int opt_ind = 0;
    static struct option long_option[] = {
        {"maxdepth", required_argument, 0, 'm'},
        {"pathmax", required_argument, 0, 'p'},
        {"badchars", required_argument, 0, 'b'},
        {"nocasesens", no_argument, 0, 'n'}
    };

    while ((opt = getopt_long(argc, argv, "m:p:b:n:",
                long_option, &opt_ind)) != -1) {
        switch(opt) {
            case 'm': max_depth = atoi_safe(optarg); 
                break;
            case 'p': max_chars = atoi_safe(optarg);
                break;
            case 'b': badchars = optarg;
                break;
            case 'n': nocases = 1;
                break;
            case '?': print_usage();
                exit(1);
            default:
                break;
        }
    }
    
    init_stack();
    fsct_dfs(file, max_depth, max_chars, badchars);
    return 0;
}

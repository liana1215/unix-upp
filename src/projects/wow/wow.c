#include    <stdio.h>
#include    <unistd.h>
#include    <sys/types.h>
#include    <utmp.h>
#include    <fcntl.h>
#include    <stdlib.h>
#include    <assert.h>

#include    "utmplib.h" 
#include    "utmpsearch.h"

/*
 *  bwow version 1.0     - read /etc/utmp and lists logins for specified date
 *                       - uses binary search 
 */

#define USAGE "usage: [-f] input_file year month day [-s|-b]\n"

int main(int argc, char **argv)
{
    char* f_name = UTMP_FILE;
    int opt = 0; 
    int year = 0;
    int month = 0;
    int day = 0;
    int seq_bin = 0;

    while ((opt = getopt(argc, argv, "f:sb")) != -1) {
        switch (opt) {
            case 'f':
                f_name = optarg;
                break;
            case 's':
                seq_bin = 1;
                break;
            case 'b':
                seq_bin = 0;                
                break;
            case '?':
                fprintf(stderr, USAGE);
                exit(1);
                break;
            default:    
                break;
        }
    } 
        
    if (optind == argc) {optind = 1;} 

    assert(argc > 3 && "usage: [-f] input_file year month day [-s|-b]\n");
    year = atoi(argv[optind++]) - 1900;
    month = atoi(argv[optind++]) - 1;
    day = atoi(argv[optind++]);     

    if (!seq_bin) {
        FILE *fp;
        
        fp = fopen(f_name, "r");
        if (fp == NULL) {
            fprintf(stderr,"%s: cannot open %s\n", *argv, f_name);
            exit(1);
        } 
        
        int fsize = utmp_fsize(f_name);
        fetch_bsearch(year, month, day, fsize, fp);
    } else {
        if (utmp_open(f_name) == -1 ) {
            fprintf(stderr,"%s: cannot open %s\n", *argv, f_name);
            exit(1);
        }
        fetch_sequential(year, month, day);
    }
    utmp_close();
    return 0;
}

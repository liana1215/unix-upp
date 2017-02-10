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


int main(int argc, char **argv)
{
    char* f_name = UTMP_FILE;
    int opt = 0; 
    int year = 0;
    int month = 0;
    int day = 0;

    while ((opt = getopt(argc, argv, "f:")) != -1) {
        switch (opt) {
            case 'f':
                f_name = optarg;
                break;
            case '?':
                fprintf(stderr, "usage: [-f] input_file year month day\n");
                exit(1);
                break;
            default:    
                break;
        }
    } 
        
    if (optind == argc) {optind = 1;} 

    assert(argc > 3 && "usage: [-f] input_file year month day\n");
    year = atoi(argv[optind++]) - 1900;
    month = atoi(argv[optind++]) - 1;
    day = atoi(argv[optind++]);     
    
    FILE *fp;
    
    fp = fopen(f_name, "r");
    if (fp == NULL) {
        fprintf(stderr,"%s: cannot open %s\n", *argv, f_name);
        exit(1);
    } 
    
    printf("OK\n");
    int fsize = utmp_fsize(f_name);
    printf("size OK\n");
    
    fetch_bsearch(year, month, day, fsize, fp);
    utmp_close();
   
    return 0;
}

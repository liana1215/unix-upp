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
 *  swow version 1.0     - read /etc/utmp and lists logins for specified date
 */

int main(int argc, char **argv)
{
    char* f_name = UTMP_FILE;
    char date[100];
    int opt = 0; 

    while ((opt = getopt(argc, argv, "f:")) != -1) {
        switch (opt) {
            case 'f':
                f_name = optarg;
                break;
            case '?':
                fprintf(stdout, "display usage");
                break;
            default:    
                break;
        }
    } 
        
    if (optind == argc) {optind = 1;} 

    assert(argc > 3);
    strcpy(date, argv[optind++]);
    strcat(date, " ");
    strcat(date, argv[optind++]);
    strcat(date, " ");
    strcat(date, argv[optind++]);
        
    char* arg_time = date;

    if (utmp_open(f_name) == -1 ) {
        fprintf(stderr,"%s: cannot open %s\n", *argv, f_name);
        exit(1);
    }
    fetch_sequential(arg_time);
    utmp_close();
   
    return 0;
}

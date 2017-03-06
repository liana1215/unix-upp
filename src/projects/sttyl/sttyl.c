/**
 * sttyl - is a light weight version of stty, and attempts to mimic some of the
 * functionality provided by stty.
 * date: 3/2/2017
 * author: Tasuku Miura
 */
#include    <ctype.h>
#include    <stdio.h>
#include    <termios.h>
#include    <stdlib.h>
#include    <string.h>
#include    <sys/ioctl.h>
#include    "sttyltables.h"
#include    "sttylutil.h"
/**
 ** showttyl 
 ** Displays some of current tty settings and capable of setting select number
 ** of modes.
 **/

//TODO: stick special char set in library
//TODO: use ptr to make more efficient(when checking args)

int main(int argc, char**argv)
{
    struct  termios ttyinfo;                  /* this struct holds tty info */
     
    if ( tcgetattr( 0 , &ttyinfo ) == -1 ){   /* get info */
        perror( "cannot get params about stdin");
        exit(1);
    }
                       
    if (argc < 2) {
        display_info(&ttyinfo);
    } else {
        int i = 1;
        int j = 0;
     
        for (i = 1; i < argc; i++) {
            for (j = 0; special_chars[j].flag != -1; j++) {
                if (strcmp(argv[i], special_chars[j].name) == 0) {
                    if (argv[i+1] == NULL) {
                        print_usage();
                        exit(1);
                    }
                        
                    ttyinfo.c_cc[special_chars[j].flag] = argv[i+1][0];
                    break;
                }
            }
        }
        if (tcsetattr( 0, TCSADRAIN, &ttyinfo) != 0) {
            perror("tcsetattr");
            exit(1);
        }
    }
    //call tcsetattr returns ok if any set, so call tcetagain to check if all is
    //ok           
    return 0;
}


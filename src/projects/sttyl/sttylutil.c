/**
 * sttylutil.c - utility functions to show information related to tty settings
 * to terminal.
 * date: 3/2/2017
 * author: Tasuku Miura
 */
#include    "sttylutil.h"
#include    <stdio.h>
#include    <stdlib.h>
#include    <sys/ioctl.h>
#include    "sttyltables.h"

void showsize()
/*
 * Prints the terminal window size. 
 */
{
    struct winsize winp;                /* This struct holds tty size info */

    if (ioctl(0, TIOCGWINSZ, &winp) < 0) {
        perror("ioctl() failed. ");
        exit(1);
    }
    printf("rows %hu; ",winp.ws_row);
    printf("columns %hu;\n",winp.ws_col);
} 

void showbaud( int thespeed )
/*
 * Prints the speed in english.
 * @arg: thespeed - speed defined in termios.h
 */
{
    printf("speed ");
    switch ( thespeed ){
        case B300:  printf("300 ");    break;
        case B600:  printf("600 ");    break;
        case B1200: printf("1200 ");   break;
        case B1800: printf("1800 ");   break;
        case B2400: printf("2400 ");   break;
        case B4800: printf("4800 ");   break;
        case B9600: printf("9600 ");   break;
        default:    printf("Fast ");   break;
    }
    printf("baud; ");
}

void showspecial(struct termios *ttyp, const struct flaginfo bitnames[])
/*
 * Displays the special chars.
 * @arg: ttyp - pointer to termios struct.
 * @arg: bitnames - an array of flag info structs.
 */
{
    int i = 0;
    for (i = 0; bitnames[i].flag != -1 ; i++) {
        printf("%s = ^%c; ", bitnames[i].name,
                            ttyp->c_cc[bitnames[i].flag]-1+'A');
    }
    printf("\n");
}

void showflags(const struct flaginfo bitnames[])
/*
 * Displays the flags associated with flaginfo struct.
 * @arg: bitnames - an array of flag info structs
 */
{
    int i = 0;
    for (i = 0; bitnames[i].flag != -1 ; i++)
        printf("%s ", bitnames[i].name);
    printf("\n");
}

/*
 * Displays the info related to stty, when no argument is specified.
 * @arg: termios_p - a pointer to struct termios.
 */
void display_info(struct termios *ttyp)
{
    showbaud ( cfgetospeed( ttyp) );    /* get + show baud rate */
    showsize();                         /* show size of tty */
    showspecial(ttyp, special_chars);   
    showflags(control_modes);
    showflags(input_modes);
    showflags(local_modes);
}





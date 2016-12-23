/* who2.c - a second version of the who program
 *        - open, read UTMP file, and show results
 *        - suppresses empty records
 *        - formats time nicely
 */
#include    <stdio.h>
#include    <utmp.h>
#include    <fcntl.h>
#include    <unistd.h>
#include    <time.h>

#define SHOWHOST    /*include remote machine on output*/

void showtime(long);
void show_info(struct utmp *);

int main() 
{
    struct utmp utbuf;              /*read info into here */
    int         utmpfd;             /*read from this descriptor*/
    int         reclen = sizeof(utbuf);

    if ((utmpfd = open(UTMP_FILE, O_RDONLY)) == -1 ) {
        perror(UTMP_FILE);          /* UTMP_FILE is in utmp.h */
        exit(1);
    }
    while (read(utmpfd, &utbuf, sizeof(utbuf)) == sizeof(utbuf))
        show_info(&utbuf);
    
    close(utmpfd);
    return 0;
}

/*
 * show info()
 *      - displays contens of the utmp struct in human readable form 
 */

void show_info(struct utmp *utbufp)
{
    if (utbufp->ut_type != USER_PROCESS)    
        return;

    printf("%-8.8s\t", utbufp->ut_name);    /* the logname */
    printf("%-8.8s\t", utbufp->ut_line);    /* the tty */
    showtime(utbufp->ut_time);              /* login time */
#ifdef  SHOWHOST
    if (utbufp->ut_host[0] != '\0')
        printf("(%s)", utbufp->ut_host);    /*the host*/
#endif
    printf("\n");
}
       
/*
 * displays time in format fit for human consumption
 */
void showtime(long timeval) 
{
    char    *cp;    
    cp = ctime(&timeval);
    printf("%12.12s", cp+4);
}

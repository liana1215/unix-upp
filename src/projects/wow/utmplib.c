/* utmplib.c  - functions to buffer reads from utmp file 
 *
 *      functions are
 *              int utmp_open( filename )   - open file
 *                      returns -1 on error
 *              struct utmp *utmp_next( )   - return pointer to next struct
 *                      returns NULL on eof or read error
 *              int utmp_close()            - close file
 *
 *      reads NRECS per read and then doles them out from the buffer
 *      hist: 2012-02-14 slightly modified error handling (thanks mk)
 */
#include        <stdio.h>
#include        <fcntl.h>
#include        <sys/types.h>
#include        <sys/stat.h>
#include        <utmp.h>
#include	    <unistd.h>
#include        <time.h>
#include        "utmplib.h"


#define TEXTDATE
#ifndef DATE_FMT
#ifdef  TEXTDATE
#define DATE_FMT    "%b %e %H:%M"       /* text format  */
#else
#define DATE_FMT    "%Y-%m-%d %H:%M"    /* the default  */
#endif
#endif


static  int     num_recs;                               /* num stored   */
static  int     cur_rec;                                /* next to go   */
static  int     fd_utmp = -1;                           /* read from    */
static  int  utmp_reload();


off_t 
utmp_fsize(const char* filename)
{
    struct stat st = {0};
    if (stat(filename, &st) != 0)
        return -1;

    return st.st_size;
}

/*
 * utmp_open -- connect to specified file
 *  args: name of a utmp file
 *  rets: -1 if error, fd for file otherwise
 */
int utmp_open( char *filename )
{
    fd_utmp = open( filename, O_RDONLY );           /* open it      */
    cur_rec = num_recs = 0;                         /* no recs yet  */
    return fd_utmp;                                 /* report       */
}


int utmp_fread(FILE *fp)
{
    int amt_read = 0;
    amt_read = fread(utmpbuf, UTSIZE, UTSIZE, fp);          
    return (amt_read < (int)UTSIZE)?0:1;
}

struct utmp *utmp_get(int idx)
{
    struct utmp *recp;
    if (fd_utmp == -1)
        return NULL;
    
    recp = &(utmpbuf[idx]);
    return recp;
}
  

/*
 * utmp_next -- return address of next record in file
 *  args: none
 *  rets: address of record in buffer
 *  note: this location will be reused on next buffer reload
 */
struct utmp *utmp_next()
{
    struct utmp *recp;

    if ( fd_utmp == -1 )                            /* error ?      */
            return NULL;
    if ( cur_rec==num_recs && utmp_reload() <= 0 )  /* any more ?   */
            return NULL;

    recp = &(utmpbuf[cur_rec]);	/* get address of next record   */
    cur_rec++;
    return recp;
}

static int utmp_reload()
/*
 *      read next bunch of records into buffer
 *      rets: 0=>EOF, -1=>error, else number of records read
 */
{
    int     amt_read;
                                            
    amt_read = read(fd_utmp, utmpbuf, NRECS*UTSIZE);   /* read data	*/
    if ( amt_read < 0 )			/* mark errors as EOF   */
        return -1;
                                            
    num_recs = amt_read/UTSIZE;		/* how many did we get?	*/
    cur_rec  = 0;				    /* reset pointer	*/
    return num_recs;			    /* report results	*/
}

/*
 * utmp_close -- disconnenect
 *  args: none
 *  rets: ret value from close(2)  -- see man 2 close
 */
int utmp_close()
{
  	int rv = 0;
        if ( fd_utmp != -1 ){                   /* don't close if not   */
                rv = close( fd_utmp );          /* open                 */
		fd_utmp = -1;			                /* record as closed	*/
	}
	return rv;
}

/*
 *  show info()
 *          displays the contents of the utmp struct
 *          in human readable form
 *          * displays nothing if record has no user name
 */

void
show_info(struct utmp *utbufp)
{
    if (utbufp->ut_type != USER_PROCESS)
        return;

    printf("%-8s\t", utbufp->ut_name);        /* the logname  */
    printf("%-12.12s\t", utbufp->ut_line);    /* the tty  */
    show_time(utbufp->ut_time, DATE_FMT);     /* display time */
    if (utbufp->ut_host[0] != '\0')
        printf(" (%s)", utbufp->ut_host);     /* the host */

    printf("\n");                             /* newline  */
}

#define MAXDATELEN  100

void
show_time( time_t timeval , char *fmt )
/*
 * displays time in a format fit for human consumption.
 * Uses localtime to convert the timeval into a struct of elements
 * (see localtime(3)) and uses strftime to format the data
 */
{
    char    result[MAXDATELEN];

    struct tm *tp = localtime(&timeval);        /* convert time */
    strftime(result, MAXDATELEN, fmt, tp);      /* format it    */
    fputs(result, stdout);
}


time_t
convert_time(char* date)
{
    struct tm tp;

    strptime(date, "%Y %m %d", &tp);
    return mktime(&tp);
} 


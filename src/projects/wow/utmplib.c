#define     _XOPEN_SOURCE
#include    <stdio.h>
#include    <fcntl.h>
#include    <sys/types.h>
#include    <sys/stat.h>
#include    <utmp.h>
#include    <unistd.h>
#include    <time.h>
#include    "utmplib.h"


static  int num_recs;                               /* num stored   */
static  int cur_rec;                                /* next to go   */
static  int fd_utmp = -1;                           /* read from    */
static  int utmp_reload();


/*
 * utmp_fize - Returns the size of the file.
 *  args: filename
 *  rets: size of file, represented by type off_t
 */
off_t utmp_fsize(const char* filename)
{
    struct stat st = {0};
    if (stat(filename, &st) != 0)
        return -1;

    return st.st_size;
}


/*
 * utmp_open -- Connects to specified file.
 *  args: filename
 *  rets: -1 if error occured, or the file descriptor
 */
int utmp_open( char *filename )
{
    fd_utmp = open( filename, O_RDONLY );           /* open it      */
    cur_rec = num_recs = 0;                         /* no recs yet  */
    return fd_utmp;                                 /* report       */
}


/*
 * utmp_next - Returns address of next record in file.
 *  args: none
 *  rets: address of record in buffer
 *  note: This location will be reused on next buffer reload.
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
 * read next bunch of records into buffer
 * rets: 0=>EOF, -1=>error, else number of records read
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
 * utmp_close - disconnenect
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
 * show_info - outputs log informatoin 
 *  args: utbufp
 * 
 * A specified subset of log information found in the utmp struct in human
 * readable form.
 */
void show_info(struct utmp *utbufp)
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
/* 
 * show_time - displays time in a format fit for human consumption.
 *  args: timeval, *fmt
 *  
 * Uses localtime to convert the timeval into a struct of elements
 * (see localtime(3)) and uses strftime to format the data
 */
void show_time( time_t timeval , char *fmt )
{
    char    result[MAXDATELEN];

    struct tm *tp = localtime(&timeval);        /* convert time */
    strftime(result, MAXDATELEN, fmt, tp);      /* format it    */
    fputs(result, stdout);
}

/*
 * convert_time - converts from string to type time_t
 *  args: *date
 *  rets: time in unix time of type time_t
 */
time_t convert_time(char* date)
{
    struct tm tp = {0};
    tp.tm_isdst = -1;

    strptime(date, "%Y %m %d", &tp);
    return mktime(&tp);
} 


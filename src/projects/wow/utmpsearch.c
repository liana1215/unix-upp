#include <stdlib.h>
#include <time.h>
#include "utmp.h"
#include "utmplib.h"

void 
fetch_sequential(int year, int month, int day) 
{
    struct utmp *utbufp = {0};
    
    while ((utbufp = utmp_next()) != ((struct utmp *) NULL)) {
        time_t* log_time = (time_t)utbufp->ut_time;
        struct tm *log = {0};

        log = gmtime(&log_time);
        if (log->tm_year == year && 
            log->tm_mon == month &&
            log->tm_mday == day) {
            show_info(utbufp);
        }        
    }
}  

/*
void
fetch_bsearch(int year, int month, int day, int fsize)
{
    struct tm key, *res;
    key.tm_year = year;
    key.tm_mon = month;
    key.tm_day = day;
    
    int tot_rec = fsize/UTSIZE;
    res = bsearch(&key, tot_rec, UTSIZE, utmp_comp)
} 
*/  

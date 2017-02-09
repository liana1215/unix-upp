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
        struct tm tm_lb, tm_ub = {0};

        //populate lower bound
        tm_lb.tm_year = year;
        tm_lb.tm_mon = month;
        tm_lb.tm_mday = day;

        //populate upper bound    
        tm_ub.tm_year = year;
        tm_ub.tm_mon = month;
        tm_ub.tm_mday = day + 1;

        time_t tgt_lb = mktime(&tm_lb);
        time_t tgt_ub = mktime(&tm_ub);

        if (log_time >= tgt_lb && log_time <= tgt_ub) {
            show_info(utbufp);
        }        
    }
}  

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


void
fetch_bsearch(int year, int month, int day, int fsize)
{
    int tot_rec = fsize/UTSIZE;
    struct utmp *utbufp = {0};
     
    time_t* log_time = (time_t)utbufp->ut_time; 


    struct tm key;
    key.tm_year = year;
    key.tm_mon = month;
    key.tm_mday = day;
    
    time_t key = mktime(&key);

    int l = 0;
    int r = tot_rec - 1;

        
    //1. set L to first record, set R to last record (n-1)
    //2. if L > R terminate
    //3. set m, middle, to floor of L+R/2
    //4. if A_m < T, set L = m+1, and go to step 2    
    //5. if A_m > T, set R to m-1, go to step 2
    //now A_m == T and search is done. 
}

        

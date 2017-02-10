#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include "utmp.h"
#include "utmplib.h"


void 
fetch_sequential(int year, int month, int day) 
{
    struct utmp *utbufp = {0};
    
    while ((utbufp = utmp_next()) != ((struct utmp *) NULL)) {
        time_t* log_time = (time_t)utbufp->ut_time;
        struct tm tm_lb = {0};
        struct tm tm_ub = {0};

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


int
utmp_bsearch(FILE *fp, int l, int r, time_t key) {
    int m = 0;
    struct utmp temp, ml, mu;
 
    if (l > r)  
        return -1;
    
    m = (int)floor((double)((l+r)/2));

    fseek(fp, (long)m*UTSIZE, SEEK_SET);
    fread(&temp, UTSIZE, 1, fp);

    //get m - 1 and m + 1 for equivalence check
    fseek(fp, (long)(m+1)*UTSIZE, SEEK_SET);
    fread(&mu, UTSIZE, 1, fp);
    fseek(fp, (long)(m-1)*UTSIZE, SEEK_SET);
    fread(&ml, UTSIZE, 1, fp);

    if (ml.ut_time < key && mu.ut_time > key) 
        return m;

    if (temp.ut_time > key) 
        return utmp_bsearch(fp, l, m-1, key);
    
    if (temp.ut_time < key)
        return utmp_bsearch(fp, m+1, r, key);
    
}
     
void
fetch_bsearch(int year, int month, int day, int fsize, FILE* fp)
{
    struct utmp *utbufp = {0};
    struct utmp temp;

    int l_idx = 0;
    int r_idx = 0;
    int m_idx = 0;
    int tot_rec = fsize/(sizeof(struct utmp));     

    //set key as the target date.
    struct tm tm_key = {0};
    tm_key.tm_year = year;
    tm_key.tm_mon = month;
    tm_key.tm_mday = day;    
    time_t key = mktime(&tm_key);

    l_idx = 0;
    r_idx = tot_rec - 1;

    int found = utmp_bsearch(fp, l_idx, r_idx, key);
    if (found == -1) {
        return;
    } else {
        int i = 1;
        tm_key.tm_mday = day + 1;
        time_t key_stop = mktime(&tm_key);
        
        while (1) {
            fseek(fp, (long)((found+(i++))*UTSIZE), SEEK_SET);
            fread(&temp, UTSIZE, 1, fp);

            if (temp.ut_time > key_stop)
                break;

            printf("%-8s\t", temp.ut_name);        /* the logname  */
            printf("%-12.12s\t", temp.ut_line);    /* the tty  */
            show_time(temp.ut_time, DATE_FMT);     /* display time */
            if (temp.ut_host[0] != '\0')
                printf(" (%s)", temp.ut_host);     /* the host */

            printf("\n");   
        }            
          

    }
}
        

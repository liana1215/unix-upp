#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include "utmp.h"
#include "utmplib.h"


static struct utmp butmpbuf[1];

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


void 
deep_copy_utmp(struct utmp* utmp1, struct utmp* utmp2) {
    utmp1->ut_time = utmp2->ut_time;
}     


void
fetch_bsearch(int year, int month, int day, int fsize, FILE *fp)
{
    FILE *l = NULL;
    FILE *r = NULL;
    FILE *m = NULL;
    struct utmp *lutmp ={0};
    struct utmp *rutmp ={0};
    struct utmp *mutmp ={0};
    int l_idx = 0;
    int r_idx = 0;
    int m_idx = 0;
    int tot_rec = fsize/(sizeof(struct utmp));     

    //set key as the target date.
    struct tm tm_key;
    tm_key.tm_year = year;
    tm_key.tm_mon = month;
    tm_key.tm_mday = day;    
    time_t key = mktime(&tm_key);


    l_idx = 0;
    r_idx = tot_rec;

    while(1) {

        l = fp + l_idx*(sizeof(struct utmp));
        r = fp + r_idx*(sizeof(struct utmp));
         
        if (utmp_fread(l) == 0) {
            if (feof(l) )
                fprintf(stdout, "End of File");
            if (ferror(l)) {
                fprintf(stderr, "Error in bsearch");
                exit(1);
            }
        } else {
            deep_copy_utmp(lutmp, butmpbuf);
        }
        
        if (utmp_fread(r) == 0) {
            if (feof(r))
                fprintf(stdout, "End of File");
            if (ferror(r)) {
                fprintf(stderr, "Error in bsearch");
                exit(1);
            }
        } else {
            deep_copy_utmp(rutmp, butmpbuf);
        }
        
        if (lutmp->ut_time > rutmp->ut_time) {
            printf("DONE");
            break;
        }
        
        m_idx = (int)floor((double)((l_idx + r_idx)/2));
        m = fp + m_idx*(sizeof(struct utmp));

        if (utmp_fread(m) == 0) {
            if (feof(m))
                fprintf(stdout, "End of File");
            if (ferror(m)) {
                fprintf(stderr, "Error in bsearch");
                exit(1);
            }
        } else {
            deep_copy_utmp(mutmp,butmpbuf);
        }

        if (mutmp->ut_time < key) {
            l_idx = m_idx + 1;
        } 
        if (mutmp->ut_time > key) {
            r_idx = m_idx - 1;
        }
    }
    //1. set L to first record, set R to last record (n-1)
    //2. if L > R terminate
    //3. set m, middle, to floor of L+R/2
    //4. if A_m < T, set L = m+1, and go to step 2    
    //5. if A_m > T, set R to m-1, go to step 2
    //now A_m == T and search is done. 
}

        

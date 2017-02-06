#include <stdlib.h>
#include "utmp.h"
#include "utmplib.h"


void 
fetch_sequential(char* arg_time) 
{
    struct utmp *utbufp;

    while ((utbufp = utmp_next()) != ((struct utmp *) NULL)) {
        time_t log_time = utbufp->ut_time;
        time_t tgt_time = convert_time(arg_time);

        if (log_time >= tgt_time && log_time <= tgt_time + (time_t)86400) {
            show_info(utbufp);
        }
    }
}    

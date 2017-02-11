#ifndef UTMPLIB_H
#define UTMPLIB_H
/* utmplib.h  - header file with decls of functions in utmplib.c */

#include <utmp.h>

#define NRECS 10
#define UTSIZE (sizeof(struct utmp))

#define TEXTDATE
#ifndef DATE_FMT
#ifdef  TEXTDATE
#define DATE_FMT    "%b %e %H:%M"       /* text format  */
#else
#define DATE_FMT    "%Y-%m-%d %H:%M"    /* the default  */
#endif
#endif

struct utmp utmpbuf[NRECS];

off_t utmp_fsize(const char *);
int utmp_open(char *);
struct utmp *utmp_next();
int utmp_close();
void show_info(struct utmp *);
void show_time(time_t, char *);
time_t convert_time(char*);

#endif

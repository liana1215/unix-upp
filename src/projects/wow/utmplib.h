#ifndef UTMPLIB_H
#define UTMPLIB_H
/* utmplib.h  - header file with decls of functions in utmplib.c */

#include <utmp.h>

int utmp_open(char *);
struct utmp *utmp_next();
int utmp_close();
void show_info(struct utmp *);
void show_time(time_t, char *);
time_t convert_time(char*);


#endif

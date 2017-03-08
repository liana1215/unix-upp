#ifndef STTYLUTIL_H
#define STTYLUTIL_H


#include <termios.h>

void print_usage();
void display_info(struct termios*);
void set_specialchars(struct termios*, int, char**);
void set_modes(struct termios*, int, char**);

#endif

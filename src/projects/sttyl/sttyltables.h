#ifndef TABLES_H
#define TABLES_H

#include <termios.h>
#include <string.h>

struct flaginfo {
    int flag;
    char name[256];
};

extern const struct flaginfo local_modes[];
extern const struct flaginfo input_modes[];
extern const struct flaginfo control_modes[];
extern const struct flaginfo special_chars[];

#endif

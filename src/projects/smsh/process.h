#ifndef	PROCESS_H
#define	PROCESS_H

#include "flexstr.h"

int process(char**);
int do_command(char**);
int execute(char**);
char* var_sub_main(char*);

#endif

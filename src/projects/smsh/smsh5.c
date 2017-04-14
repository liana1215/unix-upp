#include    <ctype.h>
#include	<stdio.h>
#include	<stdlib.h>
#include	<unistd.h>
#include	<signal.h>
#include	<sys/wait.h>
#include    "flexstr.h"
#include	"smsh.h"
#include	"splitline.h"
#include    "string.h"
#include	"varlib.h"
#include	"process.h"

/**
 **	small-shell version 4
 **		first really useful version after prompting shell
 **		this one parses the command line into strings
 **		uses fork, exec, wait, and ignores signals
 **/

#define	DFL_PROMPT	"> "

void	setup();


char* is_in_str(char *str)
/*
 * purpose: determines if a string is a legal variable name
 * returns: 0 for no, 1 for yes
 */
{
    FLEXSTR fname;                      /* Placeholder for new string */
    fs_init(&fname, 0);

    while (1) { 
        char tmp[2048];                 /* Placeholder for string after $ */
        char *cp;

        if ((cp = strchr(str, '$')) == NULL) {
            break;
        }
        
        int i = 0;
        while (*++cp != '\0' && *cp != ' ' && *cp != '.') {
            tmp[i] = *cp;
            i++;
        }
        tmp[i] = '\0';                  /* tmp now contains the target */

        char* val = VLlookup(tmp);      /* Look up tmp and return mapped val */
        if (strcmp(val, "") == 0)
            break;

        for(cp = str; *cp; cp++) {
            if (*cp != '$') {
                fs_addch(&fname, *cp);
            } else {
                fs_addstr(&fname, val);
                int j = 0;
                for (j = 0; j < i; j++)
                    cp++;
            
            }
        }
        fs_addch(&fname, '\0');
        str = fs_getstr(&fname);
    }
    return fs_getstr(&fname);
}   


int main(int argc, char** argv)
{
	char	*cmdline, *prompt, **arglist;
	int	result;
    FILE *fp;

    if (argc > 1) {
        if ((fp = fopen(argv[1], "r")) == NULL) {
            perror("Cant open file:");
            exit(EXIT_FAILURE);
        }
        prompt = NULL;
    } else {
        fp = stdin;
        prompt = DFL_PROMPT ;
    }
    
            
	setup();
	while ((cmdline = next_cmd(prompt, fp)) != NULL) {
        
        char* newcmd = is_in_str(cmdline);

        if (strcmp(newcmd,"") == 0) {
            arglist = splitline(cmdline);
        } else {
            arglist = splitline(newcmd);
        }
        
		if (arglist != NULL) {
			result = process(arglist);
			freelist(arglist);
		}
		free(cmdline);
	}
	return result;
}

void setup()
/*
 * purpose: initialize shell
 * returns: nothing. calls fatal() if trouble
 */
{
	extern char **environ;

	VLenviron2table(environ);
	signal(SIGINT,  SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void fatal(char *s1, char *s2, int n)
{
	fprintf(stderr,"Error: %s,%s\n", s1, s2);
	exit(n);
}

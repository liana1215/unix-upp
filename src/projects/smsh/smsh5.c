#include	<stdio.h>
#include	<stdlib.h>
#include	<unistd.h>
#include	<signal.h>
#include	<sys/wait.h>
#include	"smsh.h"
#include	"splitline.h"
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

	while ( (cmdline = next_cmd(prompt, fp)) != NULL ){
		if ( (arglist = splitline(cmdline)) != NULL  ){
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

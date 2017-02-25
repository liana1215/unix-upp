#
#Makefile for fsct, file system compatibility tester, which searches a tree for
#any files that fit one or more criteria that can cause problems on other
#systems.
#
#

CC  = gcc
CFLAGS = -Wall -g

fsct: fsct.o fsctchecks.o fsctlib.o fsctstack.o
	$(CC) $(CFLAGS) -o fsct fsct.o fsctchecks.o fsctlib.o fsctstack.o

fsct.o: fsct.c
	$(CC) $(CFLAGS) -c fsct.c

fsctchecks.o: fsctchecks.c
	$(CC) $(CFLAGS) -c fsctchecks.c

fsctlib.o: fsctlib.c
	$(CC) $(CFLAGS) -c fsctlib.c

fsctstack.o: fsctstack.c
	$(CC) $(CFLAGS) -c fsctstack.c

clean:
	rm -f fsct fsct.o fsctchecks.o fsctlib.o fsctstack.o

CC     = cc
CFLAGS = -Wall -Wextra -g 


bwow: bwow.o utmplib.o utmpsearch.o
	$(CC) $(CFLAGS) -o bwow bwow.o utmplib.o utmpsearch.o -lm

swow: swow.o utmplib.o utmpsearch.o
	$(CC) $(CFLAGS) -o swow swow.o utmplib.o utmpsearch.o

bwow.o: bwow.c
	$(CC) $(CFLAGS) -c bwow.c

swow.o: swow.c
	$(CC) $(CFLAGS) -c swow.c

utmplib.o: utmplib.c
	$(CC) $(CFLAGS) -c utmplib.c

utmpsearch.o: utmpsearch.c
	$(CC) $(CFLAGS) -c utmpsearch.c

clean:
	rm -f utmplib.o utmpsearch.o swow swow.o 

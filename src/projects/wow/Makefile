CC     = cc
CFLAGS = -Wall -Wextra -g 

swow: swow.o utmplib.o utmpsearch.o
	$(CC) $(CFLAGS) -o swow swow.o utmplib.o utmpsearch.o

swow.o: swow.c
	$(CC) $(CFLAGS) -c swow.c

utmplib.o: utmplib.c
	$(CC) $(CFLAGS) -c utmplib.c

utmpsearch.o: utmpsearch.c
	$(CC) $(CFLAGS) -c utmpsearch.c


clean:
	rm -f utmplib.o utmpsearch.o swow swow.o 

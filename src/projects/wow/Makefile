CC     = cc
CFLAGS = -Wall -Wextra -g 


wow: wow.o utmplib.o utmpsearch.o
	$(CC) $(CFLAGS) -o wow wow.o utmplib.o utmpsearch.o -lm

wow.o: wow.c
	$(CC) $(CFLAGS) -c wow.c

utmplib.o: utmplib.c
	$(CC) $(CFLAGS) -c utmplib.c

utmpsearch.o: utmpsearch.c
	$(CC) $(CFLAGS) -c utmpsearch.c

clean:
	rm -f utmplib.o utmpsearch.o wow wow.o 

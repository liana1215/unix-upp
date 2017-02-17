CC     = gcc
CFLAGS = -Wall -Wextra -g 


wow: wow.o wtmplib.o wtmpsearch.o
	$(CC) $(CFLAGS) -o wow wow.o wtmplib.o wtmpsearch.o -lm

wow.o: wow.c
	$(CC) $(CFLAGS) -c wow.c

utmplib.o: wtmplib.c
	$(CC) $(CFLAGS) -c wtmplib.c

utmpsearch.o: wtmpsearch.c
	$(CC) $(CFLAGS) -c wtmpsearch.c

clean:
	rm -f wtmplib.o wtmpsearch.o wow wow.o 

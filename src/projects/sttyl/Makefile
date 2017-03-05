#
#
CC  = gcc
CFLAGS = -Wall -g

sttyl: sttyl.o sttyltables.o sttylutil.o
	$(CC) $(CFLAGS) -o sttyl sttyl.o sttyltables.o sttylutil.o

sttyl.o: sttyl.c
	$(CC) $(CFLAGS) -c sttyl.c


clean:
	rm -f sttyl sttyl.o sttyltables.o sttylutil.o

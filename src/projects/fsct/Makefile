CC  = gcc
CFLAGS = -Wall -g

fstc: fsct.o fsctchecks.o fsctlib.o
	$(CC) $(CFLAGS) -o fsct fsct.o fsctchecks.o fsctlib.o

fstc.o: fstc.c
	$(CC) $(CFLAGS) -c fstc.c

fsctchecks.o: fsctchecks.c
	$(CC) $(CFLAGS) -c fsctchecks.c

fsctlib.o: fsctlib.c
	$(CC) $(CFLAGS) -c fsctlib.c

clean:
	rm -f fsct fsct.o fsctchecks.o fsctlib.o

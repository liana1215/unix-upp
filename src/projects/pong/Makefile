#
# Makefile for pong
# 

CC = gcc -Wall 
CFLAGS = -g

pong: pong.o alarmlib.o paddle.o ball.o court.o pongutil.o
	$(CC) $(CFLAGS) -o pong pong.o alarmlib.o paddle.o ball.o court.o pongutil.o -lcurses

pong.o: pong.c
	$(CC) $(CFLAGS) -c pong.c

clean:
	rm -f pong *.o


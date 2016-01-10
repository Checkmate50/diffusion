#
# Makefile for core code
# Created by Dietrich Geisler
#

CC = gcc
CFLAGS = -I

all: gauss.c analytical.c
	$(CC) -o gauss gauss.c -lm
	$(CC) -o analytical analytical.c -lm

gauss: gauss.c
	$(CC) -o gauss gauss.c -lm

analytical: analytical.c
	$(CC) -o analytical analytical.c -lm

clean:
	rm -rf *.
	rm -f gauss
	rm -f analytical
#
# Makefile for core code
# Created by Dietrich Geisler
#

CC = gcc
CFLAGS = -I

all: gauss.c
	$(CC) -o gauss gauss.c -lm

clean:
	rm -rf *.
	rm -f gauss
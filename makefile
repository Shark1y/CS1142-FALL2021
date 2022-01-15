# makefile for the Art project

CC = gcc
CFLAGS = -std=c99 -pedantic -Wall -Wextra -O1 -g
LDFLAGS = -lm

default: Greyscale Art Process

Greyscale: Greyscale.c
	${CC} ${CFLAGS} Greyscale.c -o Greyscale ${LDFLAGS}

Art: Art.c Array2D.o
	${CC} ${CFLAGS} Art.c Array2D.o -o Art ${LDFLAGS}

Array2D.o: Array2D.c Array2D.h
	${CC} ${CFLAGS} -c Array2D.c

Process: Process.c 
	${CC} ${CFLAGS} Process.c Array2D.o -o Process ${LDFLAGS}

clean: 
	rm -f Greyscale Art *.o

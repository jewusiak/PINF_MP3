CC=gcc

all:
	$(CC) ./*.c -olabsolver

debug:
	$(CC) ./*.c -g -olabsolver

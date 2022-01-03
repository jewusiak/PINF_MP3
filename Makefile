CC=cc

run: mkdir
	$(CC) ./*.c -ggdb -obin/labsolver

debug: mkdir
	$(CC) ./*.c -ggdb -obin/labsolver -D DEBUG

interactive:
	$(CC) ./*.c -ggdb -obin/labsolver -D INTRACTV

mkdir:
	mkdir -p bin/
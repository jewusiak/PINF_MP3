CC=cc

run: mkdir
	$(CC) ./*.c -ggdb -obin/labsolver

debug: mkdir
	$(CC) ./*.c -ggdb -obin/labsolver -D DEBUG

mkdir:
	mkdir -p bin/
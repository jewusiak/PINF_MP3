CC=cc

all: mkdir
	$(CC) ./*.c -ggdb -obin/a.out


mkdir:
	mkdir -p bin/
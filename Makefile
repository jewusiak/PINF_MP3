CC=cc

all: final
final: build


build: labyrinth_manager.o edges_lib.o matrix_generator.o main.o
	$(CC) $^ -oa.out

labyrinth_manager.o: labyrinth_manager.h
matrix_generator.o: matrix_generator.h
edges_lib.o: edges_lib.h
main.o: labyrinth_manager.h matrix_generator.h edges_lib.h

final:
	rm *.o
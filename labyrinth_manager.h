#ifndef PINF_MP3_LABYRINTH_MANAGER_H
#define PINF_MP3_LABYRINTH_MANAGER_H


#include "edges_lib.h"

int *read_labyrinth(FILE *f, int *real);

int get_lab_value(int* labyrinth, int real, int vert, int horiz);

#endif //PINF_MP3_LABYRINTH_MANAGER_H

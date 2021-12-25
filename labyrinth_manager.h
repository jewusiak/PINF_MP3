#ifndef PINF_MP3_LABYRINTH_MANAGER_H
#define PINF_MP3_LABYRINTH_MANAGER_H


#include "edges_lib.h"

typedef struct {
    int **data;
    int real_size;
    int raw_size;
} lab_t;




lab_t read_labyrinth(FILE *f);

void add(int real_r, int real_c, int real_prev, lab_t *lab, edge_db *edges);

void translate_lab_to_edges(int **lab, int r_size, edge_db *edgeDb);


#endif //PINF_MP3_LABYRINTH_MANAGER_H

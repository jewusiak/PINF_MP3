#ifndef PINF_MP3_MATRIX_GENERATOR_H
#define PINF_MP3_MATRIX_GENERATOR_H

#include "edges_lib.h"
#include <stdlib.h>

typedef struct {
    int **mat;
    int r;
    int c;
} Matrix;

Matrix *create_matrix_malloc(int r, int c) ;

Matrix *create_matrix_calloc(int r, int c) ;

int count_vertices(edge_db edges);

Matrix *generate_adjacency_matrix(edge_db edges);

Matrix *generate_incidence_matrix(edge_db edges);

void print_matrix(Matrix *ptr);


//search




#endif

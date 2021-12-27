#ifndef PINF_MP3_MATRIX_MANAGER_H
#define PINF_MP3_MATRIX_MANAGER_H

#include "edges_lib.h"
#include <stdlib.h>


typedef struct {
    int **mat;
    int r;
    int c;
} Matrix;


Matrix *create_matrix_malloc(int r, int c) ;

Matrix *create_matrix_calloc(int r, int c) ;

Matrix *generate_adjacency_matrix(edge_db edges);

Matrix *generate_incidence_matrix(edge_db edges);

void print_matrix(Matrix *ptr);




#endif

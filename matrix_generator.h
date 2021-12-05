#ifndef PINF_MP3_MATRIX_GENERATOR_H
#define PINF_MP3_MATRIX_GENERATOR_H

#include "edges_lib.h"


int **generate_adjacency_matrix(edge_t *edges, int vertex_cnt, int edge_cnt);

int **generate_incidence_matrix(edge_t *edges, int vertex_cnt, int edge_cnt);

void print_matrix(int **matrix, int rows, int cols);

#endif

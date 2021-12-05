#ifndef PINF_MP3_EDGES_LIB_H
#define PINF_MP3_EDGES_LIB_H


#include <stdio.h>


typedef struct edge {
    int start;
    int end;
    double weight;
} edge_t;



edge_t *load_edges(FILE *f, int *edge_c, int *vertex_c);

void print_input_data(edge_t *edges, int vertex_cnt, int edge_cnt);

#endif

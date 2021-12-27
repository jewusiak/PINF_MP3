#ifndef PINF_MP3_EDGES_LIB_H
#define PINF_MP3_EDGES_LIB_H


#include <stdio.h>


typedef struct edge {
    int start;
    int end;
    double weight;
} edge_t;

typedef struct{
    edge_t *data;
    int size;
} edge_db;


extern edge_db edges;

edge_t *load_edges(FILE *f, int *edge_c, int *vertex_c, int random);

int add_edge_rnd(int from, int to);

double get_weight(edge_t edge);

void print_input_data(edge_t *edges, int vertex_cnt, int edge_cnt);

#endif

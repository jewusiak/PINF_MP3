#ifndef PINF_MP3_SEARCH_H
#define PINF_MP3_SEARCH_H

#include <stdlib.h>
#include "matrix_manager.h"
#include "labyrinth_manager.h"

typedef struct {
    int *data;
    int size;
} sequence_t;

typedef struct{
    sequence_t **data;
    double *weight_sum;
    int size;
} sequence_db;

void DFS_init(int start, edge_db *edges, Matrix *adjacency_m, lab_t* lab, sequence_db *result_paths);

#endif //PINF_MP3_SEARCH_H

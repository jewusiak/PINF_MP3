#ifndef PINF_MP3_SEARCH_H
#define PINF_MP3_SEARCH_H

#include <stdlib.h>
#include "matrix_manager.h"
#include "labyrinth_manager.h"


void DFS_init(int start, edge_db *edges, Matrix *adjacency_m, lab_t *lab);

#endif //PINF_MP3_SEARCH_H

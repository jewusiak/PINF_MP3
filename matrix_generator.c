#include <stdlib.h>
#include "matrix_generator.h"

void print_matrix(int **matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++)
            printf("%d  ", matrix[i][j]);
        printf("\n");
    }
}

int **generate_adjacency_matrix(edge_t *edges, int vertex_cnt, int edge_cnt) {

    int **adjacency_matrix = (int **) malloc(vertex_cnt * sizeof *adjacency_matrix);

    for (int i = 0; i < vertex_cnt; i++)
        adjacency_matrix[i] = (int *) calloc(vertex_cnt, sizeof **adjacency_matrix);

    for (int i = 0; i < edge_cnt; i++)
        adjacency_matrix[edges[i].start][edges[i].end] = 1;

    return adjacency_matrix;
}


int **generate_incidence_matrix(edge_t *edges, int vertex_cnt, int edge_cnt) {

    int **incidence_matrix = (int **) malloc(vertex_cnt * sizeof *incidence_matrix);

    for (int i = 0; i < vertex_cnt; i++)
        incidence_matrix[i] = (int *) calloc(edge_cnt, sizeof **incidence_matrix);

    for (int i = 0; i < edge_cnt; i++) {
        if (edges[i].start == edges[i].end) {
            incidence_matrix[edges[i].start][i] = 2;
            continue;
        }
        incidence_matrix[edges[i].start][i] = 1;
        incidence_matrix[edges[i].end][i] = -1;
    }


    return incidence_matrix;
}

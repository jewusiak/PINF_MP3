#include <malloc.h>
#include "edges_lib.h"


void print_input_data(edge_t *edges, int vertex_cnt, int edge_cnt) {
    printf("V = %d, E = %d\n", vertex_cnt, edge_cnt);
    for (int i = 0; i < edge_cnt; i++)
        printf("E[%d] = %d -> %d; w = %g\n", i, edges[i].start, edges[i].end, edges[i].weight);
    printf("\n");
}


edge_t *load_edges(FILE *f, int *edge_c, int *vertex_c) {
    double in_tmp;
    int  in_edge_count = 0, edges_count = 0, in_count = 0;
    edge_t *edges = malloc(sizeof *edges);
    while (fscanf(f, "%lf", &in_tmp) != EOF) {
        switch (in_count) {
            case 0:
                *vertex_c = (int)in_tmp;
                in_count++;
                continue;
            case 1:
                *edge_c = (int)in_tmp;
                in_count++;
                continue;
        }


        switch (in_edge_count) {
            case 0:
                edges = realloc(edges, (edges_count + 1) * sizeof *edges);
                edges[edges_count].start = (int)in_tmp;
                in_edge_count++;
                break;
            case 1:
                edges[edges_count].end = (int)in_tmp;
                in_edge_count++;
                break;
            case 2:
                edges[edges_count].weight = in_tmp;
                in_edge_count = 0;
                edges_count++;      //zwiększenie ilości krawędzi następuje jedynie jeżeli wczytano wszystkie 3 warotści
                break;
            default:
                printf("Nastapil blad w czytaniu danych (switch).\n");
                return NULL;
        }
        in_count++;
    }
    return edges;
}
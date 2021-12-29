
#include "matrix_manager.h"


/*
 * Tworzy nową macierz bez wyzerowania elementów.
 *
 * Przyjmuje ilość rzędów i kolumn.
 * Zwraca wskaźnik na nową macierz (Matrix *).
 */
Matrix *create_matrix_malloc(int r, int c) {
    Matrix *m = malloc(sizeof *m);
    m->r=r;
    m->c=c;
    m->mat = malloc(r * sizeof *m->mat);
    for (int i = 0; i < r; i++)
        m->mat[i] = malloc(c * sizeof **m->mat);
    return m;
}

/*
 * Tworzy nową macierz z wyzerowanymi elementami.
 *
 * Przyjmuje ilość rzędów i kolumn.
 * Zwraca wskaźnik na nową macierz (Matrix *).
 */
Matrix *create_matrix_calloc(int r, int c) {
    Matrix *m = malloc(sizeof *m);
    m->r=r;
    m->c=c;
    m->mat = malloc(r * sizeof *m->mat);
    for (int i = 0; i < r; i++)
        m->mat[i] = calloc(c , sizeof **m->mat);
    return m;
}


/*
 * Wypisuje na FILE* macierz.
 *
 * Przyjmuje wskaźniki na: plik/strumień i macierz.
 */
void print_matrix(FILE *out, Matrix *ptr) {
    fprintf(out,"\t\t");
    for (int i = 0; i < ptr->c; i++)
        fprintf(out,"%d\t",i);
    fprintf(out, "\n\t----");
    for (int i = 0; i < ptr->c; i++)
        fprintf(out,"----");
    fprintf(out,"\n");
    for (int i = 0; i < ptr->r; i++) {
        fprintf(out,"%d\t|\t",i);
        for (int j = 0; j < ptr->c; j++)
            fprintf(out,"%d\t", ptr->mat[i][j]);
        fprintf(out,"\n");
    }
}

/*
 * Szuka w zbiorze krawędzi maksymalnego ID węzła w grafie.
 *
 * Przyjmuje zbiór krawędzi.
 * Zwraca maksymalne ID węzła.
 */
int get_max_vertex_id(edge_db edges) {
    int max_v = -1;
    for (int i = 0; i < edges.size; i++) {
        if (edges.data[i].start > max_v)
            max_v = edges.data[i].start;
        if (edges.data[i].end > max_v)
            max_v = edges.data[i].end;
    }
    return max_v;
}


/*
 * Generuje macierz sąsiedztwa.
 *
 * Przyjmuje zbiór krawędzi.
 * Zwraca wskaźnik na macierz.
 */
Matrix *generate_adjacency_matrix(edge_db edges) {

int vertex_cnt=get_max_vertex_id(edges)+1;
    /*int **adjacency_matrix = (int **) malloc(vertex_cnt * sizeof *adjacency_matrix);

    for (int i = 0; i < vertex_cnt; i++)
        adjacency_matrix[i] = (int *) calloc(vertex_cnt, sizeof **adjacency_matrix);
*/
    Matrix *adjacency_matrix= create_matrix_calloc(vertex_cnt, vertex_cnt);

    for (int i = 0; i < edges.size; i++)
        adjacency_matrix->mat[edges.data[i].start][edges.data[i].end] = 1;

    return adjacency_matrix;
}

/*
 * Generuje macierz incydencji.
 *
 * Przyjmuje zbiór krawędzi grafu.
 * Zwraca wskaźnik na macierz.
 */
Matrix *generate_incidence_matrix(edge_db edges) {
    int vertex_cnt=get_max_vertex_id(edges)+1;
    /*int **incidence_matrix = (int **) malloc(vertex_cnt * sizeof *incidence_matrix);

    for (int i = 0; i < vertex_cnt; i++)
        incidence_matrix[i] = (int *) calloc(edges.size, sizeof **incidence_matrix);
*/
    Matrix *incidence_matrix= create_matrix_calloc(vertex_cnt, edges.size);

    for (int i = 0; i < edges.size; i++) {
        if (edges.data[i].start == edges.data[i].end) {
            incidence_matrix->mat[edges.data[i].start][i] = 2;
            continue;
        }
        incidence_matrix->mat[edges.data[i].start][i] = 1;
        incidence_matrix->mat[edges.data[i].end][i] = -1;
    }


    return incidence_matrix;
}



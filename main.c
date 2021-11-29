#include <stdio.h>
#include <malloc.h>

typedef struct edge {
    int start;
    int end;
    int weight;
} edge_t;

edge_t *load_edges(FILE *f, int *edge_c, int *vertex_c);

int **generate_adjacency_matrix(edge_t *edges, int vertex_cnt, int edge_cnt);

int **generate_incidence_matrix(edge_t *edges, int vertex_cnt, int edge_cnt);

void print_matrix(int **matrix, int rows, int cols);

int main(int argc, char **argv) {
    if (argc < 2) {
        printf("Za mala liczba argumentow - podaj sciezke do pliku z definicja sgrafu.\n");
        return 1;
    }

    FILE *in = fopen(argv[1], "r");

    if (in == NULL) {
        printf("Nie udalo sie otworzyc pliku: %s\n", argv[1]);
        return 1;
    }


    /*
     * Najpierw definiujemy liczbę wierzchołków a później krawędzi: <V> <E>\n
     * Następnie definiujemy krawedzie w grafie w formacie: <1-wierchołek> <2-wierzchołek> <waga>\n
     * Kolejność podawania wierzchołków ma znaczenie, gdyż taki będzie kierunek w sgrafie.
     * Kolejne krawędzie oddzielamy \n
     * Ważne, aby dla n wierzchołków używać indeksów {0, 1, ..., n-1}.
     * Wszystkie podawane liczby muszą być całkowite, w zakresie |x|<=INT_MAX
     * Oraz ich liczba musi być <= INT_MAX
    */

    int edge_count = 0, vertex_count = 0;
    edge_t *edges = load_edges(in, &edge_count, &vertex_count);
    if (edges == NULL)
        return 1;

    int **adjacency_m = generate_adjacency_matrix(edges, vertex_count, edge_count);

    printf("Macierz sasiedztwa:\n");
    print_matrix(adjacency_m, vertex_count, vertex_count);

    int **incidence_m = generate_incidence_matrix(edges, vertex_count, edge_count);

    printf("Macierz incydencji:\n");
    print_matrix(incidence_m, vertex_count, edge_count);


    return 0;
}


void print_matrix(int **matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d  ", matrix[i][j]);
        }
        printf("\n");
    }
}


int **generate_adjacency_matrix(edge_t *edges, int vertex_cnt, int edge_cnt) {

    int **adjacency_matrix = (int **) malloc(vertex_cnt * sizeof *adjacency_matrix);

    for (int i = 0; i < vertex_cnt; i++)
        adjacency_matrix[i] = (int *) calloc(vertex_cnt, sizeof **adjacency_matrix);

    for (int i = 0; i < edge_cnt; i++)
        adjacency_matrix[edges[i].start][edges[i].end] = edges[i].weight;

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

edge_t *load_edges(FILE *f, int *edge_c, int *vertex_c) {
    int in_tmp, in_edge_count = 0, edges_count = 0, in_count = 0;
    edge_t *edges = malloc(sizeof *edges);
    while (fscanf(f, "%d", &in_tmp) != EOF) {
        switch (in_count) {
            case 0:
                *vertex_c = in_tmp;
                in_count++;
                continue;
            case 1:
                *edge_c = in_tmp;
                in_count++;
                continue;
        }


        switch (in_edge_count) {
            case 0:
                edges = realloc(edges, (edges_count + 1) * sizeof *edges);
                edges[edges_count].start = in_tmp;
                in_edge_count++;
                break;
            case 1:
                edges[edges_count].end = in_tmp;
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
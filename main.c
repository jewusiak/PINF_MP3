#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "labyrinth_manager.h"
#include "search.h"

Matrix *adjacency_m;
Matrix *incidence_m;
lab_t lab;


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

    srand(time(NULL));


    lab = read_labyrinth(in);
    for (int i = 0; i < lab.raw_size; i++) {
        for (int j = 0; j < lab.raw_size; j++)
            printf("%d\t", lab.data[i][j]);
        printf("\n");
    }

    extern edge_db edges;
    init_add(&lab);
    adjacency_m = generate_adjacency_matrix(edges);
    incidence_m = generate_incidence_matrix(edges);
    puts("Sasiedztwa:");
    print_matrix(adjacency_m);
    puts("Incyndencji:");
    print_matrix(incidence_m);
//search(adjacency_m);

    DFS_init(lab.start_real_c);

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
    //edge_t *edges = load_edges(in, &edge_count, &vertex_count, random_weights);
    /* if (edges == NULL)
         return 1;

     print_input_data(edges, vertex_count, edge_count);

     int **adjacency_m = generate_adjacency_matrix(edges, vertex_count, edge_count);

     printf("Macierz sasiedztwa:\n");
     print_matrix(adjacency_m, vertex_count, vertex_count);

     int **incidence_m = generate_incidence_matrix(edges, vertex_count, edge_count);

     printf("Macierz incydencji:\n");
     print_matrix(incidence_m, vertex_count, edge_count);
 */

    return 0;
}



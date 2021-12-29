#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "labyrinth_manager.h"
#include "search.h"
#include "file_manager.h"


int main(int argc, char **argv) {

    srand(time(NULL));

    //Otwarcie pliku
    FILE *in = open_file(argc, argv);
    if (in == NULL)
        return 4;

    lab_t lab;

    //Czytanie labiryntu z pliku
    if ((lab = read_labyrinth(in)).real_size == -1)
        return 2;


    //Wykrywanie krawędzi
    edge_db *edges = malloc(sizeof *edges);
    edges->size = 0;
    if (init_add(&lab, edges) == 1) {
        printf("Brak pozycji początkowej!");
        return 3;
    }

    //Generowanie macierzy sąsiedztwa
    Matrix *adjacency_m = generate_adjacency_matrix(*edges);


#ifdef DEBUG
    printf("Sasiedztwa:\n");
    print_matrix(stdout, adjacency_m);

    //Generowanie macierzy incydencji
    Matrix *incidence_m = generate_incidence_matrix(*edges);
    printf("Incyndencji:\n");
    print_matrix(stdout, incidence_m);
#endif


    sequence_db *result_paths = malloc(sizeof *result_paths);
    result_paths->size = 0;

    //Wyszukiwanie ścieżek algorytmem DFS
    DFS_init(lab.start_real_c, edges, adjacency_m, &lab, result_paths);

    int shortest_index = -1;

    //Wyszukanie najkrótszej ścieżki pod względem sumy wag krawędzi.
    for (int i = 0; i < result_paths->size; i++)
        if (shortest_index == -1)
            shortest_index = i;
        else if (result_paths->weight_sum[i] < result_paths->weight_sum[shortest_index])
            shortest_index = i;

    //Wypisanie najkrótszej ścieżki
    if (shortest_index == -1) {
        puts("Nie znaleziono sciezek!\nMozliwe jest ze nie zdefiniowano punktu koncowego 'K'.");
        return 1;
    } else {
        printf("NAJKRÓTSZA:\nP > ");
        for (int i = 0; i < result_paths->data[shortest_index]->size; i++)
            printf("%d > ", result_paths->data[shortest_index]->data[i]);
        printf("K\t(Suma: %g)\n", result_paths->weight_sum[shortest_index]);
    }

    return 0;
}



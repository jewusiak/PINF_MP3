#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "labyrinth_manager.h"
#include "search.h"
#include "file_manager.h"





int main(int argc, char **argv) {

    srand(time(NULL));
    FILE *in = open_file(argc, argv);
    if (in == NULL)
        return 1;//Niepowodzenie otwarcia pliku

    lab_t lab;

    if ((lab = read_labyrinth(in)).real_size == -1)
        return 2; //Niepowodzenie czytania z pliku

    /*//Wypisanie raw data
    for (int i = 0; i < lab.raw_size; i++) {
        for (int j = 0; j < lab.raw_size; j++)
            printf("%d\t", lab.data[i][j]);
        printf("\n");
    }*/

    edge_db *edges=malloc(sizeof *edges);
    edges->size=0;
    if(init_add(&lab, edges)==1){
        puts("Brak pozycji początkowej!");
        return 3;
    }

    Matrix *adjacency_m = generate_adjacency_matrix(*edges);
    Matrix *incidence_m = generate_incidence_matrix(*edges);

    puts("Sasiedztwa:");
    print_matrix(stdout,adjacency_m);
    puts("Incyndencji:");
    print_matrix(stdout,incidence_m);


    sequence_db *result_paths= malloc(sizeof *result_paths);
    result_paths->size=0;

    DFS_init(lab.start_real_c, edges, adjacency_m, &lab, result_paths);
    puts("TESTA\n");
    for(int i=0;i<result_paths->size;i++){
        for(int j=0;j<result_paths->data[i]->size;j++)
            printf("%d\t",result_paths->data[i]->data[j]);
        printf("(Suma: %g)\n", result_paths->weight_sum[i]);
    }



    //int edge_count = 0, vertex_count = 0;
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



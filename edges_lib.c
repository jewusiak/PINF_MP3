#include <stdlib.h>
#include "edges_lib.h"


/*
 * Wypisuje dane o krawędziach.
 *
 * Przyjmuje wskaźnik na strumień i na zbiór krawędzi, liczbę węzłów i krawędzi.
 */
void print_input_data(FILE *out, edge_t *edges, int vertex_cnt, int edge_cnt) {
    printf("V = %d, E = %d\n", vertex_cnt, edge_cnt);
    for (int i = 0; i < edge_cnt; i++)
        printf("E[%d] = %d -> %d; w = %g\n", i, edges[i].start, edges[i].end, edges[i].weight);
    printf("\n");
}

/*
 * Wczytuje listę krawędzi z pliku w formacie:
 * Najpierw definiujemy liczbę wierzchołków a później krawędzi: <V> <E>\n
 * Następnie definiujemy krawedzie w grafie w formacie: <1-wierchołek> <2-wierzchołek> [waga]\n
 * Kolejność podawania wierzchołków ma znaczenie, gdyż taki będzie kierunek w sgrafie.
 * Kolejne krawędzie oddzielamy \n
 * Ważne, aby dla n wierzchołków używać indeksów {0, 1, ..., n-1}.
 * Wszystkie podawane liczby muszą być całkowite, w zakresie |x|<=INT_MAX
 * Oraz ich liczba musi być <= INT_MAX
 * Waga nalęży wpisać jeżeli random!=1.
 *
 * Przyjmuje wskaźnik na strumień, liczbę krawędzi, węzłów i random - 1 - losowe wagi, 0 - zdefiniowane
 * Zwraca:
 * edge_t* - powowdzenie
 * NULL - niepowowdzenie
 */
edge_t *load_edges(FILE *f, int *edge_c, int *vertex_c, int random) {
    double in_tmp;
    int in_edge_count = 0, edges_count = 0, in_count = 0;
    edge_t *edges = malloc(sizeof *edges);
    while (fscanf(f, "%lf", &in_tmp) != EOF) {
        switch (in_count) {
            case 0:
                *vertex_c = (int) in_tmp;
                in_count++;
                continue;
            case 1:
                *edge_c = (int) in_tmp;
                in_count++;
                continue;
        }


        switch (in_edge_count) {
            case 0:
                edges = realloc(edges, (edges_count + 1) * sizeof *edges);
                edges[edges_count].start = (int) in_tmp;
                in_edge_count++;
                break;
            case 1:
                edges[edges_count].end = (int) in_tmp;
                if (random == 1) {
                    in_edge_count = 0;
                    edges[edges_count].weight = (double) rand() / RAND_MAX * 10.0;
                    edges_count++;
                } else
                    in_edge_count++;
                break;
            case 2:
                edges[edges_count].weight = in_tmp;
                in_edge_count = 0;
                edges_count++;      //zwiększenie ilości krawędzi następuje jedynie jeżeli wczytano wszystkie 3 warotści
                break;
            default:
                fprintf(stderr, "Nastapil blad w czytaniu danych (switch).\n");
                return NULL;
        }
        in_count++;
    }
    return edges;
}

//Zwraca: 0 - nie istnieje, 1 - istnieje (nie dodajemy), 2 - istnieje odwrotna (dodajemy z tą samą wagą)
/*
 * Sprawdza czy w zbiorze krawędzi istanieje podana krawędź.
 *
 * Przyjmuje: krawędź i wskaźnik na zbiór krawędzi.
 * Zwraca:
 * 0 - nie istnieje
 * 1 - istnieje identyczna (nie należy dodawać)
 * 2 - istnieje odwrotna (należy skopiować wagę)
 */
int does_edge_exist(edge_t edge, edge_db *edges) {
    int ident = 0;
    for (int i = 0; i < edges->size; i++)
        if (edges->data[i].start == edge.start && edges->data[i].end == edge.end) //1 - istnieje identyczna
            return 1;
        else if (edges->data[i].start == edge.end && edges->data[i].end == edge.start) //istnieje odwrotna
            ident = 1;

    return ident == 1 ? 2 : 0;
}


/*
 * Zwraca wagę krawędzi.
 *
 * Przyjmuje krawędź i wskaźnik na zbiór krawędzi.
 * Zwraca:
 * wagę do w/w krawędzi - powodzenie
 * -1 - niepowodzenie
 */
double get_weight(edge_t edge, edge_db *edges) {
    for (int i = 0; i < edges->size; i++)
        if (edges->data[i].start == edge.start && edges->data[i].end == edge.end)
            return edges->data[i].weight;
    return -1;
}


/*
 * Zwraca wagę odwrotnej krawędzi.
 *
 * Przyjmuje krawędź i wskaźnik na zbiór krawędzi.
 * Zwraca:
 * powodzenie - wagę do krawędzi odwrotnej do w/w
 * -1 - niepowodzenie
 */
double get_reversed_weight(edge_t edge, edge_db *edges) {
    return get_weight((edge_t) {.start=edge.end, .end=edge.start}, edges);
}


/*
 * Dodaje nową krawędź do zbioru krawędzi, przy okzaji generując losową wagę (0,10)
 *
 * Przyjmuje: węzeł początkowy i końcowy, wskaźnik na zbiór krawędzi
 * Zwraca:
 * 0 - powowdzenie
 * -1 - błąd ogólny
 * 2 - istnieje identyczna
 */
int add_edge_rnd(int from, int to, edge_db *edges) {
    printf("%d -> %d (", from, to);
    edge_t edge = {.start=from, .end=to, .weight=(double) rand() / RAND_MAX * 10.0};
    switch (does_edge_exist(edge, edges)) {
        case 0: //nie istnieje, czyli nic nie zmieniamy w edge
            printf("Nie istnieje - 0)\n");
            break;
        case 1: //istnieje identyczna, czyli wychodzimy z f()
            printf("Identyczna - 1)\n");
            return 2;
        case 2: //istnieje odwrotna, czyli kopiujemy weight
            edge.weight = get_reversed_weight(edge, edges);
            printf("Odwrotna - 2)\n");
            break;
        default:
            fprintf(stderr, "Blad w add_edge_rnd()!\n");
            return -1;
    }
    edges->size++;
    if (edges->size == 1)
        edges->data = malloc(sizeof *edges->data);
    else
        edges->data = realloc(edges->data, edges->size * sizeof *edges->data);

    edges->data[edges->size - 1] = edge;
    return 0;
}

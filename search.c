#include "search.h"
#include "edges_lib.h"
#include "labyrinth_manager.h"

typedef struct {
    int *data;
    int size;
} sequence_t;



/*
 * Dodaje do sekwencji.
 *
 * Przyjmuje nowy element (int) i wskaźnik na sekwencję.
 */
void add_to_sequence(int pnt, sequence_t *sequence) {
    if (sequence->size++ == 0)
        sequence->data = malloc(sizeof *sequence->data);
    else
        sequence->data = realloc(sequence->data, sequence->size * sizeof *sequence->data);
    sequence->data[sequence->size - 1] = pnt;
}


/*
 * Duplikuje sekwencję - ściezkę.
 *
 * Przyjmuje sequence_t* do zduplikowania.
 * Zwraca w pełni skopiowany element sequence_t* (deep copy).
 */
sequence_t *duplicate_sequence(sequence_t *sequenceToDuplicate) {
    sequence_t *new_s = malloc(sizeof *new_s);
    new_s->size = sequenceToDuplicate->size;
    new_s->data = malloc(sequenceToDuplicate->size * sizeof *new_s->data);
    for (int i = 0; i < sequenceToDuplicate->size; i++)
        new_s->data[i] = sequenceToDuplicate->data[i];
    return new_s;
}


/*
 * Szuka sąsiadów.
 *
 * Przyjmuje nr elementu dla którego ma znaleźć sąsiadów.
 * Zwraca (sequence_t *){->size=n}, dla n elementów.
 */
sequence_t *get_adjacent(int this, Matrix *adjacency_m) {
    sequence_t *found = malloc(sizeof *found);
    found->size=0;
    for (int i = 0; i < adjacency_m->c; i++)
        if (adjacency_m->mat[this][i] == 1)
            add_to_sequence(i, found);
    return found;
}


/* Sprawdza czy element jest elementem końcowym w labiryncie wyjściem z niego.
 *
 * Przyjmuje nr elementu.
 * Korzysta z globalnej zmiennej labiryntu.
 * Zwraca:
 * 1 - jeżeli jest to ostatni element.
 * 0 - w przeciwnym wypadku
 */
int is_last(int this, lab_t *lab) {
    int real_c = this % 10;
    this = this / 10;//this==real_r
    if (lab->data[this * 2 + 2][real_c * 2 + 1] == 3)
        return 1;
    return 0;
}

/*
 * Sprawdza czy dany element istnieje w ścieżce.
 *
 * Przyjmuje numer elementu i ścieżkę.
 * Zwraca:
 * 1 - jeżeli istnieje
 * 0 - jeżeli nie istnieje
 */
int exists_in_sequence(int this, sequence_t *sequence) {
    for (int i = 0; i < sequence->size; i++)
        if (sequence->data[i] == this)
            return 1;
    return 0;
}


/*
 * Sumuje wagę (długość) ścieżki.
 *
 * Przyjmuje ścieżkę.
 * Zwraca wagę.
 */
double sum_sequence_weight(sequence_t *sequence, edge_db *edges) {
    double sum = 0;
    for (int i = 0; i < sequence->size - 1; i++)
        sum += get_weight((edge_t) {.start=sequence->data[i], .end=sequence->data[i + 1]}, edges);
    return sum;
}

/*
 * Generalnie DFS przyjmuje dotychczasową sekwencję i kolejny element.
 * Idzie do każdego nieodwiedzonego w sequence sąsiada.
 *
 * Dodaje ścieżkę do zbioru ścieżek jeżeli nie ma żadnych więciej sąsiadów, lub dotarł do końcowego.
 *
 * Przyjmuje dotychczasową ścieżkę i kolejny element.
 * */

void DFS(sequence_t *sequence, int next, edge_db *edges, Matrix *adjacency_m, lab_t *lab) {
    add_to_sequence(next, sequence);
    sequence_t *adjacent= get_adjacent(next, adjacency_m);
    if (is_last(next, lab) == 0) /*warunek na nieostatni element*/  {//posiada somsiadów
        for (int i = 0; i<adjacent->size; i++)//dal każdego z somsiadów
            if (exists_in_sequence(adjacent->data[i], sequence) == 0)
                DFS(duplicate_sequence(sequence), adjacent->data[i], edges, adjacency_m, lab);


    } else {//somsiadów ni ma
        printf("Sciezka: ");
        for (int i = 0; i < sequence->size; i++)
            printf("%d\t", sequence->data[i]);
        if (is_last(sequence->data[sequence->size - 1], lab) == 1) {
            printf("(END, suma=%g!)", sum_sequence_weight(sequence, edges));
        }
        printf("\n");
    }

}

/*
 * Inicjuje działanie algorytmu DFS.
 *
 * Przyjmuje nr pierwszej pozycji.
 */
void DFS_init(int start, edge_db *edges, Matrix *adjacency_m, lab_t* lab) {
    sequence_t *seq = malloc(sizeof *seq);
    seq->size = 0;
    DFS(seq, start, edges, adjacency_m, lab);
}


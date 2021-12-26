#include "search.h"
#include "edges_lib.h"
#include "labyrinth_manager.h"

typedef struct {
    int *data;
    int size;
} sequence_t;

extern Matrix *adjacency_m;
extern Matrix *incidence_m;
extern lab_t lab;

void add_to_sequence(int pnt, sequence_t *sequence) {
    if (sequence->size++ == 0)
        sequence->data = malloc(sizeof *sequence->data);
    else
        sequence->data = realloc(sequence->data, sequence->size * sizeof *sequence->data);
    sequence->data[sequence->size - 1] = pnt;
}

sequence_t *duplicate_sequence(sequence_t *sequenceToDuplicate) {
    sequence_t *new_s = malloc(sizeof *new_s);
    new_s->size = sequenceToDuplicate->size;
    new_s->data = malloc(sequenceToDuplicate->size * sizeof *new_s->data);
    for (int i = 0; i < sequenceToDuplicate->size; i++)
        new_s->data[i] = sequenceToDuplicate->data[i];
    return new_s;
}

/*void add_point(int this, int up, int down, int left, int right, point_type type, point_db *points){
    points->size++;
    if(points->size==1)
        points->data= malloc(sizeo f *points->data);
    else
        points->data=realloc(points->data, points->size*sizeof *points->data);
    points->data[points->size-1]=(point_t){this, up, down, left, right, type};
}

point_t get_point(int nr, edge_db *edges){
    point_t pnt={.this=nr};
    //for(int edges)
}*/


int *get_adjacent(int this) {
    int *found=malloc(4*sizeof *found);
    for(int i=0;i<4;i++)
        found[i]=-1;
    int size = 0;
    for (int i = 0; i < adjacency_m->c; i++)
        if (adjacency_m->mat[this][i] == 1)
            found[size++] = i;
    return found;
}


//Zwraca 1 jeżeli ostatni, w przeciwnym przypadku 0
int is_last(int this){
    int real_c=this%10;
    this=this/10;//this==real_r
    if(lab.data[this*2+2][real_c*2+1]==3)
        return 1;
    return 0;
}


//Zwraca 1 jeżeli punkt jest w sekwencji, 0 w przeciwnym wypadku
int exists_in_sequence(int this, sequence_t *sequence){
    for(int i=0;i<sequence->size;i++)
        if(sequence->data[i]==this)
            return 1;
    return 0;
}
/*
 * Generalnie DFS przyjmuje dotychczasową sekwencję i kolejny element.
 * Idzie do każdego nieodwiedzonego w sequence sąsiada.
 * Zwraca nic.
 * Dodaje do zbioru sekwencji jeżeli nie ma żadnych więciej sąsiadów, lub dotarł do końcowego.
 * */

void DFS(sequence_t *sequence, int next) {
    add_to_sequence(next, sequence);
    int *adjacent=malloc(4*sizeof *adjacent);
    adjacent = get_adjacent(next);
    int a=0;
    if(*adjacent!=-1 && is_last(next)==0) /*warunek na nieostatni element*/  {//posiada somsiadów
    for (int i=0;*adjacent != -1&&i<4;i++,adjacent++)//dal każdego z max 4 somsiadów
        if(exists_in_sequence(*adjacent,sequence)==0)
            DFS(duplicate_sequence(sequence),*adjacent);


    }else{//somsiadów ni ma
        printf("Scieżka: ");
        for(int i=0;i<sequence->size;i++)
            printf("%d\t",sequence->data[i]);
        if(is_last(sequence->data[sequence->size-1])==1)
            printf("(END!)");
        printf("\n");
    }

}


void DFS_init(int start) {
    sequence_t *seq = malloc(sizeof *seq);
    seq->size = 0;
    DFS(seq, start);
}


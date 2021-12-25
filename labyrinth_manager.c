#include <math.h>
#include <stdlib.h>
#include "labyrinth_manager.h"

#define MAX_LABIRYNTH_SIZE 21 //czyli w naszej notacji 10x10


lab_t read_labyrinth(FILE *f) {
    lab_t lab;
    lab.data = malloc(MAX_LABIRYNTH_SIZE * sizeof *lab.data);
    for (int i = 0; i < MAX_LABIRYNTH_SIZE; i++)
        lab.data[i] = calloc(MAX_LABIRYNTH_SIZE, sizeof **lab.data);
    int linec = 0, charc = 0;
    //0 - puste, 1 - ściana, 2 - początek, 3 - koniec

    char c;
    while ((c = fgetc(f)) != EOF) {
        switch (c) {
            case ' ':
                lab.data[linec][charc] = 0;
                break;
            case '#':
                lab.data[linec][charc] = 1;
                break;
            case 'P':
                lab.data[linec][charc] = 2;
                break;
            case 'K':
                lab.data[linec][charc] = 3;
                break;
            case '\n':
                linec++;
                charc = 0;
                continue;
            default:
                return (lab_t) {.real_size=-1};//TODO: zrobić exception
        }
        charc++;
    }
    if (c == EOF)
        linec++;

    lab.raw_size = linec;
    lab.real_size = (linec - 1) / 2;
    return lab;

}

typedef enum {NORMAL, START, END} point_type;

typedef struct e{
    int this;
    struct e *adjacent[4]; //jeżeli brak to adjacent[x]==-1
    point_type type;
} point_t;

typedef struct{
    point_t *data;
    int size;
} point_db;


void add(int real_r, int real_c, int real_prev, lab_t *lab, edge_db *edges) {
    int a;
    if(edges->size==9)
        a=1;
    int real_this = 10 * real_r + real_c;
    int raw_r = real_r * 2 + 1;
    int raw_c = real_c * 2 + 1;
    int real_next;
    if (real_prev != -99)
        if(add_edge_rnd(real_prev, real_this, edges)==2)
            return;

    real_next = real_this - 10;
    if (real_r != 0 && lab->data[raw_r -1][raw_c] == 0&& real_next != real_prev) //go up
        add(real_r - 1, real_c, real_this, lab, edges);

    real_next = real_this + 10;
    if (real_r != lab->real_size - 1 && lab->data[raw_r + 1][raw_c] == 0 && real_next!=real_prev)  //go down
        add(real_r + 1, real_c, real_this, lab, edges);

    real_next = real_this - 1;
    if (real_c != 0 &&  lab->data[raw_r ][raw_c-1] == 0&& real_next != real_prev) //go left
        add(real_r, real_c - 1, real_this, lab, edges);

    real_next = real_this + 1;
    if (real_c != lab->real_size - 1  && lab->data[raw_r ][raw_c+1] == 0&& real_next != real_prev) //go right
        add(real_r, real_c + 1, real_this, lab, edges);


}


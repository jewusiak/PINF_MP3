#include <stdlib.h>
#include "labyrinth_manager.h"

#define MAX_LABIRYNTH_SIZE 21 //czyli w naszej notacji 10x10



/*
 * Czyta labirynt z pliku.
 * Zwraca:
 * lab_t.real_size!=-1 - powodzenie
 * lab_t.real_size==-1 - nieznany znak (!= ' ', #, P, K, '\n')
 */
lab_t read_labyrinth(FILE *f) {
    lab_t lab_tmp;
    lab_tmp.data = malloc(MAX_LABIRYNTH_SIZE * sizeof *lab_tmp.data);
    for (int i = 0; i < MAX_LABIRYNTH_SIZE; i++)
        lab_tmp.data[i] = calloc(MAX_LABIRYNTH_SIZE, sizeof **lab_tmp.data);
    int linec = 0, charc = 0;


    char c;
    while ((c = fgetc(f)) != EOF) {
        switch (c) {
            case ' ':
                lab_tmp.data[linec][charc] = 0;
                break;
            case '#':
                lab_tmp.data[linec][charc] = 1;
                break;
            case 'P':
                lab_tmp.data[linec][charc] = 2;
                break;
            case 'K':
                lab_tmp.data[linec][charc] = 3;
                break;
            case '\n':
                linec++;
                charc = 0;
                continue;
            default:
                return (lab_t){.real_size=-1};
        }
        charc++;
    }
    if (c == EOF)
        linec++;

    lab_tmp.raw_size = linec;
    lab_tmp.real_size = (linec - 1) / 2;
    return lab_tmp;

}



void add(int real_r, int real_c, int real_prev, lab_t *lab_tmp) {
    int real_this = 10 * real_r + real_c;
    int raw_r = real_r * 2 + 1;
    int raw_c = real_c * 2 + 1;
    int real_next;
    if (real_prev != -99)
        if(add_edge_rnd(real_prev, real_this)==2)
            return;

    real_next = real_this - 10;
    if (real_r != 0 && lab_tmp->data[raw_r - 1][raw_c] == 0 && real_next != real_prev) //go up
        add(real_r - 1, real_c, real_this, lab_tmp);

    real_next = real_this + 10;
    if (real_r != lab_tmp->real_size - 1 && lab_tmp->data[raw_r + 1][raw_c] == 0 && real_next != real_prev)  //go down
        add(real_r + 1, real_c, real_this, lab_tmp);

    real_next = real_this - 1;
    if (real_c != 0 && lab_tmp->data[raw_r ][raw_c - 1] == 0 && real_next != real_prev) //go left
        add(real_r, real_c - 1, real_this, lab_tmp);

    real_next = real_this + 1;
    if (real_c != lab_tmp->real_size - 1 && lab_tmp->data[raw_r ][raw_c + 1] == 0 && real_next != real_prev) //go right
        add(real_r, real_c + 1, real_this, lab_tmp);


}

/*
 * Rozpoczyna pracę poszukiwania krawędzi.
 * Poszukuje pierwszej pozycji po literze 'P' w linii zerowej.
 * Zwraca:
 * 0 - powowdzenie
 * 1 - brak pozycji początkowej
 */
int init_add(lab_t *lab_tmp){
    int line=-1;
    for(int i=0; i < lab_tmp->real_size; i++)
        if(lab_tmp->data[0][2 * i + 1] == 2){
            line=i;
            break;
        }
    if(line==-1)
        return 1;
    lab_tmp->start_real_c=line;
    add(0, lab_tmp->start_real_c, -99, lab_tmp);
    return 0;
}
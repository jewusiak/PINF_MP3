#include <stdlib.h>
#include "labyrinth_manager.h"

#define MAX_LABIRYNTH_SIZE 21 //czyli w naszej notacji 10x10

extern int mode;

/*
 * Czyta labirynt z pliku.
 *
 * Przyjmuje wskaźnik na otwarty plik (FILE *)
 * Zwraca:
 * lab_t.real_size!=-1 - powodzenie
 * lab_t.real_size==-1 - nieznany znak (!= ' ', #, P, K, '\n')
 * lab_t.real_size==-2 - labirynt niekwadratowy/nieprawidłowe dane
 * lab_t.real_size==-3 - labirynt zbyt duży
 */
lab_t read_labyrinth(FILE *f) {
    lab_t lab;
    lab.real_size=-1;
    lab.data = malloc(MAX_LABIRYNTH_SIZE * sizeof *lab.data);
    for (int i = 0; i < MAX_LABIRYNTH_SIZE; i++)
        lab.data[i] = calloc(MAX_LABIRYNTH_SIZE, sizeof **lab.data);
    int linec= 0, charc = 0;


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
                if(linec>=21)
                    return (lab_t){.real_size=-3};
                if(lab.real_size==-1){
                    lab.real_size=(charc-1)/2;
                    lab.raw_size=charc;
                }
                charc = 0;
                continue;
            case '\r':
                continue;
            default:
                return (lab_t){.real_size=-1};
        }
        charc++;
    }
    if (c == EOF)
        linec++;

   // lab.raw_size = linec;
    //lab.real_size = (linec - 1) / 2;
    if(linec!=charc){
        return (lab_t){.real_size=-2};
    }


    return lab;

}


/*
 * Przeszukuje wgłąb graf, dodaje krawędzie do zbioru.
 *
 * Przyjmuje rząd w labiryncie, kolumnę (zakres 0-9), ID poprzedniego elementu i wskaźniki na: zbiór krawędzi i labirynt.
 */
void add(int real_r, int real_c, int real_prev, lab_t *lab, edge_db *edges) {


    int real_this = 10 * real_r + real_c;
    int raw_r = real_r * 2 + 1;
    int raw_c = real_c * 2 + 1;
    int real_next;
    if (real_prev != -99)
        if(add_edge_rnd(real_prev, real_this, edges)==2)
            return;

    real_next = real_this - 10;
    if (real_r != 0 && lab->data[raw_r - 1][raw_c] == 0 && real_next != real_prev) //go up
        add(real_r - 1, real_c, real_this, lab, edges);

    real_next = real_this + 10;
    if (real_r != lab->real_size - 1 && lab->data[raw_r + 1][raw_c] == 0 && real_next != real_prev)  //go down
        add(real_r + 1, real_c, real_this, lab, edges);

    real_next = real_this - 1;
    if (real_c != 0 && lab->data[raw_r ][raw_c - 1] == 0 && real_next != real_prev) //go left
        add(real_r, real_c - 1, real_this, lab, edges);

    real_next = real_this + 1;
    if (real_c != lab->real_size - 1 && lab->data[raw_r ][raw_c + 1] == 0 && real_next != real_prev) //go right
        add(real_r, real_c + 1, real_this, lab, edges);


}

/*
 * Rozpoczyna pracę poszukiwania krawędzi.
 * Poszukuje pierwszej pozycji po literze 'P' w linii zerowej.
 *
 * Przyjmuje wskaźniki na: labirynt i zbiór krawędzi.
 * Zwraca:
 * 0 - powowdzenie
 * 1 - brak pozycji początkowej
 */
int init_add(lab_t *lab, edge_db *edges){
    int line=-1;
    for(int i=0; i < lab->real_size; i++)
        if(lab->data[0][2 * i + 1] == 2){
            line=i;
            break;
        }
    if(line==-1)
        return 1;
if (mode == 1) {
    puts("Czytanie krawędzi w labiryncie:");
}
    lab->start_real_c=line;
    add(0, lab->start_real_c, -99, lab, edges);
    return 0;
}
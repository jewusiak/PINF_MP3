#include <math.h>
#include <stdlib.h>
#include "labyrinth_manager.h"

#define MAX_LABIRYNTH_SIZE 10

int *read_labyrinth(FILE *f, int *real) {
    int array_size = pow(MAX_LABIRYNTH_SIZE * 2 + 1, 2);
    int *lab = calloc(array_size, sizeof *lab);
    int linec = 0, charc = 0;
    int real_size = 0;
    //0 - puste, 1 - ściana

    char c;
    while ((c = fgetc(f)) != EOF) {
        if (real_size == 0 && c == '\n')
            real_size = charc;
        charc++;
        if(charc>real_size&&real_size!=0) {
            charc=0;
            linec++;
            continue;
        }

        lab[linec*real_size+charc-1]=c-48;

    }
    linec++;

    *real=real_size;
return lab;

}


int get_lab_value(int* labyrinth, int real, int vert, int horiz){
    return labyrinth[real*vert+horiz];
}

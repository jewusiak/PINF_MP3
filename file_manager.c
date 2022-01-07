#include "file_manager.h"

/*
 * Otwiera plik z definicją obiektu
 *
 * Przyjmuje: liczbę argumentów wywowłania i ich zawartość tekstową.
 * Zwraca:
 * FILE * - powodzenie
 * NULL - niepowowdzenie
 */
FILE *open_file(int argc, char **argv){
    if (argc < 2) {
        fprintf(stderr,"Za mala liczba argumentow - podaj sciezke do pliku z definicja obiektu.\n");
        return NULL;
    }
    FILE *in = fopen(argv[1], "r");

    if (in == NULL) {
        fprintf(stderr,"Nie udalo sie otworzyc pliku: %s\n", argv[1]);
        return NULL;
    }
    return in;

}
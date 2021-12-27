#include "file_manager.h"

/*
 * Otwiera plik z definicją obiektu
 * Zwraca:
 * FILE * - powodzenie
 * NULL - niepowowdzenie
 */
FILE *open_file(int argc, char **argv){
    if (argc < 2) {
        printf("Za mala liczba argumentow - podaj sciezke do pliku z definicja obiektu.\n");
        return NULL;
    }
    FILE *in = fopen(argv[1], "r");

    if (in == NULL) {
        printf("Nie udalo sie otworzyc pliku: %s\n", argv[1]);
        return NULL;
    }
    return in;

}
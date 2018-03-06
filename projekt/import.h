#include "typy.h"
#include <stdio.h>

int licz_szerokosc(FILE *plik);
int licz_wysokosc(FILE *plik);
void znajdz_wejscie(labirynt_t *moj_labirynt);
void znajdz_wyjscie(labirynt_t *moj_labirynt);
bool import(char *nazwa_pliku, labirynt_t *moj_labirynt);
bool czy_pola2x2(const labirynt_t *moj_labirynt);
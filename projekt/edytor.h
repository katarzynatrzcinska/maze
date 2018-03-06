#include "typy.h"

void wstaw_blok(labirynt_t *twoj_labirynt, const gracz_t *twoj_gracz, char blok);
bool sprawdz_krawedz(const labirynt_t *twoj_labirynt, const gracz_t *gracz);
void wypelnij_labirynt(labirynt_t *twoj_labirynt);
void ruch_na_planszy(const labirynt_t *moj_labirynt, gracz_t *gracz, bool przod);
bool zapisz_do_pliku(char *nazwa_pliku, const labirynt_t *twoj_labirynt);
char* wpisz_pobierz_nazwe_pliku(bool wpisz);
bool edytor(char *nazwa_pliku, const labirynt_t *moj_labirynt);
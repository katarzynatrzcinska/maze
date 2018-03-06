#include "typy.h"
#include <time.h>

void rysuj_labirynt(const labirynt_t *moj_labirynt);
void ustaw_gracza(const labirynt_t *moj_labirynt, gracz_t *gracz);
void rysuj_gracza(const gracz_t *gracz);
void obrot_gracza(gracz_t *gracz, kierunek_t kierunek_skretu);
bool sprawdz_kolizacje(const labirynt_t *moj_labirynt, const gracz_t *gracz);
void zrob_krok(gracz_t *gracz);
void obrot_gracza_o_180_stopni(gracz_t *gracz);
void porusz_graczem(const labirynt_t *moj_labirynt, gracz_t *gracz, int *liczba_krokow, bool przod);
void reset_gry(const labirynt_t *moj_labirynt, gracz_t *gracz, time_t *start, int *liczba_krokow);
bool wykryj_mete(const labirynt_t *moj_labirynt, const gracz_t *gracz, time_t start, time_t koniec, int liczba_krokow);
void wyswietl_pomoc();
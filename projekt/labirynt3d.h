#include "typy.h"

void rysuj_kolumne(char tekstura, char wykonczenie, int wysokosc);
void rysuj_trapez(int numer_bloku, char tekstura, strona_t strona, int *margines);
void rysuj_prostokat(int numer_bloku, char tekstura, strona_t strona, int *margines);
void rysuj_srodek(int numer_bloku, char tekstura, int *margines, int szerokosc);
void rysuj_bok(int numer_bloku, strona_t strona, int *margines);
void rysuj_labirynt_3d(const labirynt_t *moj_labirynt, const gracz_t *gracz);
void rysuj_drzwi(int szerokosc);
void otwieranie_drzwi(const labirynt_t *moj_labirynt, const gracz_t *gracz);
void zamykanie_drzwi(const labirynt_t *moj_labirynt, const gracz_t *gracz);
void otworz_zamknij_drzwi(const labirynt_t *moj_labirynt, const gracz_t *gracz);
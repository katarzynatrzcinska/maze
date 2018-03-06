#ifndef TYPY_H
#define TYPY_H

#define DROGA ' '
#define SCIANA1 '#'
#define SCIANA2 '%'
#define SCIANA3 '$'
#define SCIANA4 '@'
#define SCIANA5 '&'
#define DRZWI_O '?'
#define DRZWI_Z '!'

#define MARGINES_LEWY 60
#define MARGINES_GORNY 2

#define STRZALKA_W_DOL 0x50
#define STRZALKA_W_GORE 0x48
#define STRZALKA_W_LEWO 0x4b
#define STRZALKA_W_PRAWO 0x4d

#define OTWORZ_DRZWI 'd'
#define WCZYTAJ_LABIRYNT 'i'
#define OPUSC_PROGRAM 'q'
#define WYSWIETL_POMOC 'h'
#define WEJDZ_DO_EDYTORA 'e'
#define ODCZYTAJ_LABIRYNT 'o'
#define ZAPIS_DO_PLIKU 's'
#define RESTART_GRY 'r'
#define AKTYWUJ_ANIMACJE_RUCHU 'a'

#define WYKONCZENIE_LEWO '\\'
#define WYKONCZENIE_PRAWO '/'
#define WYKONCZENIE_LINIA_POZIOMA '_'
#define WYKONCZENIE_SPACJA ' '

#define GLEBIA 7
#define MARGINES_LEWY_3D 1
#define MARGINES_PRAWY_3D MARGINES_LEWY_3D + 51
#define WYSOKOSC_PODSTAWOWA 20
#define WYSOKOSC_PODSTAWOWA_PROSTOKATA 16

#define WSTAW_SCIANE_1 '1'
#define WSTAW_SCIANE_2 '2'
#define WSTAW_SCIANE_3 '3'
#define WSTAW_SCIANE_4 '4'
#define WSTAW_SCIANE_5 '5'
#define WSTAW_DROGE '6'
#define WSTAW_DRZWI_O '7'
#define WSTAW_DRZWI_Z '8'

enum kierunek_t{
	LEWO,
	PRAWO,
	GORA,
	DOL
};

enum strona_t{
	LEWA,
	PRAWA
};

typedef struct{
	int x;
	int y;
} pozycja_t;

typedef struct{
	char** plansza;
	int szerokosc;
	int wysokosc;
	pozycja_t pozycja_wejscia;
	pozycja_t pozycja_wyjscia;
} labirynt_t;

typedef struct{
	pozycja_t pozycja_gracza;
	kierunek_t kierunek_patrzenia;
} gracz_t;

#endif
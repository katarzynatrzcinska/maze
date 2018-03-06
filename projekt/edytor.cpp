#include "edytor.h"
#include "typy.h"
#include "conio2.h"
#include "labirynt2d.h"
#include "import.h"
#include <iostream>

using namespace std;

void wstaw_blok(labirynt_t *twoj_labirynt, const gracz_t *twoj_gracz, char blok){
	twoj_labirynt->plansza[twoj_gracz->pozycja_gracza.y][twoj_gracz->pozycja_gracza.x] = blok;
	rysuj_labirynt(twoj_labirynt);
}

bool sprawdz_krawedz(const labirynt_t *twoj_labirynt, const gracz_t *gracz){ // sprawdza, czy gracz wyszedl poza labirynt
	switch (gracz->kierunek_patrzenia){
	case GORA: if (gracz->pozycja_gracza.y - 1 >= 0) return true; break;
	case DOL: if (gracz->pozycja_gracza.y + 1 <= twoj_labirynt->wysokosc - 1) return true; break;
	case PRAWO: if (gracz->pozycja_gracza.x + 1 <= twoj_labirynt->szerokosc - 1) return true; break;
	case LEWO: if (gracz->pozycja_gracza.x - 1 >= 0) return true; break;
	}
	return false;
}

void wypelnij_labirynt(labirynt_t *twoj_labirynt){
	for (int w = 0; w<twoj_labirynt->wysokosc; w++)
	{
		for (int k = 0; k<twoj_labirynt->szerokosc; k++)
		{
			gotoxy(MARGINES_LEWY + k, MARGINES_GORNY + w);
			twoj_labirynt->plansza[w][k] = DROGA;
		}
	}
}

void ruch_na_planszy(const labirynt_t *moj_labirynt, gracz_t *gracz, bool przod){
	if (!przod) obrot_gracza_o_180_stopni(gracz); // obrot gracza o 180 stopni w celu sprawdzenia kolizji
	if (sprawdz_krawedz(moj_labirynt, gracz)){
		zrob_krok(gracz);
	}
	if (!przod) obrot_gracza_o_180_stopni(gracz); // powrot gracza do wczesniejszego ustawienia
	rysuj_gracza(gracz);
}

char* wpisz_pobierz_nazwe_pliku(bool wpisz){ 
	static char nazwa_pliku_s[128];
	if (wpisz){
		cout << "Podaj nazwe pliku: ";
		cin >> nazwa_pliku_s;
	}
	return nazwa_pliku_s;
}

bool zapisz_do_pliku(char *nazwa_pliku, labirynt_t *twoj_labirynt){
	if (!czy_pola2x2(twoj_labirynt)) {
		gotoxy(2, 5);
		if(nazwa_pliku == NULL)
			nazwa_pliku = wpisz_pobierz_nazwe_pliku(true); // gracz wpisuje nazwe pliku

		FILE *zapis;
		zapis = fopen(nazwa_pliku, "w");
		if (zapis == NULL)
			return false;
		char c;
		int w = 0, k = 0;
		while (w < twoj_labirynt->wysokosc){
			while (k < twoj_labirynt->szerokosc){
				switch (twoj_labirynt->plansza[w][k]){
				case DROGA: c = '0'; break;
				case SCIANA1: c = '1'; break;
				case SCIANA2: c = '2'; break;
				case SCIANA3: c = '3'; break;
				case SCIANA4: c = '4'; break;
				case SCIANA5: c = '5'; break;
				case DRZWI_O: c = '6'; break;
				case DRZWI_Z: c = '7'; break;
				}
				fprintf(zapis, "%c", c);
				k++;
			}
			fprintf(zapis, "\n");
			k = 0;
			w++;
		}
		fclose(zapis);
		gotoxy(2, 7);
		cout << "Zapis przebiegl pomyslnie.";
		gotoxy(2, 8);
		cout << "Wczytac podany labirynt? t/n";
		if (getch() == 't')
			return true; // zwraca prawde, kiedy gracz chce wczytac podany labirynt
	}
	else{
		gotoxy(2, 7);
		cout << "W labiryncie znajduja sie pola 2x2.";
		getch();
	}
	return false;
}

bool edytor(char *nazwa_pliku, const labirynt_t *moj_labirynt){
	clrscr();
	labirynt_t twoj_labirynt;
	gracz_t twoj_gracz;
	if (moj_labirynt == NULL) // sprawdza, czy plik jest nowy
	{
		int szerokosc, wysokosc;
		gotoxy(2, 2);
		cout << "Podaj szerokosc: ";
		cin >> szerokosc;
		gotoxy(2, 3);
		cout << "Podaj wysokosc: ";
		cin >> wysokosc;
		twoj_labirynt.szerokosc = szerokosc;
		twoj_labirynt.wysokosc = wysokosc;
		twoj_labirynt.plansza = (char**)malloc(twoj_labirynt.szerokosc*sizeof(char*));
		for (int i = 0; i < twoj_labirynt.szerokosc; i++){
			twoj_labirynt.plansza[i] = (char*)malloc(twoj_labirynt.wysokosc*sizeof(char));
		}
		if (twoj_labirynt.plansza == NULL) return false; // sprawdzamy, czy system operacyjny przydzielil zadana pamiec
		for (int i = 0; i < twoj_labirynt.szerokosc; i++){
			if (twoj_labirynt.plansza[i] == NULL) return false;
		}
		wypelnij_labirynt(&twoj_labirynt);
	}
	else{
		twoj_labirynt = *moj_labirynt; // kopia labiryntu
		twoj_labirynt.plansza = NULL;
		twoj_labirynt.plansza = (char**)malloc(moj_labirynt->szerokosc*sizeof(char*));
		for (int i = 0; i < moj_labirynt->szerokosc; i++){
			twoj_labirynt.plansza[i] = (char*)malloc(moj_labirynt->wysokosc*sizeof(char));
		}
		for (int w = 0; w<moj_labirynt->wysokosc; w++){
			for (int k = 0; k<moj_labirynt->szerokosc; k++){
				twoj_labirynt.plansza[w][k] = moj_labirynt->plansza[w][k];
			}
		}
	}
	twoj_gracz.pozycja_gracza.x = 0; // ustawienie gracza na polu 1x1
	twoj_gracz.pozycja_gracza.y = 0;
	twoj_gracz.kierunek_patrzenia = PRAWO;

	int znak;
	bool pomin_rysowanie_gracza = false;
	do {
		rysuj_labirynt(&twoj_labirynt);
		if (!pomin_rysowanie_gracza) rysuj_gracza(&twoj_gracz);
		pomin_rysowanie_gracza = false; // ???????????????
		znak = getch();
		if (znak == 0) { // jezeli strzalka
			znak = getch();
			switch (znak){
			case STRZALKA_W_GORE: ruch_na_planszy(&twoj_labirynt, &twoj_gracz, true); break;
			case STRZALKA_W_DOL: ruch_na_planszy(&twoj_labirynt, &twoj_gracz, false); break;
			case STRZALKA_W_LEWO: obrot_gracza(&twoj_gracz, LEWO); break;
			case STRZALKA_W_PRAWO: obrot_gracza(&twoj_gracz, PRAWO); break;
			}
		}
		else {
			pomin_rysowanie_gracza = true;
			switch (znak){
			case WSTAW_SCIANE_1: wstaw_blok(&twoj_labirynt, &twoj_gracz, SCIANA1); break;
			case WSTAW_SCIANE_2: wstaw_blok(&twoj_labirynt, &twoj_gracz, SCIANA2); break;
			case WSTAW_SCIANE_3: wstaw_blok(&twoj_labirynt, &twoj_gracz, SCIANA3); break;
			case WSTAW_SCIANE_4: wstaw_blok(&twoj_labirynt, &twoj_gracz, SCIANA4); break;
			case WSTAW_SCIANE_5: wstaw_blok(&twoj_labirynt, &twoj_gracz, SCIANA5); break;
			case WSTAW_DROGE: wstaw_blok(&twoj_labirynt, &twoj_gracz, DROGA); break;
			case WSTAW_DRZWI_O: wstaw_blok(&twoj_labirynt, &twoj_gracz, DRZWI_O); break;
			case WSTAW_DRZWI_Z: wstaw_blok(&twoj_labirynt, &twoj_gracz, DRZWI_Z); break;
			case WYSWIETL_POMOC: wyswietl_pomoc(); break;
			case ZAPIS_DO_PLIKU: if (zapisz_do_pliku(nazwa_pliku, &twoj_labirynt)) return true; 
								 else return false; 
								 break;
								
			}
		}
	} while (znak != OPUSC_PROGRAM);
	return false;
}
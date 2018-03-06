#include <iostream>
#include <stdio.h>
#include "typy.h"
#include "labirynt2d.h"
#include "conio2.h"

using namespace std;

void rysuj_labirynt(const labirynt_t *moj_labirynt)
{
	for (int w = 0; w<moj_labirynt->wysokosc; w++){
		for (int k = 0; k<moj_labirynt->szerokosc; k++){
			gotoxy(MARGINES_LEWY + k, MARGINES_GORNY + w);
			cout << moj_labirynt->plansza[w][k];
		}
	}
}

void ustaw_gracza(const labirynt_t *moj_labirynt, gracz_t *gracz){
	gracz->pozycja_gracza.x = moj_labirynt->pozycja_wejscia.x; // ustawienie gracza w pozycji wejscia z odpowiednim kierunkiem patrzenia
	gracz->pozycja_gracza.y = moj_labirynt->pozycja_wejscia.y;
	if (gracz->pozycja_gracza.x == 0) gracz->kierunek_patrzenia = PRAWO;
	if (gracz->pozycja_gracza.x == moj_labirynt->szerokosc - 1) gracz->kierunek_patrzenia = LEWO;
	if (gracz->pozycja_gracza.y == 0) gracz->kierunek_patrzenia = DOL;
	if (gracz->pozycja_gracza.y == moj_labirynt->wysokosc - 1) gracz->kierunek_patrzenia = GORA;
}

void rysuj_gracza(const gracz_t *gracz){
	gotoxy(gracz->pozycja_gracza.x + MARGINES_LEWY, gracz->pozycja_gracza.y + MARGINES_GORNY);
	switch (gracz->kierunek_patrzenia){
	case PRAWO: cout << ">"; break;
	case LEWO: cout << "<"; break;
	case DOL: cout << "v"; break;
	case GORA: cout << "^"; break;
	}
}

void obrot_gracza(gracz_t *gracz, kierunek_t kierunek_skretu){ // o 90 stopni
	switch (kierunek_skretu){
	case LEWO:
		switch (gracz->kierunek_patrzenia){
		case DOL: gracz->kierunek_patrzenia = PRAWO; break;
		case GORA: gracz->kierunek_patrzenia = LEWO; break;
		case LEWO: gracz->kierunek_patrzenia = DOL; break;
		case PRAWO: gracz->kierunek_patrzenia = GORA; break;
		} break;
	case PRAWO:
		switch (gracz->kierunek_patrzenia){
		case DOL: gracz->kierunek_patrzenia = LEWO; break;
		case GORA: gracz->kierunek_patrzenia = PRAWO; break;
		case LEWO: gracz->kierunek_patrzenia = GORA; break;
		case PRAWO: gracz->kierunek_patrzenia = DOL; break;
		} break;
	}
	rysuj_gracza(gracz);
}

bool sprawdz_kolizacje(const labirynt_t *moj_labirynt, const gracz_t *gracz){
	switch (gracz->kierunek_patrzenia){
	case GORA:
		if (gracz->pozycja_gracza.y - 1 < 0) return false; // uniemozliwienie wyjscia gracza poza labirynt
		switch (moj_labirynt->plansza[gracz->pozycja_gracza.y - 1][gracz->pozycja_gracza.x]){
		case DROGA: return true; break;
		case DRZWI_O: return true; break;
		default: return false; break; // zwraca falsz, jezeli napotyka na sciane
		}
	case DOL:
		if (gracz->pozycja_gracza.y + 1 > moj_labirynt->wysokosc - 1) return false;
		switch (moj_labirynt->plansza[gracz->pozycja_gracza.y + 1][gracz->pozycja_gracza.x]){
		case DROGA: return true; break;
		case DRZWI_O: return true; break;
		default: return false; break;
		}
	case PRAWO:
		if (gracz->pozycja_gracza.x + 1 > moj_labirynt->szerokosc - 1) return false;
		switch (moj_labirynt->plansza[gracz->pozycja_gracza.y][gracz->pozycja_gracza.x + 1]){
		case DROGA: return true; break;
		case DRZWI_O: return true; break;
		default: return false; break;
		}
	case LEWO:
		if (gracz->pozycja_gracza.x - 1 < 0) return false;
		switch (moj_labirynt->plansza[gracz->pozycja_gracza.y][gracz->pozycja_gracza.x - 1]){
		case DROGA: return true; break;
		case DRZWI_O: return true; break;
		default: return false; break;
		}
	}
	return false;
}

void zrob_krok(gracz_t *gracz){
	switch (gracz->kierunek_patrzenia){
	case GORA: gracz->pozycja_gracza.y--; break;
	case DOL: gracz->pozycja_gracza.y++; break;
	case PRAWO: gracz->pozycja_gracza.x++; break;
	case LEWO: gracz->pozycja_gracza.x--; break;
	}
}

void obrot_gracza_o_180_stopni(gracz_t *gracz){
	switch (gracz->kierunek_patrzenia){
	case DOL: gracz->kierunek_patrzenia = GORA; break;
	case GORA: gracz->kierunek_patrzenia = DOL; break;
	case LEWO: gracz->kierunek_patrzenia = PRAWO; break;
	case PRAWO: gracz->kierunek_patrzenia = LEWO; break;
	}
}

void porusz_graczem(const labirynt_t *moj_labirynt, gracz_t *gracz, int *liczba_krokow, bool przod){
	if (!przod) obrot_gracza_o_180_stopni(gracz); // obrot gracza o 180 stopni w celu sprawdzenia kolizji
	if (sprawdz_kolizacje(moj_labirynt, gracz)){
		zrob_krok(gracz);
		(*liczba_krokow)++;
	}
	if (!przod) obrot_gracza_o_180_stopni(gracz); // powrot gracza do wczesniejszego ustawienia
	rysuj_gracza(gracz);
}

void reset_gry(const labirynt_t *moj_labirynt, gracz_t *gracz, time_t *start, int *liczba_krokow){
	rysuj_labirynt(moj_labirynt);
	ustaw_gracza(moj_labirynt, gracz);
	rysuj_gracza(gracz);
	*liczba_krokow = 0;
	time(start);
}

bool wykryj_mete(const labirynt_t *moj_labirynt, const gracz_t *gracz, time_t start, time_t koniec, int liczba_krokow){
	if (gracz->pozycja_gracza.x == moj_labirynt->pozycja_wyjscia.x && gracz->pozycja_gracza.y == moj_labirynt->pozycja_wyjscia.y){
		clrscr(); 
		gotoxy(40, 12);
		cout << "Gratulacje! Wygrales/as!";
		gotoxy(20, 14);
		time(&koniec);
		cout << "Czas gry: " << koniec - start << endl;
		gotoxy(20, 15);
		cout << "Liczba krokow: " << liczba_krokow << endl;
		getch();
		return true;
	}
	return false;
}

void wyswietl_pomoc(){
	clrscr();
	gotoxy(3, 3);
	cout << "Strzalka do przodu nie zmienia kierunku gracza. Po jej kliknieciu gracz przesuwa sie w te strone, w ktora patrzy." << endl;
	cout << "Strzalka do tylu cofa gracza." << endl;
	cout << "Strzalki w lewo i w prawo obracaja gracza o 90 stopni." << endl;
	cout << "d - otwieranie/zamykanie drzwi" << endl;
	cout << "o - wczytanie Twojego labiryntu" << endl;
	cout << endl;
	cout << "Powodzenia! May the force be with you!";
	getch();
}
#include <iostream>
#include <stdio.h>
#include "time.h"
#include "typy.h"
#include "labirynt3d.h"
#include "conio2.h"

using namespace std;

void rysuj_kolumne(char tekstura, char wykonczenie, int wysokosc){
	if (wykonczenie == WYKONCZENIE_LINIA_POZIOMA){
		cout << WYKONCZENIE_LINIA_POZIOMA;
		gotoxy(wherex() - 1, wherey() + 1);
		cout << " ";
		gotoxy(wherex() - 1, wherey() + 1);
		for (int i = 0; i < wysokosc - 3; i++){
			cout << tekstura;
			gotoxy(wherex() - 1, wherey() + 1);
		}
		cout << WYKONCZENIE_LINIA_POZIOMA;
	}
	else if (wykonczenie == WYKONCZENIE_PRAWO){
		gotoxy(wherex(), wherey() + 1);
		cout << WYKONCZENIE_PRAWO;
		gotoxy(wherex() - 1, wherey() + 1);
		for (int i = 0; i < wysokosc - 3; i++){
			cout << tekstura;
			gotoxy(wherex() - 1, wherey() + 1);
		}
		cout << WYKONCZENIE_LEWO;
	}
	else if (wykonczenie == WYKONCZENIE_LEWO){
		gotoxy(wherex(), wherey() + 1);
		cout << WYKONCZENIE_LEWO;
		gotoxy(wherex() - 1, wherey() + 1);
		for (int i = 0; i < wysokosc - 3; i++){
			cout << tekstura;
			gotoxy(wherex() - 1, wherey() + 1);
		}
		cout << WYKONCZENIE_PRAWO;
	}
	else{
		cout << WYKONCZENIE_SPACJA;
		gotoxy(wherex() - 1, wherey() + 1);
		for (int i = 0; i < wysokosc - 1; i++){
			cout << tekstura;
			gotoxy(wherex() - 1, wherey() + 1);
		}
	}
}

void rysuj_trapez(int numer_bloku, char tekstura, strona_t strona, int *margines){ // funkcja rysujaca sciany
	int wysokosc, szerokosc;
	if (numer_bloku == 1){
		wysokosc = WYSOKOSC_PODSTAWOWA;
		szerokosc = 5;
		gotoxy(1 + *margines, MARGINES_GORNY - 1);
		rysuj_kolumne('|', WYKONCZENIE_SPACJA, wysokosc); // narysowanie pierwszej lub ostatniej kolumny 
		if (strona == LEWA) (*margines)++;
		else (*margines)--;
	}
	else{
		wysokosc = WYSOKOSC_PODSTAWOWA - 2 * numer_bloku;
		szerokosc = 5 - (numer_bloku / 2);
	}
	if (strona == LEWA){ // rysowanie scian z lewej strony widoku 3D
		for (int i = 0; i < szerokosc; i++){
			gotoxy(1 + i + *margines, (WYSOKOSC_PODSTAWOWA - wysokosc) / 2 + MARGINES_GORNY - 1);
			if (i == 1 && numer_bloku == 1){
				rysuj_kolumne(tekstura, WYKONCZENIE_LEWO, wysokosc);
				wysokosc -= 2;
			}
			else if (i == szerokosc - 1){
				rysuj_kolumne('|', WYKONCZENIE_LEWO, wysokosc);
			}
			else
				rysuj_kolumne(tekstura, WYKONCZENIE_LINIA_POZIOMA, wysokosc);
		}
		*margines += szerokosc;
	}
	else{ // rysowanie scian z prawej strony widoku 3D
		for (int i = 0; i < szerokosc; i++){
			gotoxy(1 - i + *margines, (WYSOKOSC_PODSTAWOWA - wysokosc) / 2 + MARGINES_GORNY - 1);
			if (i == 1 && numer_bloku == 1){
				rysuj_kolumne(tekstura, WYKONCZENIE_PRAWO, wysokosc);
				wysokosc -= 2;
			}
			else if (i == szerokosc - 1){
				rysuj_kolumne('|', WYKONCZENIE_PRAWO, wysokosc);
			}
			else
				rysuj_kolumne(tekstura, WYKONCZENIE_LINIA_POZIOMA, wysokosc);
		}
		*margines -= szerokosc;
	}
}

void rysuj_prostokat(int numer_bloku, char tekstura, strona_t strona, int *margines){ // funkcja rysujaca przejscia
	int wysokosc, szerokosc;
	if (numer_bloku == 1){
		wysokosc = WYSOKOSC_PODSTAWOWA_PROSTOKATA;
		szerokosc = 5;
		gotoxy(1 + *margines, MARGINES_GORNY + 1);
		rysuj_kolumne('|', WYKONCZENIE_SPACJA, wysokosc); // narysowanie pierwszej lub ostatniej kolumny 
		if (strona == LEWA) (*margines)++;
		else (*margines)--;
	}
	else{
		wysokosc = WYSOKOSC_PODSTAWOWA_PROSTOKATA - 2 * (numer_bloku - 1);
		szerokosc = 5 - (numer_bloku / 2);
	}
	if (strona == LEWA){  // rysowanie przejscia z lewej strony widoku 3D
		for (int i = 0; i < szerokosc; i++){
			gotoxy(1 + i + *margines, (WYSOKOSC_PODSTAWOWA_PROSTOKATA - wysokosc) / 2 + MARGINES_GORNY + 1);
			if (i == szerokosc - 1){
				rysuj_kolumne('|', WYKONCZENIE_SPACJA, wysokosc);
			}
			else
				rysuj_kolumne(tekstura, WYKONCZENIE_LINIA_POZIOMA, wysokosc);
		}
		*margines += szerokosc;
	}
	else{ // rysowanie przejscia z prawej strony widoku 3D
		for (int i = 0; i < szerokosc; i++){
			gotoxy(1 - i + *margines, (WYSOKOSC_PODSTAWOWA_PROSTOKATA - wysokosc) / 2 + MARGINES_GORNY + 1);
			if (i == szerokosc - 1){
				rysuj_kolumne('|', WYKONCZENIE_SPACJA, wysokosc);
			}
			else
				rysuj_kolumne(tekstura, WYKONCZENIE_LINIA_POZIOMA, wysokosc);
		}
		*margines -= szerokosc;
	}
}

void rysuj_srodek(int numer_bloku, char tekstura, int *margines, int szerokosc){
	int wysokosc;
	if (numer_bloku == 1){
		wysokosc = WYSOKOSC_PODSTAWOWA;
		szerokosc--;
		gotoxy(1 + *margines, MARGINES_GORNY - 1);
		rysuj_kolumne('|', WYKONCZENIE_SPACJA, wysokosc);
		(*margines)++;
	}
	else{
		wysokosc = WYSOKOSC_PODSTAWOWA - 2 * numer_bloku;
	}
	for (int i = 0; i < szerokosc; i++){
		gotoxy(1 + i + *margines, (WYSOKOSC_PODSTAWOWA - wysokosc) / 2 + MARGINES_GORNY - 1);
		rysuj_kolumne(tekstura, WYKONCZENIE_LINIA_POZIOMA, wysokosc);
	}
	if (numer_bloku == 1){ 
		gotoxy(1 + *margines + szerokosc, MARGINES_GORNY - 1);
		rysuj_kolumne('|', WYKONCZENIE_SPACJA, wysokosc);
		(*margines)++;
	}
	*margines += szerokosc;
}

void rysuj_bok(int numer_bloku, strona_t strona, int *margines){ // funkcja rysujaca bok (kolumne)
	int wysokosc, szerokosc;
	wysokosc = WYSOKOSC_PODSTAWOWA_PROSTOKATA - 2 * (numer_bloku - 1);
	szerokosc = 5 - (numer_bloku / 2);
	if (strona == LEWA){  // rysowanie boku z lewej strony widoku 3D
		for (int i = 0; i < szerokosc; i++){
			gotoxy(1 + i + *margines, (WYSOKOSC_PODSTAWOWA_PROSTOKATA - wysokosc) / 2 + MARGINES_GORNY + 1);
			if (i == szerokosc - 1){
				rysuj_kolumne('|', WYKONCZENIE_SPACJA, wysokosc);
			}
		}
		*margines += szerokosc;
	}
	else{ // rysowanie boku z prawej strony widoku 3D
		for (int i = 0; i < szerokosc; i++){
			gotoxy(1 - i + *margines, (WYSOKOSC_PODSTAWOWA_PROSTOKATA - wysokosc) / 2 + MARGINES_GORNY + 1);
			if (i == szerokosc - 1){
				rysuj_kolumne('|', WYKONCZENIE_SPACJA, wysokosc);
			}
		}
		*margines -= szerokosc;
	}
}

void rysuj_labirynt_3d(const labirynt_t *moj_labirynt, const gracz_t *gracz){
	int margines_lewy = MARGINES_LEWY_3D;
	int margines_prawy = MARGINES_PRAWY_3D;
	int aktualna_glebia = 1;

	switch (gracz->kierunek_patrzenia){
	case GORA:
		while (gracz->pozycja_gracza.y - aktualna_glebia >= 0 // wykonuje sie dopoki rysowanie nie osiagnie gornej granicy mapy
			&& (moj_labirynt->plansza[gracz->pozycja_gracza.y - aktualna_glebia][gracz->pozycja_gracza.x] == DROGA // dodatkowo na danej glebi musi byc droga
			|| moj_labirynt->plansza[gracz->pozycja_gracza.y - aktualna_glebia][gracz->pozycja_gracza.x] == DRZWI_O) // lub drzwi otwarte
			&& aktualna_glebia <= GLEBIA) { //

			if (moj_labirynt->plansza[gracz->pozycja_gracza.y - aktualna_glebia][gracz->pozycja_gracza.x - 1] == DROGA
				|| moj_labirynt->plansza[gracz->pozycja_gracza.y - aktualna_glebia][gracz->pozycja_gracza.x - 1] == DRZWI_O) { // jezeli na danej glebi sa drzwi otwarte lub droga
				if (moj_labirynt->plansza[gracz->pozycja_gracza.y - aktualna_glebia - 1][gracz->pozycja_gracza.x - 1] == DROGA // to sprawdz czy po lewej i jedno blizej nas wzgledem aktualnej glebi jest droga lub drzwi otwarte
					|| moj_labirynt->plansza[gracz->pozycja_gracza.y - aktualna_glebia - 1][gracz->pozycja_gracza.x - 1] == DRZWI_O)
					rysuj_bok(aktualna_glebia, LEWA, &margines_lewy); // jezeli po lewej stronie s¹ dwa bloki puste obok siebie nie rysuje sciany
				else
					rysuj_prostokat(aktualna_glebia, moj_labirynt->plansza[gracz->pozycja_gracza.y - aktualna_glebia - 1][gracz->pozycja_gracza.x - 1], LEWA, &margines_lewy); // rysuje wciecie
			}
			else
				rysuj_trapez(aktualna_glebia, moj_labirynt->plansza[gracz->pozycja_gracza.y - aktualna_glebia][gracz->pozycja_gracza.x - 1], LEWA, &margines_lewy); 

			// odbicie symetryczne
			if (moj_labirynt->plansza[gracz->pozycja_gracza.y - aktualna_glebia][gracz->pozycja_gracza.x + 1] == DROGA
				|| moj_labirynt->plansza[gracz->pozycja_gracza.y - aktualna_glebia][gracz->pozycja_gracza.x + 1] == DRZWI_O) {
				if (moj_labirynt->plansza[gracz->pozycja_gracza.y - aktualna_glebia - 1][gracz->pozycja_gracza.x + 1] == DROGA
					|| moj_labirynt->plansza[gracz->pozycja_gracza.y - aktualna_glebia - 1][gracz->pozycja_gracza.x + 1] == DRZWI_O)
					rysuj_bok(aktualna_glebia, PRAWA, &margines_prawy);
				else
					rysuj_prostokat(aktualna_glebia, moj_labirynt->plansza[gracz->pozycja_gracza.y - aktualna_glebia - 1][gracz->pozycja_gracza.x + 1], PRAWA, &margines_prawy);
			}
			else
				rysuj_trapez(aktualna_glebia, moj_labirynt->plansza[gracz->pozycja_gracza.y - aktualna_glebia][gracz->pozycja_gracza.x + 1], PRAWA, &margines_prawy);
			aktualna_glebia++; // przesuniecie rysowania jedno w przod
		}
		// jezeli natrafi na przeszkode lub osiagnie limit glebi (7) to wychodzi z petli
		// i decyduje czy rysowac srodek (nie jezeli osiagnelo maksymalna glebokosc lub krawedz mapy)
		if (gracz->pozycja_gracza.y - aktualna_glebia >= 0
			&& moj_labirynt->plansza[gracz->pozycja_gracza.y - aktualna_glebia][gracz->pozycja_gracza.x] != DROGA
			&& moj_labirynt->plansza[gracz->pozycja_gracza.y - aktualna_glebia][gracz->pozycja_gracza.x] != DRZWI_O)
			rysuj_srodek(aktualna_glebia, moj_labirynt->plansza[gracz->pozycja_gracza.y - aktualna_glebia][gracz->pozycja_gracza.x], &margines_lewy, margines_prawy - margines_lewy + 1);
		break;

	case DOL:
		while (gracz->pozycja_gracza.y + aktualna_glebia < moj_labirynt->wysokosc
			&& (moj_labirynt->plansza[gracz->pozycja_gracza.y + aktualna_glebia][gracz->pozycja_gracza.x] == DROGA
			|| moj_labirynt->plansza[gracz->pozycja_gracza.y + aktualna_glebia][gracz->pozycja_gracza.x] == DRZWI_O)
			&& aktualna_glebia <= GLEBIA){
			if (moj_labirynt->plansza[gracz->pozycja_gracza.y + aktualna_glebia][gracz->pozycja_gracza.x + 1] == DROGA
				|| moj_labirynt->plansza[gracz->pozycja_gracza.y + aktualna_glebia][gracz->pozycja_gracza.x + 1] == DRZWI_O){
				if (moj_labirynt->plansza[gracz->pozycja_gracza.y + aktualna_glebia + 1][gracz->pozycja_gracza.x + 1] == DROGA
					|| moj_labirynt->plansza[gracz->pozycja_gracza.y + aktualna_glebia + 1][gracz->pozycja_gracza.x + 1] == DRZWI_O)
					rysuj_bok(aktualna_glebia, LEWA, &margines_lewy);
				else
					rysuj_prostokat(aktualna_glebia, moj_labirynt->plansza[gracz->pozycja_gracza.y + aktualna_glebia + 1][gracz->pozycja_gracza.x + 1], LEWA, &margines_lewy);
			}
			else
				rysuj_trapez(aktualna_glebia, moj_labirynt->plansza[gracz->pozycja_gracza.y + aktualna_glebia][gracz->pozycja_gracza.x + 1], LEWA, &margines_lewy);

			if (moj_labirynt->plansza[gracz->pozycja_gracza.y + aktualna_glebia][gracz->pozycja_gracza.x - 1] == DROGA
				|| moj_labirynt->plansza[gracz->pozycja_gracza.y + aktualna_glebia][gracz->pozycja_gracza.x - 1] == DRZWI_O){
				if (moj_labirynt->plansza[gracz->pozycja_gracza.y + aktualna_glebia + 1][gracz->pozycja_gracza.x - 1] == DROGA
					|| moj_labirynt->plansza[gracz->pozycja_gracza.y + aktualna_glebia + 1][gracz->pozycja_gracza.x - 1] == DRZWI_O)
					rysuj_bok(aktualna_glebia, PRAWA, &margines_prawy);
				else
					rysuj_prostokat(aktualna_glebia, moj_labirynt->plansza[gracz->pozycja_gracza.y + aktualna_glebia + 1][gracz->pozycja_gracza.x - 1], PRAWA, &margines_prawy);
			}
			else
				rysuj_trapez(aktualna_glebia, moj_labirynt->plansza[gracz->pozycja_gracza.y + aktualna_glebia][gracz->pozycja_gracza.x - 1], PRAWA, &margines_prawy);
			aktualna_glebia++;
		}
		if (gracz->pozycja_gracza.y + aktualna_glebia < moj_labirynt->wysokosc
			&& moj_labirynt->plansza[gracz->pozycja_gracza.y + aktualna_glebia][gracz->pozycja_gracza.x] != DROGA
			&& moj_labirynt->plansza[gracz->pozycja_gracza.y + aktualna_glebia][gracz->pozycja_gracza.x] != DRZWI_O)
			rysuj_srodek(aktualna_glebia, moj_labirynt->plansza[gracz->pozycja_gracza.y + aktualna_glebia][gracz->pozycja_gracza.x], &margines_lewy, margines_prawy - margines_lewy + 1);
		break;
	case PRAWO:
		while (gracz->pozycja_gracza.x + aktualna_glebia < moj_labirynt->szerokosc
			&& (moj_labirynt->plansza[gracz->pozycja_gracza.y][gracz->pozycja_gracza.x + aktualna_glebia] == DROGA
			|| moj_labirynt->plansza[gracz->pozycja_gracza.y][gracz->pozycja_gracza.x + aktualna_glebia] == DRZWI_O)
			&& aktualna_glebia <= GLEBIA){
			if (moj_labirynt->plansza[gracz->pozycja_gracza.y - 1][gracz->pozycja_gracza.x + aktualna_glebia] == DROGA
				|| moj_labirynt->plansza[gracz->pozycja_gracza.y - 1][gracz->pozycja_gracza.x + aktualna_glebia] == DRZWI_O){
				if (moj_labirynt->plansza[gracz->pozycja_gracza.y - 1][gracz->pozycja_gracza.x + aktualna_glebia + 1] == DROGA
					|| moj_labirynt->plansza[gracz->pozycja_gracza.y - 1][gracz->pozycja_gracza.x + aktualna_glebia + 1] == DRZWI_O)
					rysuj_bok(aktualna_glebia, LEWA, &margines_lewy);
				else
					rysuj_prostokat(aktualna_glebia, moj_labirynt->plansza[gracz->pozycja_gracza.y - 1][gracz->pozycja_gracza.x + aktualna_glebia + 1], LEWA, &margines_lewy);
			}
			else
				rysuj_trapez(aktualna_glebia, moj_labirynt->plansza[gracz->pozycja_gracza.y - 1][gracz->pozycja_gracza.x + aktualna_glebia], LEWA, &margines_lewy);

			if (moj_labirynt->plansza[gracz->pozycja_gracza.y + 1][gracz->pozycja_gracza.x + aktualna_glebia] == DROGA
				|| moj_labirynt->plansza[gracz->pozycja_gracza.y + 1][gracz->pozycja_gracza.x + aktualna_glebia] == DRZWI_O){
				if (moj_labirynt->plansza[gracz->pozycja_gracza.y + 1][gracz->pozycja_gracza.x + aktualna_glebia + 1] == DROGA
					|| moj_labirynt->plansza[gracz->pozycja_gracza.y + 1][gracz->pozycja_gracza.x + aktualna_glebia + 1] == DRZWI_O)
					rysuj_bok(aktualna_glebia, PRAWA, &margines_prawy);
				else
					rysuj_prostokat(aktualna_glebia, moj_labirynt->plansza[gracz->pozycja_gracza.y + 1][gracz->pozycja_gracza.x + aktualna_glebia + 1], PRAWA, &margines_prawy);
			}
			else
				rysuj_trapez(aktualna_glebia, moj_labirynt->plansza[gracz->pozycja_gracza.y + 1][gracz->pozycja_gracza.x + aktualna_glebia], PRAWA, &margines_prawy);

			aktualna_glebia++;
		}
		if (gracz->pozycja_gracza.x + aktualna_glebia < moj_labirynt->szerokosc
			&& moj_labirynt->plansza[gracz->pozycja_gracza.y][gracz->pozycja_gracza.x + aktualna_glebia] != DROGA
			&& moj_labirynt->plansza[gracz->pozycja_gracza.y][gracz->pozycja_gracza.x + aktualna_glebia] != DRZWI_O)
			rysuj_srodek(aktualna_glebia, moj_labirynt->plansza[gracz->pozycja_gracza.y][gracz->pozycja_gracza.x + aktualna_glebia], &margines_lewy, margines_prawy - margines_lewy + 1);
		break;

	case LEWO:
		while (gracz->pozycja_gracza.x - aktualna_glebia >= 0
			&& (moj_labirynt->plansza[gracz->pozycja_gracza.y][gracz->pozycja_gracza.x - aktualna_glebia] == DROGA
			|| moj_labirynt->plansza[gracz->pozycja_gracza.y][gracz->pozycja_gracza.x - aktualna_glebia] == DRZWI_O)
			&& aktualna_glebia <= GLEBIA){
			if (moj_labirynt->plansza[gracz->pozycja_gracza.y + 1][gracz->pozycja_gracza.x - aktualna_glebia] == DROGA
				|| moj_labirynt->plansza[gracz->pozycja_gracza.y + 1][gracz->pozycja_gracza.x - aktualna_glebia] == DRZWI_O){
				if (moj_labirynt->plansza[gracz->pozycja_gracza.y + 1][gracz->pozycja_gracza.x - aktualna_glebia - 1] == DROGA
					|| moj_labirynt->plansza[gracz->pozycja_gracza.y + 1][gracz->pozycja_gracza.x - aktualna_glebia - 1] == DRZWI_O)
					rysuj_bok(aktualna_glebia, LEWA, &margines_lewy);
				else
					rysuj_prostokat(aktualna_glebia, moj_labirynt->plansza[gracz->pozycja_gracza.y + 1][gracz->pozycja_gracza.x - aktualna_glebia - 1], LEWA, &margines_lewy);
			}
			else
				rysuj_trapez(aktualna_glebia, moj_labirynt->plansza[gracz->pozycja_gracza.y + 1][gracz->pozycja_gracza.x - aktualna_glebia], LEWA, &margines_lewy);

			if (moj_labirynt->plansza[gracz->pozycja_gracza.y - 1][gracz->pozycja_gracza.x - aktualna_glebia] == DROGA
				|| moj_labirynt->plansza[gracz->pozycja_gracza.y - 1][gracz->pozycja_gracza.x - aktualna_glebia] == DRZWI_O){
				if (moj_labirynt->plansza[gracz->pozycja_gracza.y - 1][gracz->pozycja_gracza.x - aktualna_glebia - 1] == DROGA
					|| moj_labirynt->plansza[gracz->pozycja_gracza.y - 1][gracz->pozycja_gracza.x - aktualna_glebia - 1] == DRZWI_O)
					rysuj_bok(aktualna_glebia, PRAWA, &margines_prawy);
				else
					rysuj_prostokat(aktualna_glebia, moj_labirynt->plansza[gracz->pozycja_gracza.y - 1][gracz->pozycja_gracza.x - aktualna_glebia - 1], PRAWA, &margines_prawy);
			}
			else
				rysuj_trapez(aktualna_glebia, moj_labirynt->plansza[gracz->pozycja_gracza.y - 1][gracz->pozycja_gracza.x - aktualna_glebia], PRAWA, &margines_prawy);
			aktualna_glebia++;
		}
		if (gracz->pozycja_gracza.x - aktualna_glebia >= 0
			&& moj_labirynt->plansza[gracz->pozycja_gracza.y][gracz->pozycja_gracza.x - aktualna_glebia] != DROGA
			&& moj_labirynt->plansza[gracz->pozycja_gracza.y][gracz->pozycja_gracza.x - aktualna_glebia] != DRZWI_O)
			rysuj_srodek(aktualna_glebia, moj_labirynt->plansza[gracz->pozycja_gracza.y][gracz->pozycja_gracza.x - aktualna_glebia], &margines_lewy, margines_prawy - margines_lewy + 1);
		break;
	}
}

void rysuj_drzwi(int szerokosc){
	for (int i = 1; i < szerokosc; i++){
		gotoxy(1 + MARGINES_LEWY_3D + i, MARGINES_GORNY - 1);
		rysuj_kolumne(DRZWI_Z, WYKONCZENIE_LINIA_POZIOMA, WYSOKOSC_PODSTAWOWA);
	}
}

void otwieranie_drzwi(const labirynt_t *moj_labirynt, const gracz_t *gracz){
	int klatki = 5;
	double czas = 0.1;
	int szerokosc = MARGINES_PRAWY_3D - MARGINES_LEWY_3D;
	for (int i = klatki; i > 0; i--){
		clrscr();
		rysuj_labirynt_3d(moj_labirynt, gracz);
		int start = clock();
		rysuj_drzwi((szerokosc / klatki)*i);
		while (clock() - start < czas * CLOCKS_PER_SEC){}
	}
	clrscr();
	rysuj_labirynt_3d(moj_labirynt, gracz);
}

void zamykanie_drzwi(const labirynt_t *moj_labirynt, const gracz_t *gracz){
	double czas = 0.1;
	int szerokosc = MARGINES_PRAWY_3D - MARGINES_LEWY_3D;
	for (int klatki = 5; klatki>0; klatki--){
		int start = clock();
		rysuj_drzwi(szerokosc / klatki);
		while (clock() - start < czas * CLOCKS_PER_SEC){}
	}
}

void otworz_zamknij_drzwi(const labirynt_t *moj_labirynt, const gracz_t *gracz){
	switch (gracz->kierunek_patrzenia){
	case GORA:
		if (moj_labirynt->plansza[gracz->pozycja_gracza.y - 1][gracz->pozycja_gracza.x] == DRZWI_Z){
			moj_labirynt->plansza[gracz->pozycja_gracza.y - 1][gracz->pozycja_gracza.x] = DRZWI_O;
			otwieranie_drzwi(moj_labirynt, gracz);
		}
		else if (moj_labirynt->plansza[gracz->pozycja_gracza.y - 1][gracz->pozycja_gracza.x] == DRZWI_O){
			moj_labirynt->plansza[gracz->pozycja_gracza.y - 1][gracz->pozycja_gracza.x] = DRZWI_Z;
			zamykanie_drzwi(moj_labirynt, gracz);
		}
	case DOL:
		if (moj_labirynt->plansza[gracz->pozycja_gracza.y + 1][gracz->pozycja_gracza.x] == DRZWI_Z){
			moj_labirynt->plansza[gracz->pozycja_gracza.y + 1][gracz->pozycja_gracza.x] = DRZWI_O;
			otwieranie_drzwi(moj_labirynt, gracz);
		}
		else if (moj_labirynt->plansza[gracz->pozycja_gracza.y + 1][gracz->pozycja_gracza.x] == DRZWI_O){
			moj_labirynt->plansza[gracz->pozycja_gracza.y + 1][gracz->pozycja_gracza.x] = DRZWI_Z;
			zamykanie_drzwi(moj_labirynt, gracz);
		}
	case PRAWO:
		if (moj_labirynt->plansza[gracz->pozycja_gracza.y][gracz->pozycja_gracza.x + 1] == DRZWI_Z){
			moj_labirynt->plansza[gracz->pozycja_gracza.y][gracz->pozycja_gracza.x + 1] = DRZWI_O;
			otwieranie_drzwi(moj_labirynt, gracz);
		}
		else if (moj_labirynt->plansza[gracz->pozycja_gracza.y][gracz->pozycja_gracza.x + 1] == DRZWI_O){
			moj_labirynt->plansza[gracz->pozycja_gracza.y][gracz->pozycja_gracza.x + 1] = DRZWI_Z;
			zamykanie_drzwi(moj_labirynt, gracz);
		}
	case LEWO:
		if (moj_labirynt->plansza[gracz->pozycja_gracza.y][gracz->pozycja_gracza.x - 1] == DRZWI_Z){
			moj_labirynt->plansza[gracz->pozycja_gracza.y][gracz->pozycja_gracza.x - 1] = DRZWI_O;
			otwieranie_drzwi(moj_labirynt, gracz);
		}
		else if (moj_labirynt->plansza[gracz->pozycja_gracza.y][gracz->pozycja_gracza.x - 1] == DRZWI_O){
			moj_labirynt->plansza[gracz->pozycja_gracza.y][gracz->pozycja_gracza.x - 1] = DRZWI_Z;
			zamykanie_drzwi(moj_labirynt, gracz);
		}
	}
}
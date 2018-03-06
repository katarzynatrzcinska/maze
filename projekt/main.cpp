#include <iostream>
#include <stdio.h>
#include <time.h>
#include "conio2.h"
#include "typy.h"
#include "import.h"
#include "edytor.h"
#include "labirynt2d.h"
#include "labirynt3d.h"

using namespace std;

int main(){
	settitle("Katarzyna Trzcinska 160871");
	textbackground(BLACK);
	textcolor(LIGHTCYAN);

	char plik[128] = "labirynt.txt";
	bool pomin_rysowanie = false;
	labirynt_t moj_labirynt;
	moj_labirynt.plansza = NULL;
	gracz_t gracz;
	time_t start, koniec;
	int liczba_krokow = 0;

	import(plik, &moj_labirynt);
	reset_gry(&moj_labirynt, &gracz, &start, &liczba_krokow);
	int znak;
	do {
		if (!pomin_rysowanie) clrscr(); // pominiêcie dwukrotnego rysowania zamkniêtych drzwi
		rysuj_labirynt(&moj_labirynt);
		rysuj_gracza(&gracz);
		if (!pomin_rysowanie) { 
			rysuj_labirynt_3d(&moj_labirynt, &gracz);
		} else pomin_rysowanie = false;
		gotoxy(2, 23);
		time(&koniec);
		cout << "Czas gry: " << koniec - start << endl;
		gotoxy(2, 24);
		cout << "Liczba krokow: " << liczba_krokow << endl;
		gotoxy(35, 23);
		cout << "h - wyswietl pomoc" << endl;
		gotoxy(35, 24);
		cout << "r - reset gry" << endl;
		gotoxy(35, 25);
		cout << "q - opusc gre" << endl;
		znak = getch();
		if (znak == 0) { // jezeli strzalka
			znak = getch();
			switch (znak){
			case STRZALKA_W_GORE: porusz_graczem(&moj_labirynt, &gracz, &liczba_krokow, true); break;
			case STRZALKA_W_DOL: porusz_graczem(&moj_labirynt, &gracz, &liczba_krokow, false); break;
			case STRZALKA_W_LEWO: obrot_gracza(&gracz, LEWO); break;
			case STRZALKA_W_PRAWO: obrot_gracza(&gracz, PRAWO); break;
			}
		}
		else {
			switch (znak){
			case RESTART_GRY: reset_gry(&moj_labirynt, &gracz, &start, &liczba_krokow); break;
			case OTWORZ_DRZWI: otworz_zamknij_drzwi(&moj_labirynt, &gracz); pomin_rysowanie = true; break;
			case WYSWIETL_POMOC: wyswietl_pomoc(); break;
			case WCZYTAJ_LABIRYNT: 
				import("labirynt.txt", &moj_labirynt);
				reset_gry(&moj_labirynt, &gracz, &start, &liczba_krokow);
				break;
			case ODCZYTAJ_LABIRYNT:
				clrscr();
				gotoxy(2, 2);
				cout << "Podaj nazwe pliku: ";
				cin >> plik;
				if (import(plik, &moj_labirynt)){
					reset_gry(&moj_labirynt, &gracz, &start, &liczba_krokow);
				}
				else {
					gotoxy(2, 3);
					cout << "Podany plik nie istnieje." << endl;
					getch();
				}
				break;
			case WEJDZ_DO_EDYTORA:
				clrscr();
				gotoxy(2, 2);
				cout << "Czy chcesz edytowac biezacy labirynt? t/n";
				znak = getch();
				if (znak == 't') {
					if (edytor(plik, &moj_labirynt)){ // edytowanie biezacego labiryntu
						import(plik, &moj_labirynt);
						reset_gry(&moj_labirynt, &gracz, &start, &liczba_krokow);
					}
				}
				else {
					labirynt_t twoj_labirynt; // stworzenie nowego labiryntu do edycji
					twoj_labirynt.plansza = NULL;
					if (edytor(NULL, NULL)){
						char *nazwa_pliku;
						nazwa_pliku = wpisz_pobierz_nazwe_pliku(false);
						int i;
						for (i = 0; nazwa_pliku[i] != '\0'; i++){
							plik[i] = *(nazwa_pliku+i);
						}
						plik[i] = '\0';
						import(plik, &moj_labirynt);
						reset_gry(&moj_labirynt, &gracz, &start, &liczba_krokow);
					}
				}
				break;
			}
		}
		if (wykryj_mete(&moj_labirynt, &gracz, start, koniec, liczba_krokow)) reset_gry(&moj_labirynt, &gracz, &start, &liczba_krokow);
	} while (znak != OPUSC_PROGRAM);

	if (moj_labirynt.plansza != NULL){ // zwolnienie pamiêci
		for (int i = 0; i < moj_labirynt.szerokosc; i++)
			free(moj_labirynt.plansza[i]);
		free(moj_labirynt.plansza);
	}

	return 0;
}
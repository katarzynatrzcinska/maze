#include <iostream>
#include <stdio.h>
#include "typy.h"
#include "import.h"

int licz_szerokosc(FILE *plik){ // uchwyt na plik
	int szerokosc = 0;
	char c = fgetc(plik);
	while (c != '\n' && c != '\r'){
		szerokosc++;
		c = fgetc(plik);
	}
	return szerokosc;
}

int licz_wysokosc(FILE *plik){
	fseek(plik, 0, SEEK_SET);
	int wysokosc = 0;
	char tab[128];
	while (fscanf(plik, "%s", tab) > 0){
		wysokosc++;
	}
	return wysokosc;
}

void znajdz_wejscie(labirynt_t *moj_labirynt){
	for (int w = moj_labirynt->wysokosc - 1; w >= 0; w--){
		for (int k = moj_labirynt->szerokosc - 1; k >= 0; k--){
			if (w == 0 || w == moj_labirynt->wysokosc - 1 || k == 0 || k == moj_labirynt->szerokosc - 1){
				if (moj_labirynt->plansza[w][k] == DROGA){
					moj_labirynt->pozycja_wejscia.x = k;
					moj_labirynt->pozycja_wejscia.y = w;
				}
			}
		}
	}
}

void znajdz_wyjscie(labirynt_t *moj_labirynt){
	for (int w = 0; w < moj_labirynt->wysokosc; w++){
		for (int k = 0; k < moj_labirynt->szerokosc; k++){
			if (w == 0 || w == moj_labirynt->wysokosc - 1 || k == 0 || k == moj_labirynt->szerokosc - 1){
				if (moj_labirynt->plansza[w][k] == DROGA){
					moj_labirynt->pozycja_wyjscia.x = k;
					moj_labirynt->pozycja_wyjscia.y = w;
				}
			}
		}
	}
}

bool import(char *nazwa_pliku, labirynt_t *moj_labirynt){
	FILE* plik;
	plik = fopen(nazwa_pliku, "r");
	if (plik == NULL)
		return false;
	if (moj_labirynt->plansza != NULL){ // zwolnienie pamieci w przypadku kolejnego importu labiryntu
		for (int i = 0; i < moj_labirynt->szerokosc; i++)
			free(moj_labirynt->plansza[i]);
		free(moj_labirynt->plansza);
	}
	moj_labirynt->szerokosc = licz_szerokosc(plik);
	moj_labirynt->wysokosc = licz_wysokosc(plik);
	moj_labirynt->plansza = (char**)malloc(moj_labirynt->szerokosc*sizeof(char*));
	for (int i = 0; i < moj_labirynt->szerokosc; i++){
		moj_labirynt->plansza[i] = (char*)malloc(moj_labirynt->wysokosc*sizeof(char));
	}
	if (moj_labirynt->plansza == NULL) return false; // sprawdzamy, czy system operacyjny przydzielil zadana pamiec
	for (int i = 0; i < moj_labirynt->szerokosc; i++){
		if (moj_labirynt->plansza[i] == NULL) return false;
	}
	fseek(plik, 0, SEEK_SET);
	int w = 0, k = 0;
	while (w < moj_labirynt->wysokosc){
		while (k < moj_labirynt->szerokosc){
			char c = fgetc(plik);
			if (c != '\n' && c != '\r'){
				switch (c){
				case '0': c = DROGA; break;
				case '1': c = SCIANA1; break;
				case '2': c = SCIANA2; break;
				case '3': c = SCIANA3; break;
				case '4': c = SCIANA4; break;
				case '5': c = SCIANA5; break;
				case '6': c = DRZWI_O; break;
				case '7': c = DRZWI_Z; break;
				}
				moj_labirynt->plansza[w][k] = c;
				k++;
			}
		}
		k = 0;
		w++;
	}
	fclose(plik);
	znajdz_wejscie(moj_labirynt);
	znajdz_wyjscie(moj_labirynt);
	return true;
}

bool czy_pola2x2(const labirynt_t *moj_labirynt){
	for (int w = 0; w < moj_labirynt->wysokosc - 1; w++){
		for (int k = 0; k < moj_labirynt->szerokosc - 1; k++){
			if (moj_labirynt->plansza[w][k] == DROGA
				|| moj_labirynt->plansza[w][k] == DRZWI_O
				|| moj_labirynt->plansza[w][k] == DRZWI_Z){
				if (moj_labirynt->plansza[w + 1][k] == DROGA
					|| moj_labirynt->plansza[w + 1][k] == DRZWI_O
					|| moj_labirynt->plansza[w + 1][k] == DRZWI_Z){
					if (moj_labirynt->plansza[w + 1][k + 1] == DROGA
						|| moj_labirynt->plansza[w + 1][k + 1] == DRZWI_O
						|| moj_labirynt->plansza[w + 1][k + 1] == DRZWI_Z){
						if (moj_labirynt->plansza[w][k + 1] == DROGA
							|| moj_labirynt->plansza[w][k + 1] == DRZWI_O
							|| moj_labirynt->plansza[w][k + 1] == DRZWI_Z){
							return true;
						}
					}
				}
			}
		}
	}
	return false;
}
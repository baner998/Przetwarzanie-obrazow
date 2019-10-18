#include <stdio.h>
#include <stdlib.h>

#define WYOSTRZ 0

#define ROZMYJ 1

#define DLUGOSC_DLA_WCZYTYWANIA_LICZBY 40

#define DLUGOSC_NAZWY 40

#define LEWO_PRAWO 1

#define GORA_DOL 2

typedef struct {
	char nazwa[DLUGOSC_NAZWY + 3];
	char standard[3];
	int SzerokoscObrazu;
	int WysokoscObrazu;
	int GlebiaSzarosci;
	int **orginal;
}obraz;

bool WczytajLiczbeFloat(float *f_liczba);

int** inicjalizacja2D(int, int);

void PokazBiblioteke(obraz *);

bool DodajObraz(obraz *);

void UsunObraz(obraz *);

bool ZapiszObraz(obraz *);

void PodazDaneObrazu(obraz zdjecie);

void MenuGlowne();

void WyswietlMenuGlowne();

void WyswietlMenuKonkretnegoObrazu();

void MenuKonkretnegoObrazu(obraz *);

void wczytaj(char *z, int ile);

bool obrot(obraz **zdjecie);

bool histogram(obraz zdjecie);

bool NadajWartosc(obraz **zdjecie, char * standard, int szerokosc, int wysokosc, int glebia, char *nazwa);

bool odbicie(obraz * zdjecie, int tryb);

bool szum(obraz *zdjecie);

bool gauss(obraz **zdjecie, int tryb, int szerokoscOkna);

void pokazkawalek(obraz zdjecie);

bool mediana(obraz **zdjecie, int szerokoscOkna);

int porownaj3(const void * a, const void * b);

int porownaj(const void * a, const void * b);

bool progowanie(obraz * zdjecie);

bool negatyw(obraz *zdjecie);

bool skalowanie(obraz **zdjecie);

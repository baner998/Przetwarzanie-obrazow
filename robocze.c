#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>
#include <string.h>

#include "obrazy1.h"

int** inicjalizacja2D(int wiersze, int kolumny)
{
	char c;
	int **tablicaPomocnicza = NULL;
	int licznik = 0; // inicjalizacja bo wywala blad
	tablicaPomocnicza = (int **)malloc(wiersze * sizeof(int *));
	if (tablicaPomocnicza == NULL)
	{
		printf("\nZBYT DUZA ILOSC DANYCH, NIE MOZNA ZAINICJALIZOWAC TAKIEJ TABLICY");
		while ((c = getchar()) != '\n') continue;
		return NULL;
	}
	else
	{
		for (licznik = 0; licznik < wiersze; licznik++)
		{
			tablicaPomocnicza[licznik] = (int *)malloc(kolumny * sizeof(int));
			if (tablicaPomocnicza[licznik] == NULL)
			{
				printf("\nBLAD PODCZAS INICJALIZACJI");

				for (licznik; licznik >= 0; licznik--)
				{
					free(tablicaPomocnicza[licznik]);
				}
				free(tablicaPomocnicza);

				return NULL;
			}
		}
	}
	return tablicaPomocnicza;
}

void wczytaj(char *z, int ile)
{
	char *tutaj;
	fgets(z, ile, stdin);
	if (z)
	{
		tutaj = strchr(z, '\n');
		if (tutaj)
			*tutaj = '\0';
		else
			while (getchar() != '\n')
				continue;
	}
}

bool WczytajLiczbeFloat(float *f_liczba)
{
	char liczba[DLUGOSC_DLA_WCZYTYWANIA_LICZBY];
	char c;
	bool PoprawnieWczytano = 0;
	int licznik = 0;
	fgets(liczba, DLUGOSC_DLA_WCZYTYWANIA_LICZBY, stdin);
	while (strchr("-0123456789.,", liczba[licznik]) && licznik < DLUGOSC_DLA_WCZYTYWANIA_LICZBY)
	{
		if (strchr(".,", liczba[licznik]))
		{
			liczba[licznik] = ',';
			if (licznik != 0) PoprawnieWczytano = 1;
			else if (strchr("0123456789", liczba[licznik + 1])) PoprawnieWczytano = 1;
			break;
		}
		else
		{
			PoprawnieWczytano = 1;
		}
		licznik++;
	}
	*f_liczba = atof(liczba);
	return PoprawnieWczytano;
}

void pokazkawalek(obraz zdjecie)
{
	int i, j;
	char c;
	printf("\nkawalek : \n");
	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 3; j++)
		{
			printf("\n[%d][%d]", i, j, zdjecie.orginal);
			//while ((c = getchar()) != '\n') continue;
		}
	}
	while ((c = getchar()) != '\n') continue;
}

int porownaj(const void * a, const void * b)
{
	return (*(int*)a - *(int*)b);
}

int porownaj3(const void * a, const void * b)
{
	int _a = *(int*)a;
	int _b = *(int*)b;
	if (_a < _b) return -1;
	else if (_a == _b) return 0;
	else return 1;
}
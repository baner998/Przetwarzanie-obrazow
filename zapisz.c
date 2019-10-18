#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>
#include <string.h>

#include "obrazy1.h"

bool ZapiszObraz(obraz *zdjecie)
{
	FILE *plik;
	char nazwa[DLUGOSC_NAZWY];
	printf("\nPodaj nazwe pliku, do ktorego nastapi zapis : ");
	wczytaj(nazwa, DLUGOSC_NAZWY);
	plik = fopen(nazwa, "w");
	int licznik1, licznik2;
	if (plik == NULL)	//nie potrzeba chyba bo ewentualnie stworzy, chociaz w sumie plik moze istniec ale my ktos go aktualnie przeglada i nie koniecznie do niego wejdziemy
	{
		printf("\nBlad pliku");
	}
	else
	{
		fprintf(plik, "%s\n", zdjecie->standard);
		fprintf(plik, "%d %d\n", zdjecie->SzerokoscObrazu, zdjecie->WysokoscObrazu);
		fprintf(plik, "%d\n", zdjecie->GlebiaSzarosci);
		for (licznik1 = 0; licznik1 < zdjecie->WysokoscObrazu; licznik1++)
		{
			for (licznik2 = 0; licznik2 < zdjecie->SzerokoscObrazu; licznik2++)
			{
				fprintf(plik, "%d ", zdjecie->orginal[licznik1][licznik2]);
			}
			fprintf(plik, "\n");
		}
		return 1;
	}
	return 0;
}

bool DodajObraz(obraz *zdjecie) // wczytanie tylko danych numerycznych z pliku do juz zainicjalizowanej struktury
{
	char c;
	FILE *plik;
	int **tablicaPomocnicza;
	int licznik1, licznik2;
	char nazwa[DLUGOSC_NAZWY];
	obraz obrazRoboczy;
	int i_pomoc = 0;

	printf("Podaj nazwe pliku : ");
	wczytaj(&(obrazRoboczy.nazwa), DLUGOSC_NAZWY);
	plik = fopen(obrazRoboczy.nazwa, "r");
	if (!plik)
	{
		printf("\nNIEPOWODZENIE PODCZAS OTWIERANIA OBRAZU\n");
		while ((c = getchar()) != '\n') continue;
	}
	else
	{
		fgets(obrazRoboczy.standard, 3, plik);

		for (licznik1 = 0; licznik1 < 3; licznik1++)
		{
			while (!fscanf(plik, "%d", &i_pomoc))
			{
				while ((c = getc(plik)) != '\n') continue;
			}

			switch (licznik1)
			{
			case 0:
				obrazRoboczy.SzerokoscObrazu = i_pomoc;
				break;
			case 1:
				obrazRoboczy.WysokoscObrazu = i_pomoc;
				break;
			case 2:
				obrazRoboczy.GlebiaSzarosci = i_pomoc;
				break;
			}

		}

		tablicaPomocnicza = inicjalizacja2D(obrazRoboczy.WysokoscObrazu, obrazRoboczy.SzerokoscObrazu);
		if (tablicaPomocnicza != NULL)
		{
			for (licznik1 = 0; licznik1 < obrazRoboczy.WysokoscObrazu; licznik1++)
			{
				for (licznik2 = 0; licznik2 < obrazRoboczy.SzerokoscObrazu; licznik2++)
				{
					if ((c = getc(plik)) == '#')
						while ((c = getc(plik)) != '\n') continue;
					else
					{
						ungetc(c, plik);
					}
					fscanf(plik, "%d", &(tablicaPomocnicza[licznik1][licznik2]));

					/*while (!fscanf(plik, "%d", &i_pomoc))
					{
						if ((c = getc(plik)) != '#')
						while ((c = getc(plik)) != '\n') continue;
					}*/

					//tablicaPomocnicza[licznik1][licznik2] = i_pomoc;
				}
			}
			obrazRoboczy.orginal = tablicaPomocnicza;
		}
		fclose(plik);
		*zdjecie = obrazRoboczy;
		return 1;
	}
	return 0;
}
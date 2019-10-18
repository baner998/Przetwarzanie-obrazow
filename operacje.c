#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>
#include <string.h>

#include "obrazy1.h"

void PodazDaneObrazu(obraz zdjecie)
{
	printf("\nnazwa = %s", zdjecie.nazwa);
	printf("\nstandard  = %s", zdjecie.standard);
	printf("\nszerokosc = %d", zdjecie.SzerokoscObrazu);
	printf("\nwysokosc  = %d", zdjecie.WysokoscObrazu);
	printf("\nszarosc   = %d", zdjecie.GlebiaSzarosci);
}

bool obrot(obraz **zdjecie)
{
	char c;
	obraz * wynik;
	wynik = (obraz *)malloc(1 * sizeof(obraz));
	int licznik = 0;
	int licznik1, licznik2;


	NadajWartosc(&wynik, (*zdjecie)->standard, (*zdjecie)->WysokoscObrazu, (*zdjecie)->SzerokoscObrazu, (*zdjecie)->GlebiaSzarosci, "roboczy.pgm");

	if (wynik == NULL) {
		printf("Wystapil blad podczas proby obrotu\n");
		while ((c = getchar()) != '\n') continue;
		return NULL;
	}

	for (licznik1 = 0; licznik1 < (*zdjecie)->WysokoscObrazu; licznik1++)
	{
		for (licznik2 = 0; licznik2 < (*zdjecie)->SzerokoscObrazu; licznik2++)
		{
			wynik->orginal[licznik2][licznik1] = (*zdjecie)->orginal[licznik1][licznik2];
		}
	}

	for (licznik1 = 0; licznik1 < wynik->WysokoscObrazu; licznik1++)
	{
		for (licznik2 = 0; licznik2 < wynik->SzerokoscObrazu / 2; licznik2++)
		{
			licznik = wynik->orginal[licznik1][licznik2];
			wynik->orginal[licznik1][licznik2] = wynik->orginal[licznik1][wynik->SzerokoscObrazu - licznik2 - 1];
			wynik->orginal[licznik1][wynik->SzerokoscObrazu - licznik2 - 1] = licznik;
		}
	}
	*zdjecie = wynik;

	return 1;
}

bool histogram(obraz zdjecie)
{
	char c;
	int * tablicaHistogramu;
	int licznik1, licznik2;
	FILE * plik;
	char nazwaPliku[DLUGOSC_NAZWY];
	tablicaHistogramu = calloc(zdjecie.GlebiaSzarosci + 1, sizeof(int));

	if (tablicaHistogramu == NULL) {
		printf("\nBlad podczas tworzenia histogramu");
		while ((c = getchar()) != '\n') continue;
		return 0;
	}

	for (licznik1 = 0; licznik1 < zdjecie.WysokoscObrazu; licznik1++)
	{
		for (licznik2 = 0; licznik2 < zdjecie.SzerokoscObrazu; licznik2++)
		{
			if (zdjecie.orginal[licznik1][licznik2] <= zdjecie.GlebiaSzarosci)
			{
				tablicaHistogramu[zdjecie.orginal[licznik1][licznik2]] += 1;
			}
		}
	}
	printf("\nPodaj nazwe pliku, w ktorym zostanie umieszczony histogram : ");
	wczytaj(nazwaPliku, DLUGOSC_NAZWY - 3);
	plik = fopen(nazwaPliku, "w");
	if (plik == NULL) {
		printf("Blad podczas tworzenia histogramu\n");
		if (tablicaHistogramu != NULL)
			free(tablicaHistogramu);
		return 0;
	}

	for (licznik1 = 0; licznik1 < zdjecie.GlebiaSzarosci + 1; licznik1++)
	{
		fprintf(plik, "%d;%d\n", licznik1, tablicaHistogramu[licznik1]);
	}

	fclose(plik);

	if (tablicaHistogramu != NULL)
	{
		free(tablicaHistogramu);
	}
	return 1;
}

bool NadajWartosc(obraz **zdjecie, char * standard, int szerokosc, int wysokosc, int glebia, char *nazwa)
{
	char c;

	obraz * zdjecieRobocze = calloc(1, sizeof(obraz)); // ewentualnie zamiana na malloc

	if (zdjecieRobocze == NULL)
	{
		printf("Blad podczas nadawania wartosci\n");
		while ((c = getchar()) != '\n') continue;
		return 0;
	}

	strcpy(zdjecieRobocze->standard, standard);
	zdjecieRobocze->SzerokoscObrazu = szerokosc;
	zdjecieRobocze->WysokoscObrazu = wysokosc;
	zdjecieRobocze->GlebiaSzarosci = glebia;
	strcpy(zdjecieRobocze->nazwa, nazwa);


	zdjecieRobocze->orginal = inicjalizacja2D(wysokosc, szerokosc);
	if (zdjecieRobocze->orginal == NULL)
	{
		printf("\nBlad podczas nadawania wartosci");
		while ((c = getchar()) != '\n') continue;
		return 0;
	}
	else
	{
		*zdjecie = zdjecieRobocze;
		return 1;
	}
}

bool negatyw(obraz *zdjecie)
{
	int licznik1, licznik2;

	if (zdjecie == NULL) {
		printf("Blad podczas proby stworzenia negatywu\n");
		return 0;
	}

	for (licznik1 = 0; licznik1 < zdjecie->WysokoscObrazu; licznik1++)
		for (licznik2 = 0; licznik2 < zdjecie->SzerokoscObrazu; licznik2++)
			zdjecie->orginal[licznik1][licznik2] = zdjecie->GlebiaSzarosci - zdjecie->orginal[licznik1][licznik2];
}

bool odbicie(obraz * zdjecie, int tryb)
{

	int pomocniczyInteger = 0;
	int licznik1, licznik2;

	if (zdjecie == NULL) {		// przeniesc*************************
		printf("brak pliku\n");
		return 0;
	}

	if (tryb == LEWO_PRAWO)
	{
		for (licznik1 = 0; licznik1 < zdjecie->WysokoscObrazu; licznik1++)
			for (licznik2 = 0; licznik2 < zdjecie->SzerokoscObrazu / 2; licznik2++)
			{
				pomocniczyInteger = zdjecie->orginal[licznik1][licznik2];
				zdjecie->orginal[licznik1][licznik2] = zdjecie->orginal[licznik1][zdjecie->SzerokoscObrazu - licznik2 - 1];
				zdjecie->orginal[licznik1][zdjecie->SzerokoscObrazu - licznik2 - 1] = pomocniczyInteger;
			}
	}
	else {
		for (licznik1 = 0; licznik1 < zdjecie->SzerokoscObrazu; licznik1++)
			for (licznik2 = 0; licznik2 < zdjecie->WysokoscObrazu / 2; licznik2++)
			{
				pomocniczyInteger = zdjecie->orginal[licznik2][licznik1];
				zdjecie->orginal[licznik2][licznik1] = zdjecie->orginal[zdjecie->WysokoscObrazu - licznik2 - 1][licznik1];
				zdjecie->orginal[zdjecie->WysokoscObrazu - licznik2 - 1][licznik1] = pomocniczyInteger;
			}
	}
	return 1;
}

bool szum(obraz *zdjecie)
{
	char c;
	int licznik1, licznik2;
	bool flagaBledu = 1;

	float prawdopodobienstwo = 0.5;

	printf("\nOkresl prawdopobienstwo zaszumienia probki ");
	printf("\nEnter dla wartosci domyslnej 50%");
	printf("\nWartosc : ");
	if ((c = getchar()) != '\n')
	{
		ungetc(c, stdin);
		do
		{
			flagaBledu = 0;
			//printf("\nPodaj prawdopodobienstwo : ");

			while (!WczytajLiczbeFloat(&prawdopodobienstwo))
			printf("\nNieprawne dane, wczytaj ponownie : ");
			if (prawdopodobienstwo < 0)
			{
				printf("\nprawdopodobienstwo nie moze byc mniejsze niz 0");
				flagaBledu = 1;
			}
			if (prawdopodobienstwo >= 100)
			{
				printf("\nprawdopodobienstwo nie moze byc wiekszw niz 100");
				flagaBledu = 1;
			}
			while ((c = getchar()) != '\n') continue;
		} while (flagaBledu);
	}

	for (licznik1 = 0; licznik1 < zdjecie->WysokoscObrazu; licznik1++)
	{
		for (licznik2 = 0; licznik2 < zdjecie->SzerokoscObrazu; licznik2++)
		{

			if (rand() % 10000 < (int)(prawdopodobienstwo * 100))
			{
				if (rand() % 2)
				{
					zdjecie->orginal[licznik1][licznik2] = 0;
				}
				else
				{
					zdjecie->orginal[licznik1][licznik2] = 255;
				}
			}
		}
	}
}

bool gauss(obraz **zdjecie, int tryb, int szerokoscOkna)
{

	obraz *wynik;
	//int szerokoscOkna = 3;
	int suma = 0;
	int rog, krawedz, srodek, suma_wag;
	int licznik1, licznik2;
	char c;
	bool flagabledu = 1;

	if (min((*zdjecie)->SzerokoscObrazu, (*zdjecie)->WysokoscObrazu) < 3)
	{
		printf("\nobraz jest za ma³y by dzialac na nim filtrem");
		while ((c = getchar()) != '\n') continue;
		return 0;
	}

	if (tryb == ROZMYJ)
	{
		do
		{
			printf("\nPodaj szerokosc okna : ");
			flagabledu = 0;
			while (!scanf("%d", &szerokoscOkna))
			{
				printf("\nPodane dane nie sa liczba calkowita (w mysl programu)");
			}
			if (szerokoscOkna < 3)
			{
				printf("\nminimalna mozliwa szerokosc okna to 3");
				flagabledu = 1;
			}
			if (min((*zdjecie)->SzerokoscObrazu, (*zdjecie)->WysokoscObrazu) < szerokoscOkna)
			{
				printf("\n za duzy rozmiar okna\npodaj mniejsza wartosc");
				flagabledu = 1;
			}
			if (!flagabledu)
			{
				while ((c = getchar()) != '\n') continue;
			}
		} while (flagabledu);
	}

	NadajWartosc(&wynik, (*zdjecie)->standard, (*zdjecie)->SzerokoscObrazu, (*zdjecie)->WysokoscObrazu, (*zdjecie)->GlebiaSzarosci, (*zdjecie)->nazwa);

	for (int licznik1 = 0; licznik1 < (*zdjecie)->WysokoscObrazu; licznik1++)
	{
		for (int licznik2 = 0; licznik2 < (*zdjecie)->SzerokoscObrazu; licznik2++)
		{
			wynik->orginal[licznik1][licznik2] = (*zdjecie)->orginal[licznik1][licznik2];
		}
	}

	if (tryb == ROZMYJ) { rog = 1; krawedz = 2; srodek = 4; /*suma_wag = 16;*/ }
	else { rog = 0; krawedz = -1; srodek = 5; /*suma_wag = 1;*/ }

	suma_wag = 4 * rog + 4 * krawedz + srodek;

	for (int licznik1 = 0; licznik1 < (*zdjecie)->WysokoscObrazu - szerokoscOkna; licznik1++)
	{
		for (int licznik2 = 0; licznik2 < (*zdjecie)->SzerokoscObrazu - szerokoscOkna; licznik2++)
		{
			suma += rog * (*zdjecie)->orginal[licznik1][licznik2];
			suma += krawedz * (*zdjecie)->orginal[licznik1][licznik2 + 1];
			suma += rog * (*zdjecie)->orginal[licznik1][licznik2 + 2];
			suma += krawedz * (*zdjecie)->orginal[licznik1 + 1][licznik2];
			suma += srodek * (*zdjecie)->orginal[licznik1 + 1][licznik2 + 1];
			suma += krawedz * (*zdjecie)->orginal[licznik1 + 1][licznik2 + 2];
			suma += rog * (*zdjecie)->orginal[licznik1 + 2][licznik2];
			suma += krawedz * (*zdjecie)->orginal[licznik1 + 2][licznik2 + 1];
			suma += rog * (*zdjecie)->orginal[licznik1 + 2][licznik2 + 2];

			wynik->orginal[licznik1][licznik2] = suma / suma_wag;

			suma = 0;
		}
	}
	*zdjecie = wynik;
	return 1;
}

bool mediana(obraz **zdjecie, int szerokoscOkna)
{
	obraz *wynik = NULL;
	char c;
	int * tablicaPomocnicza;
	int licznik = 0;
	int iNum = 0;
	bool flagabledu = 1;

	/*if (zdjecie == NULL) {
		printf("Blad w medianie\n");
		while ((c = getchar()) != '\n') continue;
		return 0;
	}*/

	do
	{
		flagabledu = 0;
		printf("\nPodaj szerokosc okna : ");
		while (!scanf("%d", &szerokoscOkna))
		{
			printf("\nPodane dane nie sa liczba calkowita (w mysl programu)");
		}
		if (szerokoscOkna < 3)
		{
			printf("\nminimalna mozliwa szerokosc okna to 3");
			flagabledu = 1;
		}

		if (min((*zdjecie)->SzerokoscObrazu, (*zdjecie)->WysokoscObrazu) < szerokoscOkna)
		{
			printf("\n za duzy rozmiar okna\npodaj mniejsza wartosc");
			flagabledu = 1;
		}

		if (szerokoscOkna % 2 == 0)
		{
			printf("\nszerokosc okna musi byc liczba parzysta");
			flagabledu = 1;
		}

		//if (!flagabledu)
		//{
		while ((c = getchar()) != '\n') continue;
		//}

	} while (flagabledu);

	printf("\nTrwa proces filtracji, prosze czekac\n");

	tablicaPomocnicza = calloc(szerokoscOkna * szerokoscOkna, sizeof(int));

	if (tablicaPomocnicza == NULL) {
		printf("\nBlad podczas filtracji medianowej");
		while ((c = getchar()) != '\n') continue;
		return NULL;
	}

	NadajWartosc(&wynik, (*zdjecie)->standard, (*zdjecie)->SzerokoscObrazu, (*zdjecie)->WysokoscObrazu, (*zdjecie)->GlebiaSzarosci, (*zdjecie)->nazwa);
	if (wynik == NULL)
	{
		printf("\nBlad podczas filtracji medianowej");
		while ((c = getchar()) != '\n') continue;
		free(tablicaPomocnicza);
		tablicaPomocnicza = NULL;
		return NULL;
	}

	for (int licznik1 = 0; licznik1 < (*zdjecie)->WysokoscObrazu; licznik1++)
	{
		for (int licznik2 = 0; licznik2 < (*zdjecie)->SzerokoscObrazu; licznik2++)
		{
			wynik->orginal[licznik1][licznik2] = (*zdjecie)->orginal[licznik1][licznik2];
		}
	}

	for (int licznik1 = 0; licznik1 < (*zdjecie)->WysokoscObrazu - szerokoscOkna; licznik1++)
	{
		for (int licznik2 = 0; licznik2 < (*zdjecie)->SzerokoscObrazu - szerokoscOkna; licznik2++)
		{
			for (int licznik3 = 0; licznik3 < szerokoscOkna; licznik3++)
			{
				for (int licznik4 = 0; licznik4 < szerokoscOkna; licznik4++)
				{
					tablicaPomocnicza[licznik] = (*zdjecie)->orginal[licznik1 + licznik3][licznik2 + licznik4];
					licznik++;
				}
			}

			licznik = 0;
			qsort(tablicaPomocnicza, szerokoscOkna * szerokoscOkna, sizeof(int), porownaj3);
			wynik->orginal[licznik1 + szerokoscOkna / 2][licznik2 + szerokoscOkna / 2] = tablicaPomocnicza[szerokoscOkna * szerokoscOkna / 2];

		}
	}

	*zdjecie = wynik;
	free(tablicaPomocnicza);
	tablicaPomocnicza = NULL;

	return 1;
}

bool progowanie(obraz * zdjecie)
{
	int prog = 0;
	int licznik1, licznik2;
	char c;
	do
	{
		printf("\nPodaj prog : ");
		while (!scanf("%d", &prog))
		{
			printf("\nPodane dane nie sa liczba calkowita (w mysl programu)");
			//while ((c = getchar()) != '\n') continue;
		}
		while ((c = getchar()) != '\n') continue;
		if (prog < 1 || prog > zdjecie->GlebiaSzarosci - 1)
		{
			printf("\nPodany przez Ciebie prog nie miesci sie w legalnym zakresie [ 1 ; %d ]", zdjecie->GlebiaSzarosci - 1);
		}
	} while (prog < 1 || prog > zdjecie->GlebiaSzarosci - 1);


	for (licznik1 = 0; licznik1 < zdjecie->WysokoscObrazu; licznik1++)
		for (licznik2 = 0; licznik2 < zdjecie->SzerokoscObrazu; licznik2++)
		{
			if (zdjecie->orginal[licznik1][licznik2] > prog)
				zdjecie->orginal[licznik1][licznik2] = zdjecie->GlebiaSzarosci;
			else
				zdjecie->orginal[licznik1][licznik2] = 0;
		}
	return 1;
}

bool skalowanie(obraz **zdjecie)
{
	char c;
	int skala = 2;
	int tryb;
	char wybor;

	/*float wysokosc;
	float szerokosc;
	printf("\n1) powieksz");
	printf("\n2) pomniejsz");
	printf("\nWybor : ");
	wybor = getchar();*/
	//while ((c = getchar()) != '\n') continue;
	/*while(wybor != '1' && wybor != '2')
	{
		printf("\npodaj wartosc z zakresu 1-2     : ");
		c = getchar();
		//if (wybor == '1') break;
		//if (wybor == '2') break;
	}*/
	
	/*if (c == '1')	tryb = 1;
	else printf("");*/

	

	bool flagaBledu = 1;
	printf("\nOkresl skale :  ");
	printf("\nEnter dla wartosci domyslnej : 2");
	printf("\nWartosc : ");
	if ((c = getchar()) != '\n')
	{
		ungetc(c, stdin);
		do
		{
			flagaBledu = 0;

			while (!scanf("%d", &skala))
			{
				printf("\nNieprawne dane, wczytaj ponownie : ");
			}
			if (skala < 0)
			{
				printf("\nskala nie moze byc mniejsze niz 0");
				flagaBledu = 1;
			}
			if (skala > 5)
			{
				printf("\nskala nie moze byc wiekszw niz 5");
				flagaBledu = 1;
			}
			while ((c = getchar()) != '\n') continue;
		} while (flagaBledu);
	}




	int licznik1, licznik2;
	obraz *wynik;
	wynik = (obraz *)malloc(1 * sizeof(obraz));
	if(tryb = 1) NadajWartosc(&wynik, (*zdjecie)->standard,skala*((*zdjecie)->SzerokoscObrazu), skala*((*zdjecie)->WysokoscObrazu), (*zdjecie)->GlebiaSzarosci, "roboczy.pgm");
	/*else
	{
		wysokosc =(float) ((*zdjecie)->WysokoscObrazu) / skala;
		szerokosc =(float) ((*zdjecie)->SzerokoscObrazu) / skala;
		NadajWartosc(&wynik, (*zdjecie)->standard, szerokosc, wysokosc, (*zdjecie)->GlebiaSzarosci, "roboczy.pgm");
	}*/
	if (wynik == NULL) 
	{
		printf("Wystapil blad podczas skalowania\n");
		while ((c = getchar()) != '\n') continue;
		return 0;
	}

	if (tryb = 1)
	{
		for (licznik1 = 1; licznik1 < skala*((*zdjecie)->WysokoscObrazu); licznik1++)
		{
			for (licznik2 = 1; licznik2 < skala*((*zdjecie)->SzerokoscObrazu); licznik2++)
			{
				wynik->orginal[licznik1][licznik2] = (*zdjecie)->orginal[((licznik1 - 1) / skala)][((licznik2 - 1) / skala)];
			}
		}
	}
	/*else
	{
		for (licznik1 = 1; licznik1 < wysokosc; licznik1++)
		{
			for (licznik2 = 1; licznik2 < szerokosc; licznik2++)
			{
				wynik->orginal[licznik1][licznik2] = (*zdjecie)->orginal[((licznik1 - 1) / skala)][((licznik2 - 1) / skala)];
			}
		}

	}*/
	*zdjecie = wynik;
	return 1;
}
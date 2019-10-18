#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>
#include <string.h>

#include "obrazy1.h"

void WyswietlMenuKonkretnegoObrazu()
{
	printf("\n\t**Przetwarzanie Obrazu**");
	printf("\n0) Wyswietl dane obrazu");
	printf("\n1) negatyw");
	printf("\n2) histogram");
	printf("\n3) obrot");
	printf("\n4) wyostrzenie");
	printf("\n5) naluz zaklucenia");
	printf("\n6) filtr Gaussa");
	printf("\n7) filtr medianowy");
	printf("\n8) odbicie");
	printf("\n9) progowanie");
	printf("\ns) zapisz do pliku wynik obrobki");
	printf("\np) powiekszenie");
	printf("\nEnter by powrocic do menu glownego");
	printf("\nTwoj Wybor : ");
}

void WyswietlMenuGlowne()
{
	printf("\n\t**Przetwarzanie Biblioteki Obrazow**");
	printf("\n1) podaz biblioteke");
	printf("\n2) wybierz obraz pod obrobke");
	printf("\n3) dodaj obraz");
	printf("\n4) zapisz obraz");
	printf("\n5) Usun obrazu");
	printf("\n6) Wejdz do menu konkretnego obrazu");
	printf("\nEnter by wyjsc");
	printf("\nTwoj Wybor : ");
}

void PokazBiblioteke(obraz *zbior, int iloscObrazow)
{
	char c;
	int iteracja1 = 0, iteracja2 = 0; // inicjalizacja bo sypalo bledem
	printf("**Biblioteka**\n");

	for (iteracja1 = 0; iteracja1 < iloscObrazow; iteracja1++)
	{
		printf("%d ) %s\n", iteracja1, zbior[iteracja1].nazwa);
	}
}
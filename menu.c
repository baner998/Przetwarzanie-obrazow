#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>
#include <string.h>

#include "obrazy1.h"

void MenuGlowne()
{
	char wybor, c;
	obraz *ZbiorObrazow = NULL;	/////////////////////
	int iloscObrazow = 0;
	obraz test;
	int nrDoObrobki = -1;
	bool wybranoObraz = 0;
	int licznik1;

	do
	{
		if (nrDoObrobki > -1)
		{
			printf("\nWybrany obraz : %s\n", ZbiorObrazow[nrDoObrobki].nazwa);
		}
		WyswietlMenuGlowne();

		wybor = getchar();
		if (wybor != '\n') while ((c = getchar()) != '\n') continue; //bez if'a chêæ zakonczenia programu wymaga dwóch enterów
		system("cls");
		switch (wybor)
		{
		case '1':
			if (iloscObrazow == 0)
			{
				printf("\nBrak obrazow do wyswietlenia");
				while ((c = getchar()) != '\n') continue;
			}
			else
			{
				PokazBiblioteke(ZbiorObrazow, iloscObrazow);
				while ((c = getchar()) != '\n') continue;
			}
			break;
		case '2':
			if (iloscObrazow > 0)
			{
				PokazBiblioteke(ZbiorObrazow, iloscObrazow);
				//printf("\nDokonaj wyboru : ");
				do
				{
					printf("\nDokonaj wyboru : ");
					while (!(scanf("%d", &nrDoObrobki)))
					{
						printf("\nNiepoprawny typ danych");
						//while ((c = getchar()) != '\n') continue;
					}
					while ((c = getchar()) != '\n') continue;
					if (nrDoObrobki > iloscObrazow)
					{
						printf("\nNumer spoza zakresu");
						//while ((c = getchar()) != '\n') continue;
					}
				} while ((nrDoObrobki >= iloscObrazow) || (nrDoObrobki < 0));
			}
			else
			{
				printf("\nbrak obrazow");
				while ((c = getchar()) != '\n') continue;
			}
			//while ((c = getchar()) != '\n') continue; //przyczyna tej linii : jesli dobrze podana zostanie liczba to enter zostanie w strumieniu
			break;
		case '3':
			ZbiorObrazow = realloc(ZbiorObrazow, (iloscObrazow + 1) * sizeof(obraz));
			if (ZbiorObrazow != NULL)
			{
				ZbiorObrazow[iloscObrazow];

				if (DodajObraz(ZbiorObrazow + iloscObrazow))
				{
					printf("\n w casie");
					iloscObrazow++;
				}
			}
			break;
		case '4':
			if (nrDoObrobki >= 0)
				ZapiszObraz(ZbiorObrazow + nrDoObrobki);
			else
			{
				printf("\nNie wybrano obrazu");
				while ((c = getchar()) != '\n') continue;
			}

			break;
		case '5':
			if (nrDoObrobki > -1)
			{
				UsunObraz(&ZbiorObrazow[nrDoObrobki]);
				//&ZbiorObrazow[nrDoObrobki] = NULL;
				for (licznik1 = nrDoObrobki; licznik1 < iloscObrazow - 1; licznik1++)
				{
					ZbiorObrazow[nrDoObrobki] = ZbiorObrazow[nrDoObrobki + 1];
				}
				nrDoObrobki = -1;//*******************************************************
				//printf("\ngotcha error 1");
				ZbiorObrazow = realloc(ZbiorObrazow, (iloscObrazow - 1) * sizeof(obraz));
				//printf("\\ngotcha error 2");
				if (iloscObrazow > 0)	//ten if nie ma sensu chyba 
				{
					iloscObrazow--;
				}
			}
			else
			{
				printf("\n Nie wybrano obrazu");
				while ((c = getchar()) != '\n') continue;
			}


			break;
		case '6':
			if (nrDoObrobki > -1)
			{
				MenuKonkretnegoObrazu(ZbiorObrazow + nrDoObrobki);
			}
			else
			{
				printf("\n Nie wybrano obrazu");
				while ((c = getchar()) != '\n') continue;
			}
			break;
		case '\n':
			printf("\nBy potwierdzic wyjscie nacisnij ponownie Enter");
			printf("\nDowolny inny ciag w przeciwnym wypadku : ");
			wybor = getchar();
			if (wybor != '\n') while ((c = getchar()) != '\n') continue; // czysczenie smieci
			break;
		default:
			printf("\nBRAK TAKIEJ OPCJI");
			while ((c = getchar()) != '\n') continue;
			break;
		}
		system("cls");
	} while (wybor != '\n');

	//ZbiorObrazow
	for (licznik1 = 0; licznik1 < iloscObrazow; licznik1++)
	{
		UsunObraz(ZbiorObrazow+(iloscObrazow-1-licznik1));
		ZbiorObrazow =realloc(ZbiorObrazow , (iloscObrazow-(licznik1+1)) * sizeof(obraz));
	}

}

void MenuKonkretnegoObrazu(obraz *zdjecie)
{
	char wybor, c;
	int tryb , krotnosc;
	obraz zdjecieRobocze;
	char nazwaRobocza[DLUGOSC_NAZWY];
	obraz **pomocniczyptr = NULL;
	bool flagaBledu=1;
	int licznik;

	do
	{
		WyswietlMenuKonkretnegoObrazu();
		wybor = getchar();
		if (wybor != '\n') while ((c = getchar()) != '\n') continue; //bez if'a chêæ zakonczenia programu wymaga dwóch enterów

		switch (wybor)
		{
		case '0':
			PodazDaneObrazu(*zdjecie);
			while ((c = getchar()) != '\n') continue;
			break;
		case '1':
			negatyw(zdjecie);
			break;
		case '2':
			histogram(*zdjecie);
			break;
		case '3':
			//printf("\nPodaj krotnosc obrotu (obrot zgodnie ze wskazowkami zegara) : ");
			do
			{
				printf("\nPodaj krotnosc obrotu (obrot zgodnie ze wskazowkami zegara) : ");
				flagaBledu = 0;
				while (!scanf("%d", &krotnosc))
				{
					while ((c = getchar()) != '\n') continue;
					printf("\npodana wartosc powinna byc liczba calkowita");
				}
				while ((c = getchar()) != '\n') continue;
				if (krotnosc > 3 || krotnosc < 0)
				{
					printf("\nZla wartosc, legalny zakres to 1-3");
					flagaBledu = 1;
				}
			} while (flagaBledu);
			for (licznik = 0; licznik < krotnosc; licznik++)
			{
				obrot(&zdjecie);
			}
			break;
		case '4':
			gauss(&zdjecie, WYOSTRZ, 3);
			break;
		case '5':
			szum(zdjecie);
			break;
		case '6':
			gauss(&zdjecie, ROZMYJ, 3);
			break;
		case '7':
			mediana(&zdjecie, 3);
			break;
		case '8':
			printf("\nWybierz tryb odbicia : ");
			printf("\n1) Lewo <-> Prawo");
			printf("\n2) Gora <-> Dol");
			printf("\nWybor : ");
			wybor = getchar();
			if (wybor != '\n') while ((c = getchar()) != '\n') continue;
			if (((int)wybor - 48) == LEWO_PRAWO)
			{
				odbicie(zdjecie, LEWO_PRAWO);
			}
			else if (((int)wybor - 48) == GORA_DOL)
			{
				odbicie(zdjecie, 2);
			}
			else
			{
				printf("\nBrak takiej opcji");
				while ((c = getchar()) != '\n') continue;
			}
			break;
		case '9':
			progowanie(zdjecie);
			break;
		case 's':
			ZapiszObraz(zdjecie);
			break;
		case 'p':
			skalowanie(&zdjecie);
			break;
		case '\n':
			printf("\nBy potwierdzic wyjscie nacisnij ponownie Enter");
			printf("\nDowolny inny ciag w przeciwnym wypadku : ");
			wybor = getchar();
			if (wybor != '\n') while ((c = getchar()) != '\n') continue; // czysczenie smieci
			break;
		default:
			printf("\nBRAK TAKIEJ OPCJI");
			while ((c = getchar()) != '\n') continue;
			break;
		}
		system("cls");
	} while (wybor != '\n');
}
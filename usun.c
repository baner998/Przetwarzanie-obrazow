#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>
#include <string.h>

#include "obrazy1.h"

void UsunObraz(obraz *zdjecie)
{
	char c;


	int licznik1;

	for (licznik1 = 0; licznik1 < zdjecie->WysokoscObrazu; licznik1++)
	{
		if (zdjecie->orginal[licznik1] != NULL)
		{
			free(zdjecie->orginal[licznik1]);
			
		}
	}
	if (zdjecie->orginal != NULL)
	{
		free(zdjecie->orginal);

	}


}
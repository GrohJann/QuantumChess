#pragma once
#include "Figuren.h"
struct Brett
{
	Figuren* Felder[8][8];
};
struct Moegliches_Feld
{
	int spalte;
	int zeile;
};

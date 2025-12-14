
#ifndef QUANTUMCHESS_QUANTEN_SCHACH_H
#define QUANTUMCHESS_QUANTEN_SCHACH_H

#include <vector>
#include "Bauer.h"
#include "Springer.h"
#include "Laeufer.h"
#include "Turm.h"
#include "Dame.h"
#include "Koenig.h"


void Startaufstellung_Bauern(std::vector <Bauer> &bauern, Figuren* (&Spielfeld)[8][8]);
void Startaufstellung_Springer(vector <Springer> &springer, Figuren* (&Spielfeld)[8][8]);
void Startaufstellung_Laeufer(vector <Laeufer>& laeufer, Figuren* (&Spielfeld)[8][8]);
void Startaufstellung_Tuerme(vector <Turm>& tuerme, Figuren* (&Spielfeld)[8][8]);
void Startaufstellung_Damen(vector <Dame>& damen, Figuren* (&Spielfeld)[8][8]);
void Startaufstellung_Koenige(vector <Koenig>& koenige, Figuren* (&Spielfeld)[8][8]);

void Initialisieren_Feld_Weiss(bool (&weiss) [8][8]);
void Initialisieren_Feld_Schwarz(bool(&schwarz)[8][8]);
void Initialisieren_Feld_Gesamt(bool(&gesamt)[8][8]);

void Spielfeld_Initialisieren(Figuren* (&Spielfeld)[8][8]);
int run_logic();

#endif //QUANTUMCHESS_QUANTEN_SCHACH_H
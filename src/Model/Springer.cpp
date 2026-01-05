#include <iostream>
#include "Springer.h"
#include "Structs.h"
#include <vector>
#include <array>
using namespace std;

vector <Moegliches_Feld>  Springer::Get_Moegliche_Felder() {
	return moegliche_felder;
 }

void Springer::Set_Moegliche_Felder(Brett spielfeld) {// bearbeiten
	moegliche_felder.clear();
	int s[8] = { 2,2,-2,-2,1,1,-1,-1 };
	int z[8] = { 1,-1,1,-1,2,-2,2,-2 };
	for (int i = 0; i < 8; i++) {

		if (spalte + s[i] >= 1 && spalte + s[i] <= 8) {
			if (zeile + z[i] >= 1 && zeile + z[i] <= 8) {
				int neue_spalte = spalte + s[i];
				int neue_zeile = zeile + z[i];
				Moegliches_Feld F;
				if (spielfeld.Felder[neue_spalte -1][ neue_zeile -1] == nullptr) {
					F.spalte = neue_spalte;
					F.zeile = neue_zeile;
					moegliche_felder.push_back(F);
				}
				else if (spielfeld.Felder[neue_spalte -1][neue_zeile -1]->Get_Farbe() != weiss) {
					F.spalte = neue_spalte;
					F.zeile = neue_zeile;
					moegliche_felder.push_back(F);
				}
			}
		}
	}
}

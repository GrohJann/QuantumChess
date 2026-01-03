#include <iostream>
#include "../Spiel_Logik/Springer.h"
#include "../Structs.h"
#include <vector>
#include <array>
using namespace std;

vector <Moegliches_Feld> Springer::Get_Moegliche_Felder() {

	return moegliche_felder;
}

void Springer::Set_Moegliche_Felder(Brett spielfeld) {// bearbeiten

	bool eine_spalte = false;
	bool zwei_spalten = true;
	for (int s = -2; s < 3; s++) {

		if (spalte + s >= 1 && spalte + s <= 8 && s != 0) {
			for (int z = -1; z < 2; z++) {

				int a = z;
				if (eine_spalte && !zwei_spalten) {
					a = 2 * z;
				}
				if (zeile + a >= 1 && zeile + a <= 8 && z != 0) {
					if (spielfeld.Felder[spalte + s - 1][zeile + a - 1] == nullptr) {
						Moegliches_Feld F;
						F.spalte = spalte + s;
						F.zeile = zeile + a;
						moegliche_felder.push_back(F);
					}
					else if (spielfeld.Felder[spalte + s - 1][zeile + z - 1]->Get_Farbe() != weiss) {
						Moegliches_Feld F;
						F.spalte = spalte + s;
						F.zeile = zeile + a;
						moegliche_felder.push_back(F);
					}
				}
			}
		}
		if (s == -2) {
			eine_spalte = true;
			zwei_spalten = false;
		}
		if (s == 1) {
			eine_spalte = false;
			zwei_spalten = true;
		}
	}
}

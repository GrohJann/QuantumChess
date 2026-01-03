#include "../Model/Koenig.h"
#include "Structs.h"
#include <vector>
using namespace std;


void Koenig::Set_Moegliche_Felder(Brett spielfeld) {

	for (int s = -1; s < 1; s++) {
		for (int z = -1; z < 1; z++) {
			Moegliches_Feld F;
			if (spalte + s >= 1 && spalte + s <= 8) {
				if (zeile + z >= 1 && zeile + z <= 8) { // liegt das Feld auf dem Brett
					if (spielfeld.Felder[spalte + s - 1][zeile + z - 1] == nullptr) {
						F.spalte = spalte + s;
						F.zeile = zeile + z;
						moegliche_felder.push_back(F);
					}
					else if (spielfeld.Felder[spalte + s - 1][zeile + z - 1]->Get_Farbe() != weiss) { // darf der K�nig da hinziehn
						F.spalte = spalte + s;
						F.zeile = zeile + z;
						moegliche_felder.push_back(F);
					}
				}
			}
		}
	}
	// Rochade kommt noch
}


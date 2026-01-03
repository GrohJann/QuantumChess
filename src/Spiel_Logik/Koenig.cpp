#include "Koenig.h"
#include "Brett.h"
#include <vector>
using namespace std;

 vector <Moegliches_Feld> Koenig::Get_Moegliche_Felder() {

	return moegliche_felder;
}


void Koenig::Set_Moegliche_Felder(Brett spielfeld) {
	moegliche_felder.clear();

	for (int s = -1; s < 1; s++) {
		for (int z = -1; z < 1; z++) {
			Moegliches_Feld F;
			if (spalte + s >= 1 && spalte + s <= 8) {
				if (  zeile + z >= 1 &&  zeile + z <= 8 ) { // liegt das Feld auf dem Brett
					if (spielfeld.Felder[spalte + s - 1][zeile + z - 1] == nullptr) {
						F.spalte = spalte + s;
						F.zeile = zeile + z;
						moegliche_felder.push_back(F);
					}
					else if (spielfeld.Felder[spalte + s - 1][zeile + z - 1]->Get_Farbe() != weiss) { // darf der König da hinziehn
						F.spalte = spalte + s;
						F.zeile = zeile + z;
						moegliche_felder.push_back(F);
					}
				}
			}
		}
	}

	/*Moegliches_Feld F;

	// Rochade (jetzt kann der Koenig zwei Felder gehen, allerding beqwegt sich der Turm noch nicht
	if (spielfeld.scw && weiss) {
		F.spalte = spalte + 2;
		F.zeile = zeile;
		moegliche_felder.push_back(F);
	}
	if (spielfeld.lcw && weiss) {
		F.spalte = spalte - 2;
		F.zeile = zeile;
		moegliche_felder.push_back(F);
	}
	if (spielfeld.scb && !weiss) {
		F.spalte = spalte + 2;
		F.zeile = zeile;
		moegliche_felder.push_back(F);
	}
	if (spielfeld.lcb && !weiss) {
		F.spalte = spalte - 2;
		F.zeile = zeile;
		moegliche_felder.push_back(F);
	}*/
	
}


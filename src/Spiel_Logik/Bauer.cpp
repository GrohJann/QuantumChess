#include "Bauer.h"
#include "Brett.h"
#include <vector>
#include <array>
using namespace std;



void Bauer::Set_Moegliche_Felder(Brett& spielfeld) {
	int z = -1;
	if (weiss) {
		z = 1;
	}
	if (zeile + z >= 8 && zeile + z <= 1) {
		for (int s = -1; s < 2; s++) {
			Moegliches_Feld F;
			if (spielfeld.Felder[spalte][zeile + z] == nullptr && s == 0) {
				F.spalte = spalte;
				F.zeile = zeile + z;
				moegliche_felder.push_back(F);
			}
			else if(spalte + s >= 1 && spalte + s <= 8){
				if (spielfeld.Felder[spalte + s - 1][zeile + z - 1] != nullptr) {
					if (spielfeld.Felder[spalte + s - 1][zeile + z - 1]->Get_Farbe() != weiss) {
						F.spalte = spalte + s;
						F.zeile = zeile + z;
						moegliche_felder.push_back(F);
					}
				}
			}
		}
	}

	if (!gezogen && spielfeld.Felder[spalte][zeile + z] == nullptr && spielfeld.Felder[spalte][zeile + (2 * z)] == nullptr) {
		Moegliches_Feld F;
		F.spalte = spalte;
		F.zeile = 2 * z;
		moegliche_felder.push_back(F);
	}
	
}
vector <Moegliches_Feld>  Bauer::Get_Moegliche_Felder() {

	return moegliche_felder;
}


#include "../Model/Turm.h"
//#include "Brett.h"
#include "Structs.h"
#include <vector>
using namespace std;

void Turm::Set_Moegliche_Felder(Brett spielfeld) {

	int s = spalte;
	for (s; s > 0; s--) { //links Bewegung
		Moegliches_Feld F;
		F.spalte = s;
		F.zeile = zeile;
		if (spielfeld.Felder[s - 1][zeile - 1] == nullptr) {
			moegliche_felder.push_back(F);
		}
		if (s != spalte && spielfeld.Felder[s - 1][zeile - 1] != nullptr) {
			if (spielfeld.Felder[s - 1][zeile - 1]->Get_Farbe() == weiss) {
				break;
			}
			else if (spielfeld.Felder[s - 1][zeile - 1]->Get_Farbe() != weiss) {
				moegliche_felder.push_back(F);
				break;
			}
		}
	}
	s = spalte;
	for (s; s < 9; s++) { //rechts Bewegung
		Moegliches_Feld F;
		F.spalte = s;
		F.zeile = zeile;
		if (spielfeld.Felder[s - 1][zeile - 1] == nullptr) {
			moegliche_felder.push_back(F);
		}
		if (s != spalte && spielfeld.Felder[s - 1][zeile - 1] != nullptr) {
			if (spielfeld.Felder[s - 1][zeile - 1]->Get_Farbe() == weiss) {
				break;
			}
			else if (spielfeld.Felder[s - 1][zeile - 1]->Get_Farbe() != weiss) {
				moegliche_felder.push_back(F);
				break;
			}
		}
	}
	int z = zeile;
	for (z; z < 9; z++) { //aufw�rts
		Moegliches_Feld F;
		F.spalte = spalte;
		F.zeile = z;
		if (spielfeld.Felder[spalte - 1][z - 1] == nullptr) {
			moegliche_felder.push_back(F);
		}
		if (z != spalte && spielfeld.Felder[spalte - 1][z - 1] != nullptr) {
			if (spielfeld.Felder[spalte - 1][z - 1]->Get_Farbe() == weiss) {
				break;
			}
			else if (spielfeld.Felder[spalte - 1][z - 1]->Get_Farbe() != weiss) {
				moegliche_felder.push_back(F);
				break;
			}
		}
	}
	z = zeile;
	for (z; z > 0; z--) { //abw�rts
		Moegliches_Feld F;
		F.spalte = s;
		F.zeile = zeile;
		if (spielfeld.Felder[spalte - 1][z - 1] == nullptr) {
			moegliche_felder.push_back(F);
		}
		if (z != spalte && spielfeld.Felder[spalte - 1][z - 1] != nullptr) {
			if (spielfeld.Felder[spalte - 1][z - 1]->Get_Farbe() == weiss) {
				break;
			}
			else if (spielfeld.Felder[spalte - 1][z - 1]->Get_Farbe() != weiss) {
				moegliche_felder.push_back(F);
				break;
			}
		}
	}
}

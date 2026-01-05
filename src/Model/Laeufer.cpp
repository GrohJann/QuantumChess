#include "Laeufer.h"
#include "Structs.h"
#include <vector>
using namespace std;


vector <Moegliches_Feld> Laeufer::Get_Moegliche_Felder() {

	return moegliche_felder;
}

void Laeufer::Set_Moegliche_Felder(Brett spielfeld) {
	moegliche_felder.clear();
	for (int i = 1; i < 8; i++) { // 45°
		Moegliches_Feld F;
		if (spalte + i <= 8 && zeile + i <= 8) { // feld aufm Brett
			if (spielfeld.Felder[spalte + i - 1][zeile + i - 1] == nullptr) {// feld leer
				F.spalte = spalte + i;
				F.zeile = zeile + i;
				moegliche_felder.push_back(F);
			}
			else {
				if (spielfeld.Felder[spalte + i - 1][zeile + i - 1]->Get_Farbe() != weiss) {
					F.spalte = spalte + i;
					F.zeile = zeile + i;
					moegliche_felder.push_back(F);
				}
				break;
			}
		}
	}
	for (int i = 1; i < 8; i++) { // 225°
		Moegliches_Feld F;
		if (spalte - i >= 1 && zeile - i >= 1) { // feld aufm Brett
			if (spielfeld.Felder[spalte - i - 1][zeile - i - 1] == nullptr) {
				F.spalte = spalte - i;
				F.zeile = zeile - i;
				moegliche_felder.push_back(F);
			}
			else {
				if (spielfeld.Felder[spalte - i - 1][zeile - i - 1]->Get_Farbe() != weiss) {
					F.spalte = spalte - i;
					F.zeile = zeile - i;
					moegliche_felder.push_back(F);
				}
				break;
			}
		}
	}
	for (int i = 1; i < 8; i++) { // 135°
		Moegliches_Feld F;
		if (spalte - i >= 1 && zeile + i <= 8) { // feld aufm Brett
			if (spielfeld.Felder[spalte - i - 1][zeile + i - 1] == nullptr) {
				F.spalte = spalte - i;
				F.zeile = zeile + i;
				moegliche_felder.push_back(F);

			}
			else {
				if (spielfeld.Felder[spalte - i - 1][zeile + i - 1]->Get_Farbe() != weiss) {
					F.spalte = spalte - i;
					F.zeile = zeile + i;
					moegliche_felder.push_back(F);
					break;
				}
				break;
			}
		}
	}
	for (int i = 1; i < 8; i++) { // 315°
		Moegliches_Feld F;
		if (spalte + i <= 8 && zeile - i >= 1) { // feld aufm Brett
			if (spielfeld.Felder[spalte + i - 1][zeile - i - 1] == nullptr) {
				F.spalte = spalte + i;
				F.zeile = zeile - i;
				moegliche_felder.push_back(F);
			}
			else {
				if (spielfeld.Felder[spalte + i - 1][zeile - i - 1]->Get_Farbe() != weiss) {
					F.spalte = spalte + i;
					F.zeile = zeile - i;
					moegliche_felder.push_back(F);
				}
				break;
			}
		}
	}
}

#include "Springer.h"
#include <vector>
#include <array>
using namespace std;

vector <Moegliches_Feld> Springer::Get_Moegliche_Felder() {

	return moegliche_felder;
}

void Springer::Set_Moegliche_Felder(Brett& spielfeld) {// bearbeiten

	/*int zeile = Get_Zeile();
	int spalte = Get_Spalte();

	// zeile +- 2 und spalte +- 1
	// zeile +- 1 und spalte +-2
	// vorausgesetzt  zeile und spalte wird nicht kleiner als 1 oder größer als 8
	// Stelle 0 = Spalte // Stelle 1 = Zeile



	if (spalte + 2 <= 8) { // zug nach oben rechts

		if (zeile + 2 <= 8) {
			moegliche_felder.push_back({ spalte + 1, zeile + 2 });
			moegliche_felder.push_back({ spalte + 2, zeile + 1 });
		}
		else if (zeile + 1 <= 8) {
			moegliche_felder.push_back({ spalte + 2, zeile + 1 });
		}
		else if (zeile - 2 >= 1) {
			moegliche_felder.push_back({ spalte + 1, zeile - 2 });
			moegliche_felder.push_back({ spalte + 2, zeile - 1 });
		}
		else if (zeile - 1 >= 1) {
			moegliche_felder.push_back({ spalte + 2, zeile - 1 });
		}
	}
	// überarbeiten

	if (spalte - 2 >= 1) { // zug nach unten rechts

		if (zeile + 2 <= 8) {
			moegliche_felder.push_back({ spalte - 1, zeile + 2 });
			moegliche_felder.push_back({ spalte - 2, zeile + 1 });
		}
		else if (zeile + 1 <= 8) {
			moegliche_felder.push_back({ spalte - 2, zeile + 1 });
		}
		else if (zeile - 2 >= 1) {
			moegliche_felder.push_back({ spalte - 1, zeile - 2 });
			moegliche_felder.push_back({ spalte - 2, zeile - 1 });
		}
		else if (zeile - 1 >= 1) {
			moegliche_felder.push_back({ spalte - 2, zeile - 1 });
		}
	}*/
}

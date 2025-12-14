#include "Figuren.h"
#include "Springer.h"
#include <vector>
#include <array>
using namespace std;

bool Springer::Get_Geschlagen() {
	return geschlagen;
}
bool Springer::Get_Farbe() {
	return schwarz;
}
int Springer::Get_Spalte() {
	return spalte;
}
int Springer::Get_Zeile() {
	return zeile;
}
vector <array<int, 2>> Springer::Get_Moegliche_Felder() {

	return moegliche_felder;
}

void Springer::Set_Geschlagen(bool neuer_zustand) {
	geschlagen = neuer_zustand;
}
void Springer::Set_Farbe(bool neue_farbe) {
	geschlagen = neue_farbe;
}
void Springer::Set_Spalte(int neue_spalte) {
	spalte = neue_spalte;
}
void Springer::Set_Zeile(int neue_zeile) {
	zeile = neue_zeile;
}



void Springer::Set_Moegliche_Felder() {// bearbeiten

	int zeile = Get_Zeile();
	int spalte = Get_Spalte();

	// zeile +- 2 und spalte +- 1
	// zeile +- 1 und spalte +-2
	// vorausgesetzt  zeile und spalte wird nicht kleiner als 1 oder gr��er als 8
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


	if (spalte - 2 >= 1 ) { // zug nach oben rechts

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
	}
}
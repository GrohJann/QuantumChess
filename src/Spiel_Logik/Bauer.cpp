#include "Bauer.h"
#include <vector>
using namespace std;

/*bool Bauer::Get_Geschlagen() {
	return geschlagen;
}
bool Bauer::Get_Farbe() {
	return schwarz;
}

int Bauer::Get_Spalte() {
	return spalte;
}
int Bauer::Get_Zeile() {
	return zeile;
}*/
vector <array<int, 2>> Bauer::Get_Moegliche_Felder() {

	return moegliche_felder;
}

/*void Bauer::Set_Geschlagen(bool neuer_zustand) {
	geschlagen = neuer_zustand;
}
void Bauer::Set_Farbe(bool neue_farbe) {
	geschlagen = neue_farbe;
}

void Bauer::Set_Spalte(int neue_spalte) {
	spalte = neue_spalte;
}
void Bauer::Set_Zeile(int neue_zeile) {
	zeile = neue_zeile;
}*/

void Bauer::Set_Moegliche_Felder() {

	if (gezogen && !schwarz && zeile  <= 8) {
		for (int s = -1; s < 2; s++) {
			if (spalte + s >= 1 && spalte + s <= 8) {
				moegliche_felder.push_back({ spalte + s , zeile + 1 });
			}
		}
	}
	if (!gezogen && !schwarz) {
		for (int s = -1; s < 2; s++) {
			if (spalte + s >= 1 && spalte + s <= 8) {
				moegliche_felder.push_back({ spalte + s , zeile + 1 });
			}
		}
		moegliche_felder.push_back({ spalte, zeile + 2 });	
	}

	if (gezogen && schwarz && zeile  >= 1) {
		for (int s = -1; s < 2; s++) {
			if (spalte + s >= 1 && spalte + s <= 8) {
				moegliche_felder.push_back({ spalte + s , zeile - 1 });
			}
		}
	}
	if (!gezogen && schwarz) {
		for (int s = -1; s < 2; s++) {
			if (spalte + s >= 1 && spalte + s <= 8) {
				moegliche_felder.push_back({ spalte + s , zeile - 1 });
			}
		}
		moegliche_felder.push_back({ spalte, zeile - 2 });

	}
}

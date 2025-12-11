#include "Dame.h"

#include <vector>
using namespace std;

/*bool Dame::Get_Geschlagen() {
	return geschlagen;
}
bool Dame::Get_Farbe() {
	return schwarz;
}
int Dame::Get_Spalte() {
	return spalte;
}
int Dame::Get_Zeile() {
	return zeile;
}*/
vector <int[2]> Dame::Get_Moegliche_Felder() {

	return moegliche_felder;
}

/*void Dame::Set_Geschlagen(bool neuer_zustand) {
	geschlagen = neuer_zustand;
}
void Dame::Set_Farbe(bool neue_farbe) {
	geschlagen = neue_farbe;
}
void Dame::Set_Spalte(int neue_spalte) {
	spalte = neue_spalte;
}
void Dame::Set_Zeile(int neue_zeile) {
	zeile = neue_zeile;
}*/
void Dame::Set_Moegliche_Felder() {

	for (int i = -7; i < 8; i++) { // 
		if (spalte + i <= 8 && spalte + i >= 1 && i != 0) {
			if (zeile + i <= 8 && zeile + i >= 1 && i != 0) {
				moegliche_felder.push_back({ spalte + i, zeile + i });
			}
		}
	}

	for (int s = -7; s < 8; s++) {
		for (int z = -7; z < 8; z++) {
			if (z + s == 0) {
				if (spalte + s <= 8 && spalte + s >= 1 && s != 0) {
					if (zeile + z <= 8 && zeile + z >= 1 && z != 0) {
						moegliche_felder.push_back({ spalte + s, zeile + z });
					}
				}
			}
		}
	}
	for (int i = 1; i < 9; i++) {//vertikal
		if (i != zeile) {
			moegliche_felder.push_back({ spalte,i });
		}
	}
	for (int i = 1; i < 9; i++) { // horizontal
		if (i != spalte) {
			moegliche_felder.push_back({ i, zeile });
		}
	}
}

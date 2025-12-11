#include "Laeufer.h"

#include <vector>
using namespace std;

/*bool Laeufer::Get_Geschlagen() {
	return geschlagen;
}
bool Laeufer::Get_Farbe() {
	return schwarz;
}
int Laeufer::Get_Spalte() {
	return spalte;
}
int Laeufer::Get_Zeile() {
	return zeile;
}*/
vector <int[2]> Laeufer::Get_Moegliche_Felder() {

	return moegliche_felder;
}
/*
void Laeufer::Set_Geschlagen(bool neuer_zustand) {
	geschlagen = neuer_zustand;
}
void Laeufer::Set_Farbe(bool neue_farbe) {
	geschlagen = neue_farbe;
}
void Laeufer::Set_Spalte(int neue_spalte) {
	spalte = neue_spalte;
}
void Laeufer::Set_Zeile(int neue_zeile) {
	zeile = neue_zeile;
}*/
void Laeufer::Set_Moegliche_Felder() {

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
}
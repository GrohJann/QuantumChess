#include "Figuren.h"
#include "Turm.h"
#include <vector>
using namespace std;

bool Turm::Get_Geschlagen() {
	return geschlagen;
}
bool Turm::Get_Farbe() {
	return istWeiss;
}
int Turm::Get_Spalte() {
	return spalte;
}
int Turm::Get_Zeile() {
	return zeile;
}
 vector <array<int, 2>> Turm::Get_Moegliche_Felder() {

	return moegliche_felder;
}

void Turm::Set_Geschlagen(bool neuer_zustand) {
	geschlagen = neuer_zustand;
}
void Turm::Set_Farbe(bool neue_farbe) {
	geschlagen = neue_farbe;
}
void Turm::Set_Spalte(int neue_spalte) {
	spalte = neue_spalte;
}
void Turm::Set_Zeile(int neue_zeile) {
	zeile = neue_zeile;
}
 void Turm::Set_Moegliche_Felder() {

	for (int i = 1; i < 9; i++) {//vertikal
		if (i != zeile) {	
			moegliche_felder.push_back({spalte,i});
		}
	}
	for (int i = 1; i < 9; i++) { // horizontal
		if (i !=spalte) {
			moegliche_felder.push_back({ i, zeile });
		}
	}
	
}
#include "Figuren.h"
#include "Koenig.h"
#include <vector>
using namespace std;

/*bool Koenig::Get_Geschlagen() {
	return geschlagen;
}
bool Koenig::Get_Farbe() {
	return schwarz;
}
int Koenig::Get_Spalte() {
	return spalte;
}
int Koenig::Get_Zeile() {
	return zeile;
}*/
vector <array<int, 2>> Koenig::Get_Moegliche_Felder() {

	return moegliche_felder;
}

/*void Koenig::Set_Geschlagen(bool neuer_zustand) {
	geschlagen = neuer_zustand;
}
void Koenig::Set_Farbe(bool neue_farbe) {
	geschlagen = neue_farbe;
}
void Koenig::Set_Spalte(int neue_spalte) {
	spalte = neue_spalte;
}
void Koenig::Set_Zeile(int neue_zeile) {
	zeile = neue_zeile;
}*/
void Koenig::Set_Moegliche_Felder() {

	if (spalte + 1 <= 8) {
		moegliche_felder.push_back({ spalte + 1,zeile });
		if (zeile + 1 <= 8) {
			moegliche_felder.push_back({ spalte + 1,zeile +1 });
		}
		else if (zeile - 1 >= 1) {
			moegliche_felder.push_back({ spalte + 1,zeile-1 });
		}
	}
	if (spalte - 1 >=1) {
		moegliche_felder.push_back({ spalte - 1,zeile });
		if (zeile + 1 <= 8) {
			moegliche_felder.push_back({ spalte - 1,zeile + 1 });
		}
		else if (zeile - 1 >= 1) {
			moegliche_felder.push_back({ spalte - 1,zeile - 1 });
		}
	}

}

#include "Figuren.h"
#include <vector>
using namespace std;

Figuren::Figuren(const bool istWeiss, const int zeile, const int spalte) {
	this->istWeiss = istWeiss;
	this->zeile = zeile;
	this->spalte = spalte;
}

bool Figuren::Get_Geschlagen() {
	return geschlagen;
}
bool Figuren::Get_Farbe() {
	return istWeiss;
}
int Figuren::Get_Spalte() {
	return spalte;
}
int Figuren::Get_Zeile() {
	return zeile;
}
bool Figuren::Get_Gezogen() {
	return gezogen;
}
std::vector<std::array<int, 2> > Figuren::Get_Moegliche_Felder() {
	return moegliche_felder;
}



void Figuren::Set_Geschlagen(bool neuer_zustand) {
	geschlagen = neuer_zustand;
}
void Figuren::Set_Farbe(bool neue_farbe) {
	geschlagen = neue_farbe;
}
void Figuren::Set_Spalte(int neue_spalte) {
	spalte = neue_spalte;
}
void Figuren::Set_Zeile(int neue_zeile) {
	zeile = neue_zeile;
}
void Figuren::Set_Gezogen(bool neuer_zustand) {
	gezogen = neuer_zustand;
}
void Figuren::Set_Moegliche_Felder() {
	moegliche_felder = {};
}

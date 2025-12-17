#include "Laeufer.h"
#include "Brett.h"
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
vector <Moegliches_Feld> Laeufer::Get_Moegliche_Felder() {

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
void Laeufer::Set_Moegliche_Felder(Brett& spielfeld) {

	for (int i = 1; i < 8; i++) { // 45°
		Moegliches_Feld F;
		if (spalte + i <= 8 && zeile + i <= 8) { // feld aufm Brett
			if (spielfeld.Felder[spalte + i - 1][zeile + i - 1] == nullptr) {
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
		if (spalte + i <= 8 && zeile + i >= 1) { // feld aufm Brett
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

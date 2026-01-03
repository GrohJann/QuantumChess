#include "../Spiel_Logik/Dame.h"
//#include "Brett.h"
#include "../Structs.h"
#include <vector>
using namespace std;





void Dame::Set_Moegliche_Felder(Brett spielfeld) {
	// Laeufer
	for (int i = 1; i < 8; i++) { // 45�
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
	for (int i = 1; i < 8; i++) { // 225�
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
	for (int i = 1; i < 8; i++) { // 135�
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
	for (int i = 1; i < 8; i++) { // 315�
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

	// Turm
	int s = spalte;

	for (s; s > 0; s--) { //links Bewegung
		Moegliches_Feld F;
		F.spalte = s;
		F.zeile = zeile;
		if (spielfeld.Felder[s - 1][zeile - 1] == nullptr) {
			moegliche_felder.push_back(F);
		}
		if (s != spalte && spielfeld.Felder[s - 1][zeile - 1] != nullptr) {
			if (spielfeld.Felder[s - 1][zeile - 1]->Get_Farbe() == weiss) {
				break;
			}
			else if (spielfeld.Felder[s - 1][zeile - 1]->Get_Farbe() != weiss) {
				moegliche_felder.push_back(F);
				break;
			}
		}
	}
	s = spalte;
	for (s; s < 9; s++) { //rechts Bewegung
		Moegliches_Feld F;
		F.spalte = s;
		F.zeile = zeile;
		if (spielfeld.Felder[s - 1][zeile - 1] == nullptr) {
			moegliche_felder.push_back(F);
		}
		if (s != spalte && spielfeld.Felder[s - 1][zeile - 1] != nullptr) {
			if (spielfeld.Felder[s - 1][zeile - 1]->Get_Farbe() == weiss) {
				break;
			}
			else if (spielfeld.Felder[s - 1][zeile - 1]->Get_Farbe() != weiss) {
				moegliche_felder.push_back(F);
				break;
			}
		}
	}
	int z = zeile;
	for (z; z < 9; z++) { //aufw�rts
		Moegliches_Feld F;
		F.spalte = spalte;
		F.zeile = z;
		if (spielfeld.Felder[spalte - 1][z - 1] == nullptr) {
			moegliche_felder.push_back(F);
		}
		if (z != spalte && spielfeld.Felder[spalte - 1][z - 1] != nullptr) {
			if (spielfeld.Felder[spalte - 1][z - 1]->Get_Farbe() == weiss) {
				break;
			}
			else if (spielfeld.Felder[spalte - 1][z - 1]->Get_Farbe() != weiss) {
				moegliche_felder.push_back(F);
				break;
			}
		}
	}
	z = zeile;
	for (z; z > 0; z--) { //abw�rts
		Moegliches_Feld F;
		F.spalte = s;
		F.zeile = zeile;
		if (spielfeld.Felder[spalte - 1][z - 1] == nullptr) {
			moegliche_felder.push_back(F);
		}
		if (z != spalte && spielfeld.Felder[spalte - 1][z - 1] != nullptr) {
			if (spielfeld.Felder[spalte - 1][z - 1]->Get_Farbe() == weiss) {
				break;
			}
			else if (spielfeld.Felder[spalte - 1][z - 1]->Get_Farbe() != weiss) {
				moegliche_felder.push_back(F);
				break;
			}
		}
	}
}
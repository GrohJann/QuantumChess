#include "Laeufer.h"
#include "Structs.h"
#include <vector>
using namespace std;


vector <Moegliches_Feld> Laeufer::Get_Moegliche_Felder() {

	return moegliche_felder;
}

/*void Laeufer::Set_Moegliche_Felder(Brett spielfeld) {
	moegliche_felder.clear();
	for (int i = 1; i < 8; i++) { // 45°
		Moegliches_Feld F;
		if (spalte + i <= 8 && zeile + i <= 8) { // feld aufm Brett
			if (spielfeld.Felder[spalte + i - 1][zeile + i - 1] == nullptr) {// feld leer
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
}*/


void Laeufer::Set_Moegliche_Felder(Brett spielfeld) { // Kopie
	moegliche_felder.clear();
	float p = 1.0;
	vector <int> sv;
	vector <int> zv;
	bool moving_over_self = false;
	
	// Hole allen alternativen Positione der Figur
	for (int i = 0; i < spielfeld.Felder[spalte - 1][zeile - 1]->Get_Same_Piece().size(); i++) {
		int s = spielfeld.Felder[spalte - 1][zeile - 1]->Get_Same_Piece()[i]->Get_Spalte();
		int z = spielfeld.Felder[spalte - 1][zeile - 1]->Get_Same_Piece()[i]->Get_Zeile();
		sv.push_back(s);
		zv.push_back(z);
	}



	for (int i = 1; i < 8; i++) { // 45°
		Moegliches_Feld F;
		F.wahrscheinlichkeit = p;
		if (spalte + i <= 8 && zeile + i <= 8) { // feld aufm Brett
			// Checken, ob die ueber eine alternative Position gezogen wird
			for (int j = 0; j < sv.size(); j++) {
				if (sv[j] == spalte + i && zv[j] == zeile + i) {
					moving_over_self = true;
					break;
				}
			}

			if (spielfeld.Felder[spalte + i - 1][zeile + i - 1] == nullptr) {// feld leer
				F.spalte = spalte + i;
				F.zeile = zeile + i;
				moegliche_felder.push_back(F);
			}
			else {
				if (spielfeld.Felder[spalte + i - 1][zeile + i - 1]->Get_Wahrscheinlichkeit() == 1.0 || moving_over_self) {			
					if (spielfeld.Felder[spalte + i - 1][zeile + i - 1]->Get_Farbe() != weiss ) {
						F.spalte = spalte + i;
						F.zeile = zeile + i;
						moegliche_felder.push_back(F);
						break;
					}
					else {
						
						break;
					}
				}
				else {
					p = 1 - spielfeld.Felder[spalte + i - 1][zeile + i - 1]->Get_Wahrscheinlichkeit();
					F.spalte = spalte + i;
					F.zeile = zeile + i;
					moegliche_felder.push_back(F);
				}
			}
		}	
	}
	p = 1.0;
	moving_over_self = false;
	for (int i = 1; i < 8; i++) { // 225°
		Moegliches_Feld F;
		F.wahrscheinlichkeit = p;
		if (spalte - i >= 1 && zeile - i >= 1) { // feld aufm Brett
			  

			for (int j = 0; j < sv.size(); j++) {
				if (sv[j] == spalte - i && zv[j] == zeile - i) {
					moving_over_self = true;
					break;
				}
			}

			if (spielfeld.Felder[spalte - i - 1][zeile - i - 1] == nullptr) {
				F.spalte = spalte - i;
				F.zeile = zeile - i;
				moegliche_felder.push_back(F);
			}
			else {
				if (spielfeld.Felder[spalte - i - 1][zeile - i - 1]->Get_Wahrscheinlichkeit() == 1.0 || moving_over_self) {			
					if (spielfeld.Felder[spalte - i - 1][zeile - i - 1]->Get_Farbe() != weiss ) {
						F.spalte = spalte - i;
						F.zeile = zeile - i;
						moegliche_felder.push_back(F);
						break;
					}
					else {
						
						break;
					}
				}
				else {
					p = 1 - spielfeld.Felder[spalte - i - 1][zeile - i - 1]->Get_Wahrscheinlichkeit();
					F.spalte = spalte - i;
					F.zeile = zeile - i;
					moegliche_felder.push_back(F);
				}
			}
		}
	}
	p = 1.0;
	moving_over_self = false;
	for (int i = 1; i < 8; i++) { // 135°
		Moegliches_Feld F;
		if (spalte - i >= 1 && zeile + i <= 8) { // feld aufm Brett

			for (int j = 0; j < sv.size(); j++) {
				if (sv[j] == spalte - i && zv[j] == zeile + i) {
					moving_over_self = true;
					break;
				}
			}
			if (spielfeld.Felder[spalte - i - 1][zeile + i - 1] == nullptr) {
				F.spalte = spalte - i;
				F.zeile = zeile + i;
				moegliche_felder.push_back(F);

			}
			else {
				if (spielfeld.Felder[spalte - i - 1][zeile + i - 1]->Get_Wahrscheinlichkeit() == 1.0 || moving_over_self) {
					if (spielfeld.Felder[spalte - i - 1][zeile + i - 1]->Get_Farbe() != weiss) {
						F.spalte = spalte - i;
						F.zeile = zeile + i;
						moegliche_felder.push_back(F);
						break;
					}
					else {
						break;
					}
				}
				else {
					p = 1 - spielfeld.Felder[spalte - i - 1][zeile + i - 1]->Get_Wahrscheinlichkeit();
					F.spalte = spalte - i;
					F.zeile = zeile + i;
					moegliche_felder.push_back(F);
				}
			}
		}
	}
	p = 1.0;
	moving_over_self = false;
	for (int i = 1; i < 8; i++) { // 315°
		Moegliches_Feld F;
		if (spalte + i <= 8 && zeile - i >= 1) { // feld aufm Brett

			for (int j = 0; j < sv.size(); j++) {
				if (sv[j] == spalte + i && zv[j] == zeile - i) {
					moving_over_self = true;
					break;
				}
			}


			if (spielfeld.Felder[spalte + i - 1][zeile - i - 1] == nullptr) {
				F.spalte = spalte + i;
				F.zeile = zeile - i;
				moegliche_felder.push_back(F);
			}
			else {
				if (spielfeld.Felder[spalte + i - 1][zeile - i - 1]->Get_Wahrscheinlichkeit() == 1.0 || moving_over_self) {
					if (spielfeld.Felder[spalte + i - 1][zeile - i - 1]->Get_Farbe() != weiss) {
						F.spalte = spalte + i;
						F.zeile = zeile - i;
						moegliche_felder.push_back(F);
						break;
					}
					else {
						break;
					}
				}
				else {
					p = 1 - spielfeld.Felder[spalte + i - 1][zeile - i - 1]->Get_Wahrscheinlichkeit();
					F.spalte = spalte + i;
					F.zeile = zeile - i;
					moegliche_felder.push_back(F);
				}
			}
		}
	}
}

#include "SDL_Test_alt.h"

#include <iostream>
#include <SDL3/SDL.h>
#include "Brett.h"
#include "../Spiel_Logik/Figuren.h"
#include "../Model/Bauer.h"
#include "../Spiel_Logik/Dame.h"
#include "../Model/Koenig.h"
#include "../Spiel_Logik/Laeufer.h"
#include "../Spiel_Logik/Springer.h"
#include "../Spiel_Logik/Turm.h"

void Spielfeld_Reset(Brett& spielfeld) {

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			spielfeld.Felder[i][j] = nullptr;
		}
	}
}
void Startaufstellung_Bauern(vector <Bauer>& bauern, Brett& spielfeld) {

	for (int i = 1; i < 17; i++) {
		Bauer b;
		b.Set_Geschlagen(false);
		b.Set_Gezogen(false);
		b.Set_Name('b');
		if (i <= 8) {
			b.Set_Farbe(true); // true = weiss
			b.Set_Zeile(2);
			b.Set_Spalte(i);
			b.Set_Dateipfad("../assets/chess_pieces/pawn_w.png");
		}
		else {
			b.Set_Farbe(false);
			b.Set_Zeile(7);
			b.Set_Spalte(i - 8);
			b.Set_Dateipfad("../assets/chess_pieces/pawn_b.png");

		}
		bauern.push_back(b);
	}
	for (int i = 0; i < bauern.size(); i++) {
		spielfeld.Felder[bauern[i].Get_Spalte() - 1][bauern[i].Get_Zeile() - 1] = &bauern[i];
	}
}
void Startaufstellung_Springer(vector <Springer>& springer, Brett& spielfeld) {

	for (int i = 1; i < 5; i++) {
		Springer S;
		S.Set_Geschlagen(false);
		S.Set_Name('S');
		if (i <= 2) {
			S.Set_Farbe(true);
			S.Set_Zeile(1);
			S.Set_Dateipfad("../assets/chess_pieces/knight_w.png");
			switch (i)
			{
			case 1:
				S.Set_Spalte(2);
				break;

			case 2:
				S.Set_Spalte(7);
				break;
			}
		}
		else {
			S.Set_Farbe(false);
			S.Set_Zeile(8);
			S.Set_Dateipfad("../assets/chess_pieces/knight_b.png");
			switch (i)
			{
			case 3:
				S.Set_Spalte(2);
				break;

			case 4:
				S.Set_Spalte(7);
				break;
			}
		}
		springer.push_back(S);
	}
	for (int i = 0; i < springer.size(); i++) {
		spielfeld.Felder[springer[i].Get_Spalte() - 1][springer[i].Get_Zeile() - 1] = &springer[i];
	}


}
void Startaufstellung_Laeufer(vector <Laeufer>& laeufer, Brett& spielfeld) {
	for (int i = 1; i < 5; i++) {
		Laeufer L;
		L.Set_Geschlagen(false);
		L.Set_Name('L');
		if (i <= 2) {
			L.Set_Farbe(true);
			L.Set_Zeile(1);
			L.Set_Dateipfad("../assets/chess_pieces/bishop_w.png");
			switch (i)
			{
			case 1:
				L.Set_Spalte(3);
				break;

			case 2:
				L.Set_Spalte(6);
				break;
			}
		}
		else {
			L.Set_Farbe(false);
			L.Set_Zeile(8);
			L.Set_Dateipfad("../assets/chess_pieces/bishop_b.png");
			switch (i)
			{
			case 3:
				L.Set_Spalte(3);
				break;

			case 4:
				L.Set_Spalte(6);
				break;
			}
		}

		laeufer.push_back(L);
	}
	for (int i = 0; i < laeufer.size(); i++) {
		spielfeld.Felder[laeufer[i].Get_Spalte() - 1][laeufer[i].Get_Zeile() - 1] = &laeufer[i];
	}

}
void Startaufstellung_Tuerme(vector <Turm>& tuerme, Brett& spielfeld) {
	for (int i = 1; i < 5; i++) {
		Turm T;
		T.Set_Geschlagen(false);
		T.Set_Gezogen(false);
		T.Set_Name('T');
		if (i <= 2) {
			T.Set_Farbe(true);
			T.Set_Zeile(1);
			T.Set_Dateipfad("../assets/chess_pieces/rook_w.png");
			switch (i)
			{
			case 1:
				T.Set_Spalte(1);
				break;

			case 2:
				T.Set_Spalte(8);
				break;
			}
		}
		else {
			T.Set_Farbe(false);
			T.Set_Zeile(8);
			T.Set_Dateipfad("../assets/chess_pieces/rook_b.png");
			switch (i)
			{
			case 3:
				T.Set_Spalte(1);
				break;

			case 4:
				T.Set_Spalte(8);
				break;
			}
		}
		tuerme.push_back(T);
	}
	for (int i = 0; i < tuerme.size(); i++) {
		spielfeld.Felder[tuerme[i].Get_Spalte() - 1][tuerme[i].Get_Zeile() - 1] = &tuerme[i];
	}
}
void Startaufstellung_Damen(vector <Dame>& damen, Brett& spielfeld) {
	for (int i = 1; i < 3; i++) {
		Dame D;
		D.Set_Geschlagen(false);
		D.Set_Spalte(4);
		D.Set_Name('D');
		if (i == 1) {
			D.Set_Farbe(true);
			D.Set_Zeile(1);
			D.Set_Dateipfad("../assets/chess_pieces/queen_w.png");
		}
		else {
			D.Set_Farbe(false);
			D.Set_Zeile(8);
			D.Set_Dateipfad("../assets/chess_pieces/queen_b.png");
		}
		damen.push_back(D);
	}
	for (int i = 0; i < damen.size(); i++) {
		spielfeld.Felder[damen[i].Get_Spalte() - 1][damen[i].Get_Zeile() - 1] = &damen[i];
	}
}
void Startaufstellung_Koenige(vector <Koenig>& koenige, Brett& spielfeld) {
	for (int i = 1; i < 3; i++) {
		Koenig K;
		K.Set_Geschlagen(false);
		K.Set_Gezogen(false);
		K.Set_Name('K');
		K.Set_Spalte(5);
		if (i == 1) {
			K.Set_Farbe(true);
			K.Set_Zeile(1);
			K.Set_Dateipfad("../assets/chess_pieces/king_w.png");
		}
		else {
			K.Set_Farbe(false);
			K.Set_Zeile(8);
			K.Set_Dateipfad("../assets/chess_pieces/king_b.png");
		}
		koenige.push_back(K);
	}
	for (int i = 0; i < koenige.size(); i++) {
		spielfeld.Felder[koenige[i].Get_Spalte() - 1][koenige[i].Get_Zeile() - 1] = &koenige[i];
	}
}

int main() {

	Brett Spielfeld;
	vector <Bauer> bauern;
	vector <Springer> springer;
	vector <Laeufer> laeufer;
	vector <Turm> tuerme;
	vector <Dame> damen;
	vector <Koenig> koenige;

	Spielfeld_Reset(Spielfeld);
	Startaufstellung_Bauern(bauern, Spielfeld);
	Startaufstellung_Springer(springer, Spielfeld);
	Startaufstellung_Laeufer(laeufer, Spielfeld);
	Startaufstellung_Tuerme(tuerme, Spielfeld);
	Startaufstellung_Damen(damen, Spielfeld);
	Startaufstellung_Koenige(koenige, Spielfeld);

	run(Spielfeld);
}
#include "Spiel_Logik.h"

void Erstes_Feld(int s, int z, Brett& spielfeld) {
	Check_for_Mate(spielfeld);
	if (spielfeld.schachmatt) {
		return;
	}
	
	int spalte_ziel = s;
	int zeiel_ziel = z;
	vector <Moegliches_Feld> moegliche_felder;
	if (!spielfeld.piece_selected) {
		if (spielfeld.Felder[s - 1][z - 1] != nullptr) {
			if (spielfeld.Felder[s - 1][z - 1]->Get_Farbe() == spielfeld.whites_turn)
				spielfeld.piece_selected = true;
			spielfeld.selected_piece_s = s;
			spielfeld.selected_piece_z = z;
			cout << spielfeld.Felder[s - 1][z - 1]->Get_Name() << " gewaehlt" << endl;
		}
	}
	else {
		vector <Moegliches_Feld> moegliche_felder;
		spielfeld.Felder[spielfeld.selected_piece_s - 1][spielfeld.selected_piece_z - 1]->Set_Moegliche_Felder(spielfeld);

		moegliche_felder = spielfeld.Felder[spielfeld.selected_piece_s - 1][spielfeld.selected_piece_z - 1]->Get_Moegliche_Felder();
		if (moegliche_felder.size() == 0) {
			cout << "Keine moeglichen felder" << endl;

		}
		for (int i = 0; i < moegliche_felder.size(); i++) {

			if (moegliche_felder[i].spalte == s && moegliche_felder[i].zeile == z) {
				if (King_selected(spielfeld.selected_piece_s, spielfeld.selected_piece_z, spielfeld)) {
					Check_Castle_Selected(i, moegliche_felder, spielfeld);
				}
				if (spielfeld.en_passant) {
					Check_For_En_Passant(i, moegliche_felder, spielfeld);
				}
				Check_For_Double_Pawn(i, moegliche_felder, spielfeld);
				Ziehen(spielfeld.selected_piece_s, spielfeld.selected_piece_z, s, z, spielfeld);
				spielfeld.whites_turn = !spielfeld.whites_turn;
				spielfeld.piece_selected = false;
				break;
			}
			else {
				cout << "Kein gueltiges Feld ausgewaehlt" << endl;
			}
		}
		spielfeld.piece_selected = false;
		
	}
}

void Ziehen (int sa, int za, int s, int z, Brett & spielfeld){
	
	spielfeld.Felder[s - 1][z - 1] = spielfeld.Felder[sa - 1][za - 1];
	spielfeld.Felder[s - 1][z - 1]->Set_Spalte(s);
	spielfeld.Felder[s - 1][z - 1]->Set_Zeile(z);
	spielfeld.Felder[s - 1][z - 1]->Set_Gezogen(true);

	spielfeld.Felder[sa - 1][za - 1] = nullptr;



	cout << "Figur gezogen" << endl;
	
}

bool King_selected(int s, int z, Brett& spielfeld) {

	if (s == 5 && (z == 8 || z == 1)) {
		if (!spielfeld.Felder[s - 1][z - 1]->Get_Gezogen()) {
			return true;
		}
	}
	else {
		return false;
	}
}
bool Check_For_scw(Brett& spielfeld) {
	bool scw = false;
	if (spielfeld.Felder[5 - 1][1 - 1] != nullptr && spielfeld.Felder[8 - 1][1 - 1] != nullptr) {
		if (!spielfeld.Felder[5 - 1][1 - 1]->Get_Gezogen() && !spielfeld.Felder[8 - 1][1 - 1]->Get_Gezogen()) {
			if (spielfeld.Felder[6 - 1][0] == nullptr && spielfeld.Felder[7 - 1][0] == nullptr) {
				scw = true;
			}
		}
	}
	return scw;
}
bool Check_For_lcw(Brett& spielfeld) {
	bool lcw = false;
	if (spielfeld.Felder[5 - 1][1 - 1] != nullptr && spielfeld.Felder[1 - 1][1 - 1] != nullptr) {
		if (!spielfeld.Felder[5 - 1][1 - 1]->Get_Gezogen() && !spielfeld.Felder[1 - 1][1 - 1]->Get_Gezogen()) {
			if (spielfeld.Felder[2 - 1][1 - 1] == nullptr && spielfeld.Felder[3 - 1][1 - 1] == nullptr && spielfeld.Felder[4 - 1][1 - 1]) {
				lcw = true;
			}
		}
	}
	return lcw;
}
bool Check_For_scb(Brett& spielfeld) {
	bool scb = false;
	if (spielfeld.Felder[5 - 1][8 - 1] != nullptr && spielfeld.Felder[8 - 1][8 - 1] != nullptr) {
		if (!spielfeld.Felder[5 - 1][8 - 1]->Get_Gezogen() && !spielfeld.Felder[8 - 1][8 - 1]->Get_Gezogen()) {
			if (spielfeld.Felder[6 - 1][8 - 1] == nullptr && spielfeld.Felder[7 - 1][8 - 1] == nullptr) {
				scb = true;
			}
		}
	}
	return scb;
}
bool Check_For_lcb(Brett& spielfeld) {
	bool lcb = false;
	if (spielfeld.Felder[5 - 1][8 - 1] != nullptr && spielfeld.Felder[1 - 1][8 - 1] != nullptr) {
		if (!spielfeld.Felder[5 - 1][8 - 1]->Get_Gezogen() && !spielfeld.Felder[1 - 1][8 - 1]->Get_Gezogen()) {
			if (spielfeld.Felder[2 - 1][8 - 1] == nullptr && spielfeld.Felder[3 - 1][8 - 1] == nullptr && spielfeld.Felder[4 - 1][8 - 1] == nullptr) {
				lcb = true;
			}
		}
	}
	return lcb;
}
	
void Check_Castle_Selected(int i, vector <Moegliches_Feld> moegliche_felder, Brett& spielfeld) {
	bool scw = Check_For_scw(spielfeld);
	bool lcw = Check_For_lcw(spielfeld);
	bool scb = Check_For_scb(spielfeld);
	bool lcb = Check_For_lcb(spielfeld);
	
	if (!scw && !lcb && !spielfeld.whites_turn) {
		return ;
	}
	if (spielfeld.whites_turn) {
		if (!scw && !lcw ) {
			return;
		}
		if (scw && !lcw ) {
			if (i == moegliche_felder.size() - 1) {
				Ziehen(8, 1, 6, 1, spielfeld);
				return;
			}
		}
		if (lcw && !scw ) {
			if (i == moegliche_felder.size() - 1) {
				Ziehen(1, 1, 4, 1, spielfeld);
				return;
			}
		}

		if (scw && lcw ) {
			if (i == moegliche_felder.size() - 1) {
				Ziehen(1, 1, 4, 1, spielfeld); // lc
				return;
			}
		}
		if (scw && lcw ) {
			if (i == moegliche_felder.size() - 2) {
				Ziehen(8, 1, 6, 1, spielfeld); // sc
				return;
			}
		}
	}
	if (!spielfeld.whites_turn) {
		if (!scb && !lcb) {
			return;
		}
		if (scb && !lcb) {
			if (i == moegliche_felder.size() - 1) {
				Ziehen(8, 8, 6, 8, spielfeld);
				return;
			}
		}
		if (lcb && !scb) {
			if (i == moegliche_felder.size() - 1) {
				Ziehen(1, 8, 4, 8, spielfeld);
				return;
			}
		}

		if (scb && lcb) {
			if (i == moegliche_felder.size() - 1) {
				Ziehen(1, 8, 4, 8, spielfeld); // lc
				return;
			}
		}
		if (scb && lcb) {
			if (i == moegliche_felder.size() - 2) {
				Ziehen(8, 8, 6, 8, spielfeld); // sc
				return;
			}
		}
	}

}

void Check_for_Mate(Brett& spielfeld) {
	int k = 0;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (spielfeld.Felder[i][j] != nullptr) {
				if (spielfeld.Felder[i][j]->Get_Name() == 'K') {
					k++;
				}
			}
		}
	}
	if (k != 2) {
		spielfeld.schachmatt = true;
	}
}


bool Ceck_For_Promotion(Brett& spielfeld, vector <Dame>& damen){

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (spielfeld.Felder[i][j] != nullptr) {
				if (spielfeld.Felder[i][j]->Get_Name() == 'b') {
					int z = spielfeld.Felder[i][j]->Get_Zeile();
					if (z == 1 || z == 8) {
						Make_Queen(i + 1, z, spielfeld, damen);
						return true;
					}
				}
			}
		}
	}
	return false;
}
void Make_Queen(int s, int z, Brett& spielfeld, vector <Dame>& damen) {
	Dame D;

	D.Set_Zeile(z);
	D.Set_Spalte(s);
	D.Set_Farbe(spielfeld.Felder[s - 1][z - 1]->Get_Farbe());
	D.Set_Gezogen(true);

	if (D.Get_Farbe()) {
		D.Set_Dateipfad("C:\\Users\\Lenny\\OneDrive\\Hka\\Semester_2\\Schach_Projekt\\2x\\w_queen_2x.png");
	}
	else {
		D.Set_Dateipfad("C:\\Users\\Lenny\\OneDrive\\Hka\\Semester_2\\Schach_Projekt\\2x\\b_queen_2x.png");
	}
	damen.push_back(D);

	for (int i = 0; i < damen.size(); i++) {
		spielfeld.Felder[damen[i].Get_Spalte() - 1][damen[i].Get_Zeile() - 1] = &damen[i];
	}
	

}

void Check_For_Double_Pawn(int i, vector <Moegliches_Feld> moegliche_felder, Brett& spielfeld) {

	int s = spielfeld.selected_piece_s;
	int z = spielfeld.selected_piece_z;

	if (spielfeld.Felder[s-1][z-1]->Get_Name() == 'b' && !spielfeld.Felder[s - 1][z - 1]->Get_Gezogen()){
		if (i == moegliche_felder.size() - 1) {
			spielfeld.en_passant = true;
			spielfeld.en_passant_spalte = moegliche_felder[i].spalte;
			spielfeld.en_passant_zeile = moegliche_felder[i].zeile;

		}
		else if (i == moegliche_felder.size() - 2 && spielfeld.en_passant) {
			spielfeld.en_passant = true;
			spielfeld.en_passant_spalte = moegliche_felder[i].spalte;
			spielfeld.en_passant_zeile = moegliche_felder[i].zeile;
		}
		else {
			spielfeld.en_passant = false;
			spielfeld.en_passant_spalte = -2;
		}
	}
	else {
		spielfeld.en_passant = false;
		spielfeld.en_passant_spalte = -2;
	}

}
void Check_For_En_Passant(int i, vector <Moegliches_Feld> moegliche_felder, Brett& spielfeld) {
	int s = spielfeld.selected_piece_s;
	int z = spielfeld.selected_piece_z;
	if (i == moegliche_felder.size() - 1 && spielfeld.en_passant && spielfeld.en_passant_spalte != -2) {
		if (z == spielfeld.en_passant_zeile && (s == spielfeld.en_passant_spalte +1 || s == spielfeld.en_passant_spalte -1))

		spielfeld.Felder[spielfeld.en_passant_spalte -1][spielfeld.en_passant_zeile - 1] = nullptr;
	}
}


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
			b.Set_Dateipfad("C:\\Users\\Lenny\\OneDrive\\Hka\\Semester_2\\Schach_Projekt\\2x\\w_pawn_2x.png");
			//bmp:			"C:\\Users\\Lenny\\OneDrive\\Hka\\Semester_2\\Schach_Projekt\\2x\\w_pawn_2x.bmp"
		}
		else {
			b.Set_Farbe(false);
			b.Set_Zeile(7);
			b.Set_Spalte(i - 8);
			b.Set_Dateipfad("C:\\Users\\Lenny\\OneDrive\\Hka\\Semester_2\\Schach_Projekt\\2x\\b_pawn_2x.png");

		}\
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
			S.Set_Dateipfad("C:\\Users\\Lenny\\OneDrive\\Hka\\Semester_2\\Schach_Projekt\\2x\\w_knight_2x.png");
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
			S.Set_Dateipfad("C:\\Users\\Lenny\\OneDrive\\Hka\\Semester_2\\Schach_Projekt\\2x\\b_knight_2x.png");
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
			L.Set_Dateipfad("C:\\Users\\Lenny\\OneDrive\\Hka\\Semester_2\\Schach_Projekt\\2x\\w_bishop_2x.png");
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
			L.Set_Dateipfad("C:\\Users\\Lenny\\OneDrive\\Hka\\Semester_2\\Schach_Projekt\\2x\\b_bishop_2x.png");

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
			T.Set_Dateipfad("C:\\Users\\Lenny\\OneDrive\\Hka\\Semester_2\\Schach_Projekt\\2x\\w_rook_2x.png");
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
			T.Set_Dateipfad("C:\\Users\\Lenny\\OneDrive\\Hka\\Semester_2\\Schach_Projekt\\2x\\b_rook_2x.png");
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
			D.Set_Dateipfad("C:\\Users\\Lenny\\OneDrive\\Hka\\Semester_2\\Schach_Projekt\\2x\\w_queen_2x.png");
		}
		else {
			D.Set_Farbe(false);
			D.Set_Zeile(8);
			D.Set_Dateipfad("C:\\Users\\Lenny\\OneDrive\\Hka\\Semester_2\\Schach_Projekt\\2x\\b_queen_2x.png");
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
			K.Set_Dateipfad("C:\\Users\\Lenny\\OneDrive\\Hka\\Semester_2\\Schach_Projekt\\2x\\w_king_2x.png");
		}
		else {
			K.Set_Farbe(false);
			K.Set_Zeile(8);
			K.Set_Dateipfad("C:\\Users\\Lenny\\OneDrive\\Hka\\Semester_2\\Schach_Projekt\\2x\\b_king_2x.png");
		}
		koenige.push_back(K);
	}
	for (int i = 0; i < koenige.size(); i++) {
		spielfeld.Felder[koenige[i].Get_Spalte() - 1][koenige[i].Get_Zeile() - 1] = &koenige[i];
	}
}





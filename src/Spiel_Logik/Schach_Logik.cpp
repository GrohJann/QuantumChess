

#include <iostream>
#include <SDL3/SDL.h>
#include "Brett.h"
#include "Figuren.h"
#include "Bauer.h"
#include "Dame.h"
#include "Koenig.h"
#include "Laeufer.h"
#include "Springer.h"
#include "Turm.h"



using namespace std;




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
			b.Set_Dateipfad("Weisser Bauer");
		}
		else {
			b.Set_Farbe(false);
			b.Set_Zeile(7);
			b.Set_Spalte(i - 8);
			b.Set_Dateipfad("Schwarze Bauer");

		}
		bauern.push_back(b); 	
	}
	for (int i = 0; i < bauern.size(); i++) {
		spielfeld.Felder  [bauern[i].Get_Spalte() - 1]  [bauern[i].Get_Zeile() - 1]   = &bauern[i];
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
			S.Set_Dateipfad("Weisser Springer");
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
			S.Set_Dateipfad("Schwarzer Springer");
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
			L.Set_Dateipfad("Weisser Laeufer");
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
			L.Set_Dateipfad("Schwarzer Laeufer");
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
			T.Set_Dateipfad("Weisser Turm");
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
			T.Set_Dateipfad("Schwarzer Turm");
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
			D.Set_Dateipfad("Weisse Dame");
		}
		else {
			D.Set_Farbe(false);
			D.Set_Zeile(8);
			D.Set_Dateipfad("Schwarze Dame");
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
			K.Set_Dateipfad("Weisser Koenig");
		}
		else {
			K.Set_Farbe(false);
			K.Set_Zeile(8);
			K.Set_Dateipfad("Schwarzer Koenig");
		}
		koenige.push_back(K);
	}
	for (int i = 0; i < koenige.size(); i++) {
		spielfeld.Felder[koenige[i].Get_Spalte() - 1][koenige[i].Get_Zeile() - 1] = &koenige[i];
	}
}


// vielleicht muss man noch nach jedem Zug die Pointer nue definieren, aber eigentlich nich da sich die Vektoren nicht veraendern
// wenn dann im Quantenschach neue Figuren dazukommen und sich der Vektor erweitert ist das jedoch wichtig
// Oder im normalen schach für die Umwandlung
void Set_Ptr_Bauern(vector <Bauer>& bauern, Brett& spielfeld) {
	for (int i = 0; i < bauern.size(); i++) {
		if (!spielfeld.Felder[bauern[i].Get_Spalte() - 1][bauern[i].Get_Zeile() - 1]->Get_Geschlagen())
			spielfeld.Felder[bauern[i].Get_Spalte() - 1][bauern[i].Get_Zeile() - 1] = &bauern[i];
	}
}
void Set_Ptr_Stpinger(vector <Springer>& springer, Brett& spielfeld) {
	for (int i = 0; i < springer.size(); i++) {
		if (!spielfeld.Felder[springer[i].Get_Spalte() - 1][springer[i].Get_Zeile() - 1]->Get_Geschlagen())
			spielfeld.Felder[springer[i].Get_Spalte() - 1][springer[i].Get_Zeile() - 1] = &springer[i];
	}
}
void Set_Ptr_Laeufer(vector <Laeufer>& laeufer, Brett& spielfeld) {
	for (int i = 0; i < laeufer.size(); i++) {
		if (!spielfeld.Felder[laeufer[i].Get_Spalte() - 1][laeufer[i].Get_Zeile() - 1]->Get_Geschlagen())
			spielfeld.Felder[laeufer[i].Get_Spalte() - 1][laeufer[i].Get_Zeile() - 1] = &laeufer[i];
	}
}
void Set_Ptr_Tuerme(vector <Turm>& tuerme, Brett& spielfeld) {
	for (int i = 0; i < tuerme.size(); i++) {
		if (!spielfeld.Felder[tuerme[i].Get_Spalte() - 1][tuerme[i].Get_Zeile() - 1]->Get_Geschlagen())
			spielfeld.Felder[tuerme[i].Get_Spalte() - 1][tuerme[i].Get_Zeile() - 1] = &tuerme[i];
	}
}
void Set_Ptr_Damen(vector <Dame>& damen, Brett& spielfeld) {
	for (int i = 0; i < damen.size(); i++) {
		if (!spielfeld.Felder[damen[i].Get_Spalte() - 1][damen[i].Get_Zeile() - 1]->Get_Geschlagen())
			spielfeld.Felder[damen[i].Get_Spalte() - 1][damen[i].Get_Zeile() - 1] = &damen[i];
	}
}
void Set_Ptr_Koenige(vector <Koenig>& koenige, Brett& spielfeld) {
	for (int i = 0; i < koenige.size(); i++) {
		if (!spielfeld.Felder[koenige[i].Get_Spalte() - 1][koenige[i].Get_Zeile() - 1]->Get_Geschlagen())
			spielfeld.Felder[koenige[i].Get_Spalte() - 1][koenige[i].Get_Zeile() - 1] = &koenige[i];
	}
}


void Bauern_Umwandlung(int spalte, int zeile, vector <Dame>& damen, Brett& spielfeld) {
	
	if (zeile == 1 && !spielfeld.Felder[spalte - 1][zeile - 1]->Get_Farbe() || zeile == 8 && spielfeld.Felder[spalte - 1][zeile - 1]->Get_Farbe()) {
		Dame D;
		D.Set_Spalte(spielfeld.Felder[spalte - 1][zeile - 1]->Get_Spalte()); // noch in Bearbeitung
	}

}


bool Erstes_Feld(int spalte, int zeile, Brett spielfeld, bool weiss_am_zug, vector <Moegliches_Feld> & moegliche_Felder) {

	if (spielfeld.Felder[spalte - 1][zeile - 1] == nullptr) {
		return false;
	}
	if (spielfeld.Felder[spalte - 1][zeile - 1]->Get_Farbe() != weiss_am_zug) {
		return false;
	}
	spielfeld.Felder[spalte - 1][zeile - 1]->Set_Moegliche_Felder(spielfeld);
	moegliche_Felder = spielfeld.Felder[spalte - 1][zeile - 1]->Get_Moegliche_Felder();
	return true; 	
}

int  Zweites_Feld(int spalte, int zeile, vector <Moegliches_Feld> moegliche_Felder) {

	for (int i = 0; i < moegliche_Felder.size(); i++) {
		if (moegliche_Felder[i].spalte == spalte && moegliche_Felder[i].zeile == zeile) {	
			return i;
		}
	}
	return -1;
}

void Ziehen(int spalte_ausgang, int zeile_ausgang, int i, vector <Moegliches_Feld>& moegliche_Felder, Brett& spielfeld) {

	int spalte_ziel = moegliche_Felder[i].spalte;
	int zeile_ziel = moegliche_Felder[i].zeile;


	if (spielfeld.Felder[spalte_ziel - 1][zeile_ziel - 1] != nullptr) { // falls auf dem Feld nh Figur steht
		spielfeld.Felder[spalte_ziel - 1][zeile_ziel - 1]->Set_Geschlagen(true); // Figur wird geschlagen
		spielfeld.Felder[spalte_ziel - 1][zeile_ziel - 1] = nullptr; // Pointer auf die Figur zeigt jetzt auf null
	}
	
	spielfeld.Felder[spalte_ziel - 1][zeile_ziel - 1] = spielfeld.Felder[spalte_ausgang - 1][zeile_ausgang - 1]; // pointer auf ziehende Figur aendert das Feld (wird kopiert)
	spielfeld.Felder[spalte_ausgang - 1][zeile_ausgang - 1] = nullptr; // pointer auf alter position wird zum nullptr (wird "geloescht")
	spielfeld.Felder[spalte_ziel - 1][zeile_ziel - 1]->Set_Spalte(spalte_ziel);
	spielfeld.Felder[spalte_ziel - 1][zeile_ziel - 1]->Set_Zeile(zeile_ziel);

	if (!spielfeld.Felder[spalte_ziel - 1][zeile_ziel - 1]->Get_Gezogen()) {
		spielfeld.Felder[spalte_ziel - 1][zeile_ziel - 1]->Set_Gezogen(true); // gezogen wird true gesetzt 
	}
	moegliche_Felder.clear();

}

void Check_For_Mate(bool& schachmatt, bool& verlierer_farbe, vector <Koenig> koenige) {

	for (int i = 0; i < koenige.size(); i++) {
		if (koenige[i].Get_Geschlagen()) {
			schachmatt = true;
			verlierer_farbe = koenige[i].Get_Farbe();
			break;
		}
	}
}
int main()
{
	Brett Spielfeld;
	
	vector <Bauer> bauern;
	vector <Springer> springer;
	vector <Laeufer> laeufer;
	vector <Turm> tuerme;
	vector <Dame> damen;
	vector <Koenig> koenige;

	vector <Moegliches_Feld> moegliche_Felder;

	Spielfeld_Reset(Spielfeld);
	Startaufstellung_Bauern(bauern, Spielfeld);
	Startaufstellung_Springer(springer, Spielfeld);
	Startaufstellung_Laeufer(laeufer, Spielfeld);
	Startaufstellung_Tuerme(tuerme, Spielfeld);
	Startaufstellung_Damen(damen, Spielfeld);
	Startaufstellung_Koenige(koenige, Spielfeld);





	for (int i = 7; i > -1; i--) {//Zeile	
		for (int j = 0; j < 8; j++) { // Spalte
			if (Spielfeld.Felder[j][i] != nullptr) {
				char  a;
				
				a = Spielfeld.Felder[j][i]->Get_Name();
				
				cout << a;
				//cout << b;
				cout << "   ";
			}			
		}
		cout << endl;
	} // nur zum überprüfen

	bool weiss_am_zug = true;
	bool schachmatt = false;
	bool verlierer_farbe;

	while (!schachmatt) { 
		// Irgendwie muss es hier bei der Netzwerkprogrammierung noch moeglich werden, dass nicht ein Spieler beide Farben bewegt, und auch nur ziehen kann wenn er am Zug ist
		// bis jetzt isses nur so dass die farben im Wechsel bewegt werden muessen, der selbe Spieler kann trotzdem beide bewegen
		
		int z_1 = -1; // hier muss eine Funktion die Zeile des ersten angeklickten Feldes uebertragen  (SDL)
		int s_1 = -1; // dasselbe für die Spalte (SDL)

		cin >> s_1; // Platzhalter für die Funktion
		cin >> z_1; // "..."
		if (Erstes_Feld(s_1, z_1, Spielfeld, weiss_am_zug, moegliche_Felder)) {

			int s_2 = -1;
			int z_2 = -1; //  hier muss eine Funktion die Zeile des zweiten angeklickten Feldes uebertragen
			
			while (z_2 == -1 && s_2 == -1) { // haelt den Spieler hier bis irgendein Feld ausgewaehlt wurde
				
				cin >> s_2;
				cin >> z_2;

				if (Zweites_Feld(s_2, z_2, moegliche_Felder) != -1) { // preuft, ob die Figir dahin ziehen darf

					int i = Zweites_Feld(s_2, z_2, moegliche_Felder);
					Ziehen(s_1, z_1, i, moegliche_Felder, Spielfeld); // bewegt Figur
					
					if (weiss_am_zug) {
						weiss_am_zug = false;
					}
					else {
						weiss_am_zug = true;
					}
				}
				else {
					break; // falls kein gueltiges Feld ausgewaehlt wurde, muss eine neue Figur ausgewaehlt werden
				}
			}
		}
		Check_For_Mate(schachmatt,verlierer_farbe,koenige);
	}
	if (verlierer_farbe) {
		cout << "Schwarz gewinnt" << endl;
	}
	else {
		cout << "Weiss gewinnt" <<  endl;
	}

	/*for (int i = 0; i < 8; i++) {//Zeile
		for (int j = 0; j < 8; j++) { // Spalte
			
			if (Spielfeld.Felder[j][i] != nullptr) {
				

				Spielfeld.Felder[j][i]->Set_Moegliche_Felder(Spielfeld);
				
				vector <Moegliches_Feld> felder = Spielfeld.Felder[j][i]->Get_Moegliche_Felder();
				if (felder.size() != 0)
				{
					cout << Spielfeld.Felder[j][i]->Get_Name();
					for (int k = 0; k < felder.size(); k++) {
						cout << " Feld: " << felder[k].spalte << felder[k].zeile << "    " ;
					}
					cout << endl;
				}
			}
		}
		cout << endl;
	}*/





	

}


		
		
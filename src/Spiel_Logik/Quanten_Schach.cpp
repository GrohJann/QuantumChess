

#include <iostream>
#include "Quanten_Schach.h"
#include "Figuren.h"
#include "Bauer.h"
#include "Dame.h"
#include "Koenig.h"
#include "Laeufer.h"
#include "Springer.h"
#include "Turm.h"

using namespace std; 


void Startaufstellung_Bauern(vector <Bauer> &bauern, Figuren* (&Spielfeld)[8][8]) {

	for (int i = 1; i < 17; i++) {
		Bauer b;
		b.Set_Geschlagen(false);
		b.Set_Gezogen(false);
		if (i <= 8) {
			b.Set_Farbe(false);
			b.Set_Zeile(2);
			b.Set_Spalte(i);	
			
		}
		else {
			b.Set_Farbe(true);
			b.Set_Zeile(7);
			b.Set_Spalte(i-8);
			
		}
		Spielfeld[b.Get_Spalte() - 1][b.Get_Zeile() - 1] = &b;
		bauern.push_back(b); // Vektor �berhaupt notwendig
	}
}
void Startaufstellung_Springer(vector <Springer> &springer, Figuren* (&Spielfeld)[8][8]) {

	for (int i = 1; i < 5; i++) {
		Springer S;
		S.Set_Geschlagen(false);
		if (i <= 2) {
			S.Set_Farbe(false);
			S.Set_Zeile(1);
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
			S.Set_Farbe(true);
			S.Set_Zeile(8);
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
		Spielfeld[S.Get_Spalte() - 1][S.Get_Zeile() - 1] = &S;
		springer.push_back(S);


	}

}
void Startaufstellung_Laeufer(vector <Laeufer>& laeufer, Figuren* (&Spielfeld)[8][8]) {
	for (int i = 1; i < 5; i++) {
		Laeufer L;
		L.Set_Geschlagen(false);
		if (i <= 2) {
			L.Set_Farbe(false);
			L.Set_Zeile(1);
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
			L.Set_Farbe(true);
			L.Set_Zeile(8);
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
		Spielfeld[L.Get_Spalte() - 1][L.Get_Zeile() - 1] = &L;
		laeufer.push_back(L);
	}
}
void Startaufstellung_Tuerme(vector <Turm>& tuerme, Figuren* (&Spielfeld)[8][8]) {
	for (int i = 1; i < 5; i++) {
		Turm T;
		T.Set_Geschlagen(false);
		T.Set_Gezogen(false);
		if (i <= 2) {
			T.Set_Farbe(false);
			T.Set_Zeile(1);
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
			T.Set_Farbe(true);
			T.Set_Zeile(8);
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
		Spielfeld[T.Get_Spalte() - 1][T.Get_Zeile() - 1] = &T;
		tuerme.push_back(T);
	}
}
void Startaufstellung_Damen(vector <Dame>& damen, Figuren* (&Spielfeld)[8][8]) {
	for (int i = 1; i < 3; i++) {
		Dame D;
		D.Set_Geschlagen(false);
		D.Set_Spalte(4);
		if (i == 1) {
			D.Set_Farbe(false);
			D.Set_Zeile(1);
		}
		else {
			D.Set_Farbe(true);
			D.Set_Zeile(8);
		}
		Spielfeld[D.Get_Spalte() - 1][D.Get_Zeile() - 1] = &D;
		damen.push_back(D);
	}
	
}
void Startaufstellung_Koenige(vector <Koenig>& koenige, Figuren* (&Spielfeld)[8][8]) {
	for (int i = 1; i < 3; i++) {
		Koenig K;
		K.Set_Geschlagen(false);
		K.Set_Gezogen(false);
		K.Set_Spalte(5);
		if (i == 1) {
			K.Set_Farbe(false);
			K.Set_Zeile(1);
		}
		else {
			K.Set_Farbe(true);
			K.Set_Zeile(8);
		}
		Spielfeld[K.Get_Spalte() - 1][K.Get_Zeile() - 1] = &K;
		koenige.push_back(K);
	}
}


void Initialisieren_Feld_Weiss(bool (&weiss) [8][8]) {

	for (int i = 1; i < 9; i++) {// Spalten
		for (int j = 1; j < 9; j++) {// Zeilen
			if (i <= 2) {
				weiss[i - 1][j - 1] = true;
			}
			else {
				weiss[i - 1][j - 1] = false;
			}
		}
	}
}
void Initialisieren_Feld_Schwarz(bool(&schwarz)[8][8]) {
	for (int i = 1; i < 9; i++) {// Spalten
		for (int j = 1; j < 9; j++) {// Zeilen
			if (i >= 7) {
				schwarz[i - 1][j - 1] = true;
			}
			else {
				schwarz[i - 1][j - 1] = false;
			}
		}
	}
}
void Initialisieren_Feld_Gesamt(bool(&gesamt)[8][8]) {
	for (int i = 1; i < 9; i++) {// Spalten
		for (int j = 1; j < 9; j++) {// Zeilen
			if (i >= 7 || i <=2) {
				gesamt[i - 1][j - 1] = true;
			}
			else {
				gesamt[i - 1][j - 1] = false;
			}
		}
	}
}



void Spielfeld_Initialisieren(Figuren* (&Spielfeld)[8][8]) {
	
	
}
int run_logic()
{
	bool weiss[8][8];
	bool schwarz[8][8];
	bool gesamt[8][8];
	Figuren* Spielfeld[8][8]; // damit




	/* TEST


	Figuren F;
	Bauer b;
	Figuren* Test = &F;
	Bauer* Test1 = &b;
	Test = Test1;
	
	Test1->Get_Moegliche_Felder();
	Test->Get_Moegliche_Felder();


	TEST ENDE */ 





	vector <Bauer> bauern;
	vector <Springer> springer;
	vector <Laeufer> laeufer;
	vector <Turm> tuerme;
	vector <Dame> damen;
	vector <Koenig> koenige;

	Startaufstellung_Bauern(bauern,Spielfeld);
	Startaufstellung_Springer(springer, Spielfeld);
	Startaufstellung_Laeufer (laeufer, Spielfeld);
	Startaufstellung_Tuerme(tuerme, Spielfeld);
	Startaufstellung_Damen(damen, Spielfeld);
	Startaufstellung_Koenige(koenige, Spielfeld);

	// Wahrscheinlich weg
	Initialisieren_Feld_Weiss(weiss);
	Initialisieren_Feld_Schwarz(schwarz);
	Initialisieren_Feld_Gesamt(gesamt);


	return 0;
}



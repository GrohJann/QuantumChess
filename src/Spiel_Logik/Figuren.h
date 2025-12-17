#pragma once

#include <vector>
#include <array>

using namespace std;
struct Brett;
struct Moegliches_Feld;

class Figuren
{

protected:

	bool geschlagen = false; // koenig
	bool weiss = true;
	bool gezogen = false; // Turm Bauer Koenig
	// bool gewaehlt = false;
	// float wahrscheinlichkeit = 1;
	//

	vector <Moegliches_Feld> moegliche_felder;
	int spalte = 0;
	int  zeile = 0;


public:
	
	virtual bool Get_Geschlagen();
	virtual bool Get_Farbe();
	virtual int Get_Spalte();
	virtual int Get_Zeile();
	virtual bool Get_Gezogen();
	virtual vector <Moegliches_Feld> Get_Moegliche_Felder();
	virtual void Set_Geschlagen(bool neuer_zustand);
	virtual void Set_Farbe(bool neue_farbe);
	virtual void Set_Spalte(int neue_Spalte);
	virtual void Set_Zeile(int neue_Zeile);
	virtual void Set_Gezogen(bool neuer_zustand);
	virtual void Set_Moegliche_Felder(Brett& spielfeld);



};


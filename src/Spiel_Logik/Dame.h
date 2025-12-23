#pragma once
#include "Figuren.h"
#include <vector>
#include <array>
using namespace std;
class Dame : public Figuren
{

public:
	using Figuren::Figuren; // verwende den Constructor der Figuren-Klassse
	//bool Get_Geschlagen();
	//bool Get_Farbe();
	//int Get_Spalte();
	//int Get_Zeile();
	vector <array<int, 2>> Get_Moegliche_Felder() override;

	//void Set_Geschlagen(bool neuer_zustand);
	//void Set_Farbe(bool neue_farbe);
	//void Set_Spalte(int neue_Spalte);
	//void Set_Zeile(int neue_Zeile);
	void Set_Moegliche_Felder() override;

private:
	//bool geschlagen = false;
	//bool schwarz = false;
	// bool gewaehlt = false;
	// float wahrscheinlichkeit = 1;
	//
	//int spalte;
	//int  zeile;
	vector <array<int, 2>>  moegliche_felder; // Stelle 0 = Spalte // Stelle 1 = Zeile
};

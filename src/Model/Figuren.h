#pragma once
#include <SDL3/SDL.h>
#include <vector>
#include <array>
#include <string>

using namespace std;
struct Brett;
struct Moegliches_Feld;

class Figuren
{

protected:

	bool geschlagen = false; // koenig
	bool weiss = true;
	bool gezogen = false; // Turm Bauer Koenig
	char name = 'F';
	int id = 0;

	// bool gewaehlt = false;
	float wahrscheinlichkeit = 1.0f;
	//

	vector <Moegliches_Feld> moegliche_felder;
	int spalte = 0;
	int  zeile = 0;

	// Ausgabe:
	string dateipfad = "leer";
	SDL_Texture* texture_ptr = nullptr;


public:
	virtual ~Figuren() = default;

	virtual char Get_Name();
	virtual bool Get_Geschlagen();
	virtual bool Get_Farbe();
	virtual int Get_Spalte();
	virtual int Get_Zeile();
	virtual bool Get_Gezogen();
	virtual vector <Moegliches_Feld> Get_Moegliche_Felder();
	virtual string Get_Dateipfad();
	virtual SDL_Texture* Get_Texture();
	virtual float Get_Wahrscheinlichkeit();
	virtual int Get_ID();

	virtual void Set_Name(char neuer_name);
	virtual void Set_Geschlagen(bool neuer_zustand);
	virtual void Set_Farbe(bool neue_farbe);
	virtual void Set_Spalte(int neue_Spalte);
	virtual void Set_Zeile(int neue_Zeile);
	virtual void Set_Gezogen(bool neuer_zustand);
	virtual void Set_Moegliche_Felder(Brett spielfeld);
	virtual void Set_Wahrscheinlichkeit(float wahrscheinlichkeit);
	virtual void Set_ID(int id);

	// 
	virtual void Set_Dateipfad(string neuer_dateipfad);
	virtual void Set_Texture(SDL_Texture* neuer_texture_ptr);




};

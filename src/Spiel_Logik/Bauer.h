#pragma once
//#include "../Spiel_Logik/Brett.h"
#include "../Spiel_Logik/Figuren.h"
#include <vector>
#include <array>
using namespace std;
class Bauer : public Figuren
{
public:
	virtual vector <Moegliches_Feld> Get_Moegliche_Felder();
	virtual void Set_Moegliche_Felder(Brett spielfeld);
};


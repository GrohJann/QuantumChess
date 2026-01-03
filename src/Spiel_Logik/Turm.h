#pragma once
//#include "Brett.h"
#include "Figuren.h"
#include <vector>
#include <array>
using namespace std;
class Turm : public Figuren
{
private:
	//vector <Moegliches_Feld>  moegliche_felder;
public:

	//vector <Moegliches_Feld> Get_Moegliche_Felder() override;
	void Set_Moegliche_Felder(Brett spielfeld) override;
};

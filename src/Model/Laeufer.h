#pragma once
//#include "Brett.h"
#include "Figuren.h"
#include <vector>
#include <array>
using namespace std;
class Laeufer : public Figuren {

public:
	void Set_Moegliche_Felder(Brett spielfeld) override;
};

#pragma once
#include "../Model/Figuren.h"
#include <vector>
#include <array>
using namespace std;
class Bauer : public Figuren
{
public:
	void Set_Moegliche_Felder(Brett spielfeld) override;
};


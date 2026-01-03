#pragma once
#include "Figuren.h"
#include <vector>
#include <array>
using namespace std;
class Turm : public Figuren
{
public:

	void Set_Moegliche_Felder(Brett spielfeld) override;
};

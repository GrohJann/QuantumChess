#pragma once
#include "../Deprecated/Brett.h"
#include "Figuren.h"
#include <vector>
#include <array>
using namespace std;
class Koenig : public Figuren
{
public:

	void Set_Moegliche_Felder(Brett spielfeld) override;
};

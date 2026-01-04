

#include <iostream>
#include "SDL_Test.h"
#include "SDL.h"
#include "Brett.h"
#include "Figuren.h"
#include "Bauer.h"
#include "Dame.h"
#include "Koenig.h"
#include "Laeufer.h"
#include "Springer.h"
#include "Turm.h"
#include <vector>

using namespace std; //notwendig vor vector

struct Brett;
struct Moegliches_Feld;

void Erstes_Feld(int s, int z, Brett& spielfeld);
void Ziehen(int sa, int za, int s, int z, Brett& spielfeld);
bool King_selected(int s, int z, Brett& spielfeld);
bool Check_For_scw(Brett &spielfeld);
bool Check_For_lcw(Brett& spielfeld);
bool Check_For_scb(Brett& spielfeld);
bool Check_For_lcb(Brett& spielfeld);
void Check_Castle_Selected(int i, vector <Moegliches_Feld> moegliche_felder, Brett& spielfeld);
void Check_for_Mate(Brett& spielfeld);
bool Ceck_For_Promotion(Brett& spielfeld, vector <Dame>& damen);
void Make_Queen(int s, int z, Brett& spielfeld, vector <Dame>& damen);
void Check_For_Double_Pawn(int i, vector <Moegliches_Feld> moegliche_felder, Brett& spielfeld);
void Check_For_En_Passant(int i, vector <Moegliches_Feld> moegliche_felder, Brett& spielfeld);

void Spielfeld_Reset(Brett& spielfeld);
void Startaufstellung_Bauern(vector <Bauer>& bauern, Brett& spielfeld);
void Startaufstellung_Springer(vector <Springer>& springer, Brett& spielfeld);
void Startaufstellung_Laeufer(vector <Laeufer>& laeufer, Brett& spielfeld);
void Startaufstellung_Tuerme(vector <Turm>& tuerme, Brett& spielfeld);
void Startaufstellung_Damen(vector <Dame>& damen, Brett& spielfeld);
void Startaufstellung_Koenige(vector <Koenig>& koenige, Brett& spielfeld);
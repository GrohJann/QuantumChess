#pragma once
#include "../Model/Figuren.h"
struct Brett_deprecated
{
	Figuren* Felder[8][8];
	/*bool scw = false;
	bool lcw = false;
	bool scb = false;
	bool lcb = false;*/

	bool piece_selected = false;
	int selected_piece_s = -1;
	int selected_piece_z = -1;


	bool whites_turn = true;
	bool schachmatt = false;



	bool en_passant = false;
	int en_passant_spalte = -2;
	int en_passant_zeile = -2;

};
/*struct Moegliches_Feld
{
	int spalte;
	int zeile;
};*/

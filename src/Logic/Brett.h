#pragma once
#include "Figuren.h"
/*struct Brett
{
	Figuren* Felder[8][8];
};
*/
struct Brett
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

struct Moegliches_Feld
{
	int spalte;
	int zeile;
};

struct Window_Configuration {
	int WindowWidth = 960;
	int WindowHeight = 720;
	int minWidth = 640;
	int minHeight = 480;
};

struct Layout {
	float sidebarRatio = 0.2f;   // 20 % UI
	float sidebarWidth;
	float WidthMinusSidebar;
	float boardSize;
};

struct MoveButton {
	SDL_Texture* normal;
	SDL_Texture* split;
	SDL_Texture* merge;
	bool normal_move = true;
	bool split_move = false;
	bool merge_move = false;

};

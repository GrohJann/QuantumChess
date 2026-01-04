//#include "Brett.h"
#include "Structs.h"
#include "../Model/Figuren.h"

#include <vector>
#include <string>
using namespace std;


SDL_Texture* Figuren::Get_Texture() {
	return texture_ptr;
}
string Figuren::Get_Dateipfad() {
	return dateipfad;
}
char Figuren::Get_Name() {
	return name;
}
bool Figuren::Get_Geschlagen() {
	return geschlagen;
}
bool Figuren::Get_Farbe() {
	return weiss;
}
int Figuren::Get_Spalte() {
	return spalte;
}
int Figuren::Get_Zeile() {
	return zeile;
}
bool Figuren::Get_Gezogen() {
	return gezogen;
}
vector <Moegliches_Feld> Figuren::Get_Moegliche_Felder() {
	return moegliche_felder;
}
float Figuren::Get_Wahrscheinlichkeit() {
	return wahrscheinlichkeit;
}
int Figuren::Get_ID() {
	return id;
}

void Figuren::Set_Name(char neuer_name) {
	name = neuer_name;
}
void Figuren::Set_Geschlagen(bool neuer_zustand) {
	geschlagen = neuer_zustand;
}
void Figuren::Set_Farbe(bool neue_farbe) {
	weiss = neue_farbe;
}
void Figuren::Set_Spalte(int neue_spalte) {
	spalte = neue_spalte;
}
void Figuren::Set_Zeile(int neue_zeile) {
	zeile = neue_zeile;
}
void Figuren::Set_Gezogen(bool neuer_zustand) {
	gezogen = neuer_zustand;
}
void Figuren::Set_Moegliche_Felder(Brett spielfeld) {
	return;
}

void Figuren::Set_Dateipfad(string neuer_dateipfad) {
	dateipfad = neuer_dateipfad;
}

void Figuren::Set_Texture(SDL_Texture* neue_texture_ptr) {
	texture_ptr = neue_texture_ptr;
}

void Figuren::Set_Wahrscheinlichkeit(const float wahrscheinlichkeit) {
	this->wahrscheinlichkeit = wahrscheinlichkeit;
}

void Figuren::Set_ID(int id) {
	this->id = id;
}


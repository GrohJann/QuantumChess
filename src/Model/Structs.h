/**
 * @file Structs.h
 * @brief A set of Structs used in the programm
 *
 * @author GrohJann
 * @date 05/12/2025
 */


#ifndef QUANTUMCHESS_STRUCTS_H
#define QUANTUMCHESS_STRUCTS_H

#include <memory>

#include "Figuren.h"

enum MoveMode : uint8_t {
    NORMAL,
    SPLIT,
    MERGE,
};

struct Color {
    Uint8 r;
    Uint8 g;
    Uint8 b;
    Uint8 a;
};

struct ColorScheme {
    Color black;
    Color white;
};

struct Brett {
    //todo: remove
    unique_ptr<Figuren> Felder[8][8];
    //Figuren* Felder[8][8];
};

struct Moegliches_Feld {
    int spalte;
    int zeile;
};

struct MoveBtnTex {
    SDL_Texture* normal;
    SDL_Texture* split;
    SDL_Texture* merge;
};

struct TilePos {
    Uint8 row;
    Uint8 col;
};

#endif //QUANTUMCHESS_STRUCTS_H
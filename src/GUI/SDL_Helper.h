/**
 * @file SDL_Helper.h
 * @brief Headerfile for a set of Functions usefull when using SDL
 *
 * @author GrohJann
 * @date 05/12/2025
 */

#ifndef QUANTUMCHESS_SDL_HELPER_H
#define QUANTUMCHESS_SDL_HELPER_H

#include "SDL3/SDL_rect.h"

#include "../Model/Structs.h"


bool PointInRect(const float* x, const float* y, const SDL_FRect* rect);
TilePos GetTileFromMousePos(const float& mouseX, const float& mouseY, const SDL_FRect* board);

#endif //QUANTUMCHESS_SDL_HELPER_H
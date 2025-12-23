/**
 * @file SDL_Test.h
 * @brief TODO: Add a short description of what this file does.
 *
 * @author GrohJann
 * @date 05/12/2025
 */
#ifndef QUANTUMCHESS_SDL_TEST_H
#define QUANTUMCHESS_SDL_TEST_H

#include <SDL3/SDL_render.h>
#include <SDL3/SDL_video.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_init.h>

#include "../Spiel_Logik/Bauer.h"
#include "../Spiel_Logik/Dame.h"
#include "../Spiel_Logik/Figuren.h"
#include "../Spiel_Logik/Koenig.h"
#include "../Spiel_Logik/Laeufer.h"
#include "../Spiel_Logik/Springer.h"
#include "../Spiel_Logik/Turm.h"

struct QuantumChessSquare;
struct FigureTextures;
struct AppState;

using Board = std::array<std::array<QuantumChessSquare*, 8>, 8>;

SDL_AppResult AppInit(void **appstate);
SDL_AppResult AppIterate(void *appstate);
SDL_AppResult AppEvent(void *appstate, SDL_Event* event);
void AppQuit(void *appstate, SDL_AppResult result);

bool CreateFigureTextures(SDL_Renderer* renderer, FigureTextures* whiteFigures, FigureTextures* blackFigures);
//void InitChessBoard(Board& board);
Board InitChessBoard();
SDL_Texture* GetFigureTexture(const char* file, SDL_Renderer* renderer);
bool drawChessboard(AppState* state);
bool pointInRect(const float* x, const float* y, const SDL_FRect* rect);
void handleNormalChessMove(AppState* state);

int run();


#endif //QUANTUMCHESS_SDL_TEST_H
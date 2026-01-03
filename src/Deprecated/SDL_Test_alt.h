
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
struct Brett;

SDL_AppResult SDL_AppInit(void** appstate);
SDL_AppResult AppIterate(void* appstate, Brett& Spielfeld);
SDL_AppResult AppEvent(void* appstate, SDL_Event* event, float* mouseX, float* mouseY);
void AppQuit(void* appstate, SDL_AppResult result);

void createTexture(void* appstate, Brett& Spielfeld);
int drawChessboard(SDL_Window* window, SDL_Renderer* renderer);
void RenderChessTextures(SDL_Window* window, SDL_Renderer* renderer, Brett& Spielfeld);
void calculateFieldFromCoordinates(void* appstate, const float& mouseX, const float& mouseY, int* selectedRow, int* selectedCol);
int run(Brett& Spielfeld);


#endif //QUANTUMCHESS_SDL_TEST_H
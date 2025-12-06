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


SDL_AppResult AppInit(void **appstate);
SDL_AppResult AppIterate(void *appstate);
SDL_AppResult AppEvent(void *appstate, SDL_Event* event);
void AppQuit(void *appstate, SDL_AppResult result);

int drawChessboard(SDL_Window* window, SDL_Renderer* renderer);

int run();


#endif //QUANTUMCHESS_SDL_TEST_H
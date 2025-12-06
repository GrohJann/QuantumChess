/**
 * @file SDL_Test.h
 * @brief TODO: Add a short description of what this file does.
 *
 * @author ruvaak
 * @date 05/12/2025
 */
#ifndef QUANTUMCHESS_SDL_TEST_H
#define QUANTUMCHESS_SDL_TEST_H

#include "SDL3/SDL_render.h"
#include "SDL3/SDL_video.h"


static SDL_AppResult AppInit(void **appstate);
static SDL_AppResult AppIterate(void *appstate);
static SDL_AppResult AppEvent(void *appstate, SDL_Event* event);
static void AppQuit(void *appstate, SDL_AppResult result);

static int drawChessboard(SDL_Window* window, SDL_Renderer* renderer);

static int run();


#endif //QUANTUMCHESS_SDL_TEST_H
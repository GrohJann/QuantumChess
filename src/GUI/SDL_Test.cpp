/**
 * @file SDL_Test.cpp
 * @brief A test implementation of the chessboard gui
 *
 * @author GrohJann
 * @date 05/12/2025
 */

#include <iostream>
#include <SDL3_image/SDL_image.h>

#include "../GUI/SDL_Test.h"

struct FigureTextures {
    SDL_Texture* rookTexture;
    SDL_Texture* knightTexture;
    SDL_Texture* bishopTexture;
    SDL_Texture* queenTexture;
    SDL_Texture* kingTexture;
    SDL_Texture* pawnTexture;
};

struct AppState {
    const char* title;
    SDL_Window* window;
    SDL_Renderer* renderer;
    FigureTextures whiteFigures;
    FigureTextures blackFigures;
    bool redraw = true;
};

/**
 * Initializes an SDL3 Window
 * @param appstate AppState struct to store information of the apps state in
 * @return SDL_APP_FAILURE to terminate with an error or SDL_APP_CONTINUE to continue.
 */
SDL_AppResult AppInit(void **appstate) {
    // allocate memory for AppState struct
    if (!(*appstate = SDL_malloc(sizeof(AppState)))) {
        return SDL_APP_FAILURE;
    }
    auto* state = static_cast<AppState*>(*appstate);
    state -> title = "Quantum Chess";

    if (!SDL_Init(SDL_INIT_VIDEO))
        return SDL_APP_FAILURE;

    int width = 800;
    int height = 800;
    if (!(state->window = SDL_CreateWindow(state->title, width, height, SDL_WINDOW_RESIZABLE)))
        return SDL_APP_FAILURE;
    SDL_SetWindowAspectRatio(state -> window, 1.0f, 1.0f);

    if (!(state->renderer = SDL_CreateRenderer(state->window, NULL)))
        return SDL_APP_FAILURE;

    // make figure Textures
    if (!CreateFigureTextures(state->renderer, &state->whiteFigures, &state->blackFigures))

    std::cout << "Program loaded!" << std::endl;
    return SDL_APP_CONTINUE;
}

// TODO: add javadoc
bool CreateFigureTextures(SDL_Renderer* renderer, FigureTextures* whiteFigures, FigureTextures* blackFigures) {
    // create white figure textures
    if (!(whiteFigures -> rookTexture = GetFigureTexture("../assets/rook_w.svg", renderer)))
        return false;
    if (!(whiteFigures -> knightTexture = GetFigureTexture("../assets/knight_w.svg", renderer)))
        return false;
    if (!(whiteFigures -> bishopTexture = GetFigureTexture("../assets/bishop_w.svg", renderer)))
        return false;
    if (!(whiteFigures -> queenTexture = GetFigureTexture("../assets/queen_w.svg", renderer)))
        return false;
    if (!(whiteFigures -> kingTexture = GetFigureTexture("../assets/king_w.svg", renderer)))
        return false;
    if (!(whiteFigures -> pawnTexture = GetFigureTexture("../assets/pawn_w.svg", renderer)))
        return false;

    // create black figure textures
    if (!(blackFigures -> rookTexture = GetFigureTexture("../assets/rook_b.svg", renderer)))
        return false;
    if (!(blackFigures -> knightTexture = GetFigureTexture("../assets/knight_b.svg", renderer)))
        return false;
    if (!(blackFigures -> bishopTexture = GetFigureTexture("../assets/bishop_b.svg", renderer)))
        return false;
    if (!(blackFigures -> queenTexture = GetFigureTexture("../assets/queen_b.svg", renderer)))
        return false;
    if (!(blackFigures -> kingTexture = GetFigureTexture("../assets/king_b.svg", renderer)))
        return false;
    if (!(blackFigures -> pawnTexture = GetFigureTexture("../assets/pawn_b.svg", renderer)))
        return false;

    return true;
}

// TODO: add javadoc
SDL_Texture* GetFigureTexture(const char* file, SDL_Renderer* renderer) {
    SDL_IOStream* io = SDL_IOFromFile(file, "rb");
    if (!io) {
        SDL_Log("Cannot open test.svg: %s", SDL_GetError());
        return NULL;
    }

    // Load and rasterize SVG to desired size
    SDL_Surface *surface = IMG_LoadSizedSVG_IO(io, 256, 256); // TODO: make size adjustable
    if (!(surface)) {
         SDL_Log("SVG load failed: %s", SDL_GetError());
         return NULL;
     }

    // Convert to texture
    return SDL_CreateTextureFromSurface(renderer, surface);
}

/**
 * Logic that needs to be done every frame
 * @param appstate AppState struct to store information of the apps state in
 * @return SDL_APP_FAILURE to terminate with an error, SDL_APP_SUCCESS to
 *         terminate with success, SDL_APP_CONTINUE to continue.
 */
SDL_AppResult AppIterate(void *appstate) {
    auto* state = static_cast<AppState*>(appstate);

    if (state->redraw) {
        state->redraw = false;
        // TODO: redraw Frame
        // clear frame buffer
        SDL_SetRenderDrawColor(state->renderer, 0, 0, 0, 255);
        SDL_RenderClear(state->renderer);

        // draw chessboard
        drawChessboard(state);

        // swap frame buffer
        SDL_RenderPresent(state->renderer);
    }

    return SDL_APP_CONTINUE;
}

// TODO: add javadoc
bool drawChessboard(AppState* state) {
    int w, h;
    constexpr int boardFields = 8;
    SDL_GetWindowSize(state -> window, &w, &h);

    // get size of squares
    const float squareSize = (w * 1.0f) / (boardFields * 1.0f);

    // render Background
    SDL_RenderClear(state -> renderer);

    // render squares
    for (int row = 0; row < boardFields; row++) {
        for (int col = 0; col < boardFields; col++) {

            // Alternate colors
            if ((row + col) % 2 == 0)
                SDL_SetRenderDrawColor(state->renderer, 236, 236, 208, 255);
            else
                SDL_SetRenderDrawColor(state->renderer, 119, 149, 87, 255);

            SDL_FRect rect = {col * squareSize, row * squareSize, squareSize, squareSize};

            bool success = SDL_RenderFillRect(state->renderer, &rect);

/********************************************************/
            if ( row == 0 ) {
                if (col == 0 || col == boardFields - 1) {
                    SDL_RenderTexture(state->renderer, state->blackFigures.rookTexture, nullptr, &rect);
                }else if (col == 1 || col == boardFields - 2) {
                    SDL_RenderTexture(state->renderer, state->blackFigures.knightTexture, nullptr, &rect);
                } else if (col == 2 || col == boardFields - 3) {
                    SDL_RenderTexture(state->renderer, state->blackFigures.bishopTexture, nullptr, &rect);
                } else if (col == 3) {
                    SDL_RenderTexture(state->renderer, state->blackFigures.queenTexture, nullptr, &rect);
                } else if (col == 4) {
                    SDL_RenderTexture(state->renderer, state->blackFigures.kingTexture, nullptr, &rect);
                }
            } else if (row == 1) {
                SDL_RenderTexture(state->renderer, state->blackFigures.pawnTexture, nullptr, &rect);
            } else if (row == 6) {
                SDL_RenderTexture(state->renderer, state->whiteFigures.pawnTexture, nullptr, &rect);
            }else if (row == 7) {
                if (col == 0 || col == boardFields - 1) {
                    SDL_RenderTexture(state->renderer, state->whiteFigures.rookTexture, nullptr, &rect);
                }else if (col == 1 || col == boardFields - 2) {
                    SDL_RenderTexture(state->renderer, state->whiteFigures.knightTexture, nullptr, &rect);
                } else if (col == 2 || col == boardFields - 3) {
                    SDL_RenderTexture(state->renderer, state->whiteFigures.bishopTexture, nullptr, &rect);
                } else if (col == 3) {
                    SDL_RenderTexture(state->renderer, state->whiteFigures.queenTexture, nullptr, &rect);
                } else if (col == 4) {
                    SDL_RenderTexture(state->renderer, state->whiteFigures.kingTexture, nullptr, &rect);
                }
            }
/*******************************************************/

            if (!success) {
                return false;
            }
        }
    }

    return true;
}

/**
 * Handles SDL events
 * @param appstate AppState struct to store information of the apps state in
 * @param event Pointer of the event to handle
* @return SDL_APP_FAILURE to terminate with an error, SDL_APP_SUCCESS to
 *        terminate with success, SDL_APP_CONTINUE to continue.
 */
SDL_AppResult AppEvent(void *appstate, SDL_Event* event) {
    auto* state = static_cast<AppState*>(appstate);

    switch (event->type) {
    case SDL_EVENT_WINDOW_PIXEL_SIZE_CHANGED: {
        int w, h;
        SDL_GetWindowSize(state->window, &w, &h);
        const int size = (w < h) ? w : h; // take the smaller dimension
        SDL_SetWindowSize(state->window, size, size);
        state->redraw = true;
        break;
    }
    case SDL_EVENT_QUIT:
        return SDL_APP_SUCCESS;
    default:    // ignore all events not listed above
        break;
    }

    return SDL_APP_CONTINUE;
}

/**
 * Gets called when quitting SDL
 * @param appstate AppState struct to store information of the apps state in
* @param result SDL_APP_FAILURE to terminate with an error, SDL_APP_SUCCESS to
 *              terminate with success, SDL_APP_CONTINUE to continue.
 */
void AppQuit(void *appstate, SDL_AppResult result) {
    //Cleanup here
    const auto* state = static_cast<AppState*>(appstate);
    SDL_DestroyRenderer(state->renderer);
    SDL_DestroyWindow(state->window);
    if (result == SDL_APP_FAILURE)
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error",
            SDL_GetError(), appstate ? state->window : NULL);
    SDL_free(appstate); // deallocate AppState
    SDL_Quit();
}

/**
 * Pseudo main function to run an SDL Window
 * @return error code
 */
int run() {
    // init SDL
    void* appstate = nullptr;
    SDL_AppResult result = AppInit(&appstate);
    if (result == SDL_APP_CONTINUE) {

        // main loop
        //bool running = true;
        SDL_Event event;

        while (true) {
            // handle events
            while (SDL_PollEvent(&event)) {
                result = AppEvent(appstate, &event);
                switch (result) {
                    case SDL_APP_SUCCESS:
                        AppQuit(appstate, result);
                        return 0;
                    case SDL_APP_FAILURE:
                        AppQuit(appstate, result);
                        return 1;
                    case SDL_APP_CONTINUE:
                    default:
                        break;
                }
            }

            // logic
            AppIterate(appstate);
        }
    }

    // Deconstruct
    AppQuit(appstate, result);
    return 0;
}
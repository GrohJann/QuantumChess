#define SDL_MAIN_USE_CALLBACKS
#include <iostream>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL.h>

#include "Logic/GameLogic.h"
#include "Model/Structs.h"
#include "GUI/SDL_Helper.h"
#include "GUI/ChesssBoardView.h"
//#include "Spiel_Logik/SDL_Test.h"

struct AppState {
    const char* title;
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_FRect board_dst;
    SDL_FRect sidebar_dst;
    MoveMode move_mode = NORMAL;
    ColorScheme linchess;
    ColorScheme chess_com;
    Brett game_board;
    MoveBtnTex move_btn_tex;
    bool redraw = true;
    bool btn_down = false;
    bool is_white_turn = true;
    bool win = false;
    TilePos selected_piece;
    std::vector<TilePos> moves;
    std::vector<TilePos> possible_moves;
};


/*
 * Initializes an SDL3 Window
 * @param appstate AppState struct to store information of the apps state in
 * @return SDL_APP_FAILURE to terminate with an error, SDL_APP_SUCCESS to
 *         terminate with success, SDL_APP_CONTINUE to continue.
 */
SDL_AppResult SDL_AppInit(void** appstate, int argc, char *argv[]) {
    // allocate memory for AppState struct
    if (!(*appstate = SDL_malloc(sizeof(AppState)))) {
        return SDL_APP_FAILURE;
    }
    auto* state = static_cast<AppState*>(*appstate);
    state -> title = "Quantum Chess";

    if (!SDL_Init(SDL_INIT_VIDEO))
        return SDL_APP_FAILURE;

    int width = 1000;
    int height = 800;

    state->linchess = {
        {181, 136, 99, 255},
        {240, 217, 181, 255}
    };
    state->chess_com = {
        {119, 149, 87, 255},
        {236, 236, 208, 255}
    };
    state->selected_piece = {
        255,
        255
    };
    state->is_white_turn = true;
    if (!(state->window = SDL_CreateWindow(state->title, width, height, SDL_WINDOW_RESIZABLE)))
        return SDL_APP_FAILURE;
    //TODO: set new aspect ratio
    //SDL_SetWindowAspectRatio(state -> window, 1.0f, 1.0f);

    if (!(state->renderer = SDL_CreateRenderer(state->window, NULL)))
        return SDL_APP_FAILURE;

    // enable use of alpha channel
    SDL_SetRenderDrawBlendMode(state->renderer, SDL_BLENDMODE_BLEND);

    state->game_board = GameLogic::InitGameBoard();
    Graphics::CreateChessTextures(state->renderer, state->game_board);
    Graphics::CreateMoveBtnTextures(state->renderer, state->move_btn_tex);

    std::cout << "Program loaded!" << std::endl;
    return SDL_APP_CONTINUE;
}


/*
 * Logic that needs to be done every frame
 * @param appstate AppState struct to store information of the apps state in
 * @return SDL_APP_FAILURE to terminate with an error, SDL_APP_SUCCESS to
 *         terminate with success, SDL_APP_CONTINUE to continue.
 */
SDL_AppResult SDL_AppIterate(void* appstate) {
    auto* state = static_cast<AppState*>(appstate);

    if (state->redraw) {
        state->redraw = false;

        // Calculate the size of the chessboard and side bar
        int window_width, window_height;
        SDL_GetWindowSize(state->window, &window_width, &window_height);

        float sidebar_width = window_width / 5;
        float available_width = window_width - sidebar_width;
        float board_size = SDL_min(available_width, window_height);

        state->board_dst = {
            0,
            (window_height - board_size) / 2,
            board_size,
            board_size
        };
        state->sidebar_dst = {
            available_width,
            0,
            sidebar_width,
            static_cast<float>(window_height)
        };

        // create textures to render the chess board and side bar to
        //todo: learn more about pixelformat
        SDL_Texture* board_texture = SDL_CreateTexture(
                state->renderer,
                SDL_PIXELFORMAT_RGBA8888,
                SDL_TEXTUREACCESS_TARGET,
                static_cast<int>(board_size), static_cast<int>(board_size)
            );
        SDL_Texture* sidebar_texture = SDL_CreateTexture(
                state->renderer,
                SDL_PIXELFORMAT_RGBA8888,
                SDL_TEXTUREACCESS_TARGET,
                static_cast<int>(sidebar_width), window_height
            );

        // Render to Chessboard texture
        SDL_SetRenderTarget(state->renderer, board_texture);
        SDL_SetRenderViewport(state->renderer, NULL); // Use the full texture size as the viewport
        SDL_SetRenderDrawColor(state->renderer, 0, 0, 0, 255);
        SDL_RenderClear(state->renderer);

        Graphics::DrawChessboard(state->renderer, state->linchess, state->possible_moves);
        Graphics::RenderChessTextures(state->renderer, state->game_board);


        // Render to sidebar texture
        SDL_SetRenderTarget(state->renderer, sidebar_texture);
        SDL_SetRenderViewport(state->renderer, NULL); // Use the full texture size as the viewport
        SDL_SetRenderDrawColor(state->renderer, 0, 0, 0, 255);
        SDL_RenderClear(state->renderer);

        // Create texture for sidebar
        Graphics::RenderSidebar(state->renderer, state->linchess, state->move_mode, state->move_btn_tex);

        // Render to the main window
        SDL_SetRenderTarget(state->renderer, NULL);
        SDL_SetRenderDrawColor(state->renderer, 0, 0, 0, 255);
        SDL_RenderClear(state->renderer);

        // Copy Texture 1 to the left side of the window
        SDL_RenderTexture(state->renderer, board_texture, NULL, &state->board_dst);
        SDL_RenderTexture(state->renderer, sidebar_texture, NULL, &state->sidebar_dst);

        // Present the final rendered image
        SDL_RenderPresent(state->renderer);

        // Destroy textures
        SDL_DestroyTexture(board_texture);
        SDL_DestroyTexture(sidebar_texture);
    }
    return SDL_APP_CONTINUE;
}


/*
 * Handles SDL events
 * @param appstate AppState struct to store information of the apps state in
 * @param event Pointer of the event to handle
 * @return SDL_APP_FAILURE to terminate with an error, SDL_APP_SUCCESS to
 *        terminate with success, SDL_APP_CONTINUE to continue.
 */
SDL_AppResult SDL_AppEvent(void* appstate, SDL_Event* event) {
    auto* state = static_cast<AppState*>(appstate);

    switch (event->type) {
        case SDL_EVENT_WINDOW_PIXEL_SIZE_CHANGED: {
            state->redraw = true;
            break;
        }
        case SDL_EVENT_MOUSE_BUTTON_DOWN:
            if (event->button.button == SDL_BUTTON_LEFT)
                state->btn_down = true;
            break;
        case SDL_EVENT_MOUSE_BUTTON_UP:
            if (event->button.button == SDL_BUTTON_LEFT && state->btn_down && !state->win) {
                // button pressed
                state->btn_down = false;
                state->redraw = true;
                if (PointInRect(&event->button.x, &event->button.y, &state->board_dst)) {
                    // Click in Chessboard
                    TilePos pos = GetTileFromMousePos(event->button.x, event->button.y, &state->board_dst);
                    switch (state->move_mode) {
                        case NORMAL:
                            GameLogic::HandleNormalChessMoveEvent(
                                pos,
                                state->selected_piece,
                                state->possible_moves,
                                state->game_board,
                                state->is_white_turn
                            );
                            break;
                        case SPLIT:
                            GameLogic::HandleSplitChessMoveEvent(
                                pos,
                                state->selected_piece,
                                state->moves,
                                state->possible_moves,
                                state->game_board,
                                state->is_white_turn
                            );
                            break;
                        case MERGE:
                            GameLogic::HandleMergeChessMoveEvent(
                                pos,
                                state->selected_piece,
                                state->moves,
                                state->possible_moves,
                                state->game_board,
                                state->is_white_turn
                            );
                            break;
                    }
                } else if (PointInRect(&event->button.x, &event->button.y, &state->sidebar_dst)) {
                    // Click in Sidebar
                    bool mode_changed = false;
                    if (event->button.y >= 0 && event->button.y < state->sidebar_dst.w) {
                        // normal move selected
                        mode_changed = state->move_mode != NORMAL;
                        state->move_mode = NORMAL;
                    } else if (event->button.y >= state->sidebar_dst.w && event->button.y < 2*state->sidebar_dst.w ) {
                        // split move selected
                        mode_changed = state->move_mode != SPLIT;
                        state->move_mode = SPLIT;
                    } else if ( event->button.y >= 2*state->sidebar_dst.w && event->button.y < 3*state->sidebar_dst.w ) {
                        // merge move selected
                        mode_changed = state->move_mode != MERGE;
                        state->move_mode = MERGE;
                    }
                    // reset moves when movement mode changes
                    if (mode_changed) {
                        state->selected_piece = {
                            255,
                            255
                        };
                        state->possible_moves.clear();
                        state->moves.clear();
                    }
                }
            }
            break;
        case SDL_EVENT_QUIT:
            return SDL_APP_SUCCESS;
        default:    // ignore all events not listed above
            break;
    }

    return SDL_APP_CONTINUE;
}


/*
 * Gets called when quitting SDL
 * @param appstate AppState struct to store information of the apps state in
 * @param result SDL_APP_FAILURE to terminate with an error, SDL_APP_SUCCESS to
 *              terminate with success, SDL_APP_CONTINUE to continue.
 */
void SDL_AppQuit(void* appstate, SDL_AppResult result) {
    //Cleanup here
    const auto* state = static_cast<AppState*>(appstate);
    SDL_DestroyRenderer(state->renderer);
    SDL_DestroyWindow(state->window);
    // Call deconstructor for game_board.Felder since the figures where created with new ...
    for (auto& row: state->game_board.Felder) {
        for (auto& col: row) {
            delete col;
        }
    }
    if (result == SDL_APP_FAILURE)
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error",
            SDL_GetError(), appstate ? state->window : NULL);
    SDL_free(appstate); // deallocate AppState
    SDL_Quit();
}
/**
 * @file SDL_Test.cpp
 * @brief A test implementation of the chessboard gui
 *
 * @author GrohJann
 * @date 05/12/2025
 */

#include <iostream>
#include <algorithm>
#include <SDL3_image/SDL_image.h>

#include "../GUI/SDL_Test.h"

enum mode {
    NORMAL,
    SPLIT,
    MERGE
};

struct QuantumChessSquare {
    // TODO: odd id
    Figuren* chessPice;
    // FIXME: remove if unnecessary
    //bool isWhite;
    float probability;
};

struct FigureTextures {
    SDL_Texture* rookTexture;
    SDL_Texture* knightTexture;
    SDL_Texture* bishopTexture;
    SDL_Texture* queenTexture;
    SDL_Texture* kingTexture;
    SDL_Texture* pawnTexture;
};

struct Pos {
    float x;
    float y;
};

struct AppState {
    const char* title;
    SDL_Window* window;
    SDL_Renderer* renderer;
    FigureTextures whiteFigures;
    FigureTextures blackFigures;
    Board board;
    mode moveMode = NORMAL;
    bool whiteTurn = true;
    bool btn_down = false;
    //bool clicked = false;
    Pos mousePos;
    vector<Pos> selectedTiles;
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

    // enable use of alpha channel
    SDL_SetRenderDrawBlendMode(state->renderer, SDL_BLENDMODE_BLEND);

    // save mouse pos to prevent null-pointer exception
    SDL_GetMouseState(&state->mousePos.x, &state->mousePos.y);

    // make figure Textures
    if (!CreateFigureTextures(state->renderer, &state->whiteFigures, &state->blackFigures))
        return SDL_APP_FAILURE;

    //InitChessBoard(*state->board);
    state->board = InitChessBoard();

    std::cout << "Program loaded!" << std::endl;
    return SDL_APP_CONTINUE;
}

/**
 * Initializes the Chessboard
 * @param board 2D Array of QuantumChess structs with type std::array<std::array<QuantumChessSquare*, 8>, 8>
 */
/*void InitChessBoard(Board& board) {
    for (int row = 0; row < board.size(); row++) {
        for (int col = 0; col < board.size(); col++) {
            if (row == 0 || row == 7) {
                if (col == 0 || col == 7) {
                    const bool isWhite = row>3;
                    auto f = Turm(isWhite, row, col);
                    auto square = QuantumChessSquare{&f, isWhite, 1.0f};
                    board[row][col] = &square;
                } else if (col == 1 || col == 6) {
                    const bool isWhite = row>3;
                    auto f = Springer(isWhite, row, col);
                    auto square = QuantumChessSquare{&f, isWhite, 1.0f};
                    board[row][col] = &square;
                } else if (col == 2 || col == 5) {
                    const bool isWhite = row>3;
                    auto f = Laeufer(isWhite, row, col);
                    auto square = QuantumChessSquare{&f, isWhite, 1.0f};
                    board[row][col] = &square;
                } else if (col == 3) {
                    const bool isWhite = row>3;
                    if (isWhite) {
                        auto f = Dame(isWhite, row, col);
                        auto square = QuantumChessSquare{&f, isWhite, 1.0f};
                        board[row][col] = &square;
                    } else {
                        auto f = Koenig(isWhite, row, col);
                        auto square = QuantumChessSquare{&f, isWhite, 1.0f};
                        board[row][col] = &square;
                    }
                } else if (col == 4) {
                    const bool isWhite = row>3;
                    if (isWhite) {
                        auto f = Koenig(isWhite, row, col);
                        auto square = QuantumChessSquare{&f, isWhite, 1.0f};
                        board[row][col] = &square;
                    } else {
                        auto f = Dame(isWhite, row, col);
                        auto square = QuantumChessSquare{&f, isWhite, 1.0f};
                        board[row][col] = &square;
                    }
                }
            } else if (row == 1 || row == 6) {
                const bool isWhite = row>3;
                auto f = Bauer(isWhite, row, col);
                auto square = QuantumChessSquare{&f, isWhite, 1.0f};
                board[row][col] = &square;
            } else {
                board[row][col] = nullptr;
                break;
            }
        }
    }
}*/
Board InitChessBoard() {
    Board board{};

    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            const bool isWhite = row > 3;
            auto* square = new QuantumChessSquare{};

            if (row == 0 || row == 7) {
                if (col == 0 || col == 7) {
                    square->chessPice = new Turm(isWhite, row, col);
                } else if (col == 1 || col == 6) {
                    square->chessPice = new Springer(isWhite, row, col);
                } else if (col == 2 || col == 5) {
                    square->chessPice = new Laeufer(isWhite, row, col);
                } else if (col == 3) {
                    if (isWhite)
                        square->chessPice = new Dame(isWhite, row, col);
                    else
                        square->chessPice = new Koenig(isWhite, row, col);
                } else if (col == 4) {
                    if (isWhite)
                        square->chessPice = new Koenig(isWhite, row, col);
                    else
                        square->chessPice = new Dame(isWhite, row, col);
                }
                // FIXME: remove if unnecessary
                //square->isWhite = isWhite;
                square->probability = 1.0f;
                board[row][col] = square;
            } else if (row == 1 || row == 6) {
                square->chessPice = new Bauer(isWhite, row, col);
                // FIXME: remove if unnecessary
                //square->isWhite = isWhite;
                square->probability = 1.0f;
                board[row][col] = square;
            } else {
                board[row][col] = nullptr;
            }
        }
    }

    return board;
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

/*********************** Handle Clicks *********************************/
            for (auto [x, y]: state->selectedTiles) {
                if (pointInRect(&x, &y, &rect)) {
                    SDL_SetRenderDrawColor(state->renderer, 230, 98, 253, 150);
                    success = success && SDL_RenderFillRect(state->renderer, &rect);
                    //state->clicked = false;
                }
            }
            /*if (state->clicked && pointInRect(&state->mousePos.x, &state->mousePos.y, &rect)) {
                SDL_SetRenderDrawColor(state->renderer, 230, 98, 253, 150);
                success = success && SDL_RenderFillRect(state->renderer, &rect);
                state->clicked = false;
            }*/
/************************************************************************/
            // TODO: move to seperate function and make variable
/*********************** Draw Chess Figures *********************************/
            if (state->board[row][col] != nullptr) {
                Figuren* piece = state->board[row][col]->chessPice;
                if (dynamic_cast<Turm*>(piece)) {
                    SDL_Texture* texture = piece->Get_Farbe() ?
                                state->whiteFigures.rookTexture :
                                state->blackFigures.rookTexture;
                    SDL_SetTextureAlphaMod(texture, static_cast<Uint8>(255.0f*state->board[row][col]->probability));
                    SDL_RenderTexture(state->renderer, texture, nullptr, &rect);
                } else if (dynamic_cast<Springer*>(piece)) {
                    SDL_Texture* texture = piece->Get_Farbe() ?
                                state->whiteFigures.knightTexture :
                                state->blackFigures.knightTexture;
                    SDL_SetTextureAlphaMod(texture, static_cast<Uint8>(255.0f*state->board[row][col]->probability));
                    SDL_RenderTexture(state->renderer, texture, nullptr, &rect);
                } else if (dynamic_cast<Laeufer*>(piece)) {
                    SDL_Texture* texture = piece->Get_Farbe() ?
                                state->whiteFigures.bishopTexture :
                                state->blackFigures.bishopTexture;
                    SDL_SetTextureAlphaMod(texture, static_cast<Uint8>(255.0f*state->board[row][col]->probability));
                    SDL_RenderTexture(state->renderer, texture, nullptr, &rect);
                } else if (dynamic_cast<Dame*>(piece)) {
                    SDL_Texture* texture = piece->Get_Farbe() ?
                                state->whiteFigures.queenTexture :
                                state->blackFigures.queenTexture;
                    SDL_SetTextureAlphaMod(texture, static_cast<Uint8>(255.0f*state->board[row][col]->probability));
                    SDL_RenderTexture(state->renderer, texture, nullptr, &rect);
                } else if (dynamic_cast<Koenig*>(piece)) {
                    SDL_Texture* texture = piece->Get_Farbe() ?
                                state->whiteFigures.kingTexture :
                                state->blackFigures.kingTexture;
                    SDL_SetTextureAlphaMod(texture, static_cast<Uint8>(255.0f*state->board[row][col]->probability));
                    SDL_RenderTexture(state->renderer, texture, nullptr, &rect);
                } else if (dynamic_cast<Bauer*>(piece)) {
                    SDL_Texture* texture = piece->Get_Farbe() ?
                                state->whiteFigures.pawnTexture :
                                state->blackFigures.pawnTexture;
                    SDL_SetTextureAlphaMod(texture, static_cast<Uint8>(255.0f*state->board[row][col]->probability));
                    SDL_RenderTexture(state->renderer, texture, nullptr, &rect);
                }
            }
/****************************************************************************/

            if (!success) {
                return false;
            }
        }
    }

    return true;
}

/**
 * Checks whether the given point is located inside the area of an SDL_FRect
 * @param x x coordinate of the point
 * @param y y coordinate of the point
 * @param rect SDL_FRect to check against
 * @return true when the given point is inside the SDL_FRect, otherwise false
 */
bool pointInRect(const float* x, const float* y, const SDL_FRect* rect) {
    return *x >= rect->x &&
           *x <= rect->x + rect->w &&
           *y >= rect->y &&
           *y <= rect->y + rect->h;
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
        case SDL_EVENT_MOUSE_BUTTON_DOWN:
            if (event->button.button == SDL_BUTTON_LEFT)
                state->btn_down = true;
            break;
        case SDL_EVENT_MOUSE_BUTTON_UP:
            if (event->button.button == SDL_BUTTON_LEFT && state->btn_down) {
                // button pressed
                state->btn_down = false;
                SDL_GetMouseState(&state->mousePos.x, &state->mousePos.y);
                state->redraw = true;
                //state->clicked = true;
                switch (state->moveMode) {
                    case NORMAL:
                        if (state->selectedTiles.size() >= 1) {
                            state->selectedTiles.push_back(state->mousePos);
                            // TODO: check if valid move and move
                            handleNormalChessMove(state);
                        } else {
                            state->selectedTiles.clear();
                            state->selectedTiles.push_back(state->mousePos);
                        }
                        break;
                    case SPLIT:
                        // TODO: add quantum split move
                        if (state->selectedTiles.size() >= 2) {
                            state->selectedTiles.push_back(state->mousePos);
                            // TODO: check if valid move and move
                        } else {
                            state->selectedTiles.clear();
                            state->selectedTiles.push_back(state->mousePos);
                        }
                        break;
                    case MERGE:
                        // TODO: add quantum merge move
                        if (state->selectedTiles.size() >= 2) {
                            state->selectedTiles.push_back(state->mousePos);
                            // TODO: check if valid move and move
                        } else {
                            state->selectedTiles.clear();
                            state->selectedTiles.push_back(state->mousePos);
                        }
                        break;
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

// TODO: check player turn
void handleNormalChessMove(AppState* state) {
    int w, h;
    constexpr int boardFields = 8;
    SDL_GetWindowSize(state -> window, &w, &h);
    Pos startPos = state->selectedTiles.front();
    Pos endPos = state->selectedTiles.back();
    int startRow, startCol, endRow, endCol;
    Figuren* chessPiece = nullptr;
    const float squareSize = (w * 1.0f) / (boardFields * 1.0f);

    // todo: rewrite without for loops
    for (int row = 0; row < boardFields; row++) {
        for (int col = 0; col < boardFields; col++) {
            if (state->board[row][col] != nullptr  &&
                startPos.x >= col * squareSize &&
                startPos.x <= col * squareSize + squareSize &&
                startPos.y >= row * squareSize &&
                startPos.y <= row * squareSize + squareSize ) {
                    chessPiece = state->board[row][col]->chessPice;
                    startRow = row;
                    startCol = col;
                    //break;
                }
            if (endPos.x >= col * squareSize &&
                endPos.x <= col * squareSize + squareSize &&
                endPos.y >= row * squareSize &&
                endPos.y <= row * squareSize + squareSize ) {
                    endRow = row;
                    endCol = col;
                }
        }
        //if (chessPiece != nullptr) break;
    }

    // TODO: check if endRow and endCol are initialized
    if (chessPiece != nullptr) {
        if (dynamic_cast<Turm*>(chessPiece)) {
             // TODO: implement rook
        } else if (dynamic_cast<Springer*>(chessPiece)) {
            // TODO: implement knight
        } else if (dynamic_cast<Laeufer*>(chessPiece)) {
            // TODO: implement bishop
        } else if (dynamic_cast<Koenig*>(chessPiece)) {
            // TODO: implement king
        } else if (dynamic_cast<Dame*>(chessPiece)) {
            // TODO: implement queen
        } else if (dynamic_cast<Bauer*>(chessPiece)) {
            chessPiece->Set_Moegliche_Felder();
            std::vector<std::array<int, 2>> possibleMoves = chessPiece->Get_Moegliche_Felder();
            auto iterator = std::find(possibleMoves.begin(), possibleMoves.end(), std::array<int, 2>{endCol, endRow});
            if (iterator != possibleMoves.end()) {
                state->board[endRow][endCol] = state->board[startRow][startCol];
                state->board[endRow][endCol]->chessPice->Set_Zeile(endRow);
                state->board[endRow][endCol]->chessPice->Set_Spalte(endCol);
                state->board[startRow][startCol] = nullptr;
            }
        }
    }

    // delete all selections after you are done
    state->selectedTiles.clear();
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
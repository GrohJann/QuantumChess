/**
 * @file SDL_Test.cpp
 * @brief A test implementation of the chessboard gui
 *
 * @author GrohJann
 * @date 05/12/2025
 */
#include "Brett.h"
#include <iostream>
#include <SDL3/SDL.h>
#include "../Spiel_Logik/SDL_Test.h"
#include <string>
#include <vector>


using namespace std;

struct AppState {
    const char* title;
    SDL_Window* window;
    SDL_Renderer* renderer;
    bool redraw = true;
};

struct figures {
    string name;
    const char* path;
    SDL_Texture* texture;
};

/**
 * Initializes an SDL3 Window
 * @param appstate AppState struct to store information of the apps state in
 * @return SDL_APP_FAILURE to terminate with an error, SDL_APP_SUCCESS to
 *         terminate with success, SDL_APP_CONTINUE to continue.
 */
SDL_AppResult SDL_AppInit(void** appstate) {
    // allocate memory for AppState struct
    if (!(*appstate = SDL_malloc(sizeof(AppState)))) {     //SDL_malloc gibt Zeiger auf reservierten Speicherbreich zur�ck
        return SDL_APP_FAILURE;                        //Wenn SDL_malloc nullpointer zur�ckgibt
    }
    auto* state = static_cast<AppState*>(*appstate);   //lokaler Zeiger , static_cast, da malloc void* zur�ckgibt
    state->title = "Quantum Chess";

    if (!SDL_Init(SDL_INIT_VIDEO))
        return SDL_APP_FAILURE;

    int width = 800;
    int height = 800;
    if (!(state->window = SDL_CreateWindow(state->title, width, height, SDL_WINDOW_RESIZABLE)))
        return SDL_APP_FAILURE;
    SDL_SetWindowAspectRatio(state->window, 1.0f, 1.0f);

    if (!(state->renderer = SDL_CreateRenderer(state->window, NULL)))
        return SDL_APP_FAILURE;

    std::cout << "Program loaded!" << std::endl;
    return SDL_APP_CONTINUE;
}

/**
 * Logic that needs to be done every frame
 * @param appstate AppState struct to store information of the apps state in
 * @return SDL_APP_FAILURE to terminate with an error, SDL_APP_SUCCESS to
 *         terminate with success, SDL_APP_CONTINUE to continue.
 */
SDL_AppResult AppIterate(void* appstate, Brett& Spielfeld) {
    auto* state = static_cast<AppState*>(appstate);

    if (state->redraw) {
        state->redraw = false;
        // TODO: redraw Frame
        // clear frame buffer
        SDL_SetRenderDrawColor(state->renderer, 0, 0, 0, 255);
        SDL_RenderClear(state->renderer);

        // draw chessboard
        drawChessboard(state->window, state->renderer);
        RenderChessTextures(state->window, state->renderer, Spielfeld);

        // swap frame buffer
        SDL_RenderPresent(state->renderer);
    }

    return SDL_APP_CONTINUE;
}

// TODO: add javadoc
int drawChessboard(SDL_Window* window, SDL_Renderer* renderer) {
    int w, h;
    constexpr int boardFields = 8;
    SDL_GetWindowSize(window, &w, &h);

    // get size of squares
    const float squareSize = (w * 1.0f) / (boardFields * 1.0f);    //*1.f -> float/float und nicht mehr int/int

    // render Background
    SDL_RenderClear(renderer);

    // render squares
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {

            // Alternate colors
            if ((row + col) % 2 == 0) {
               // SDL_SetRenderDrawColor(renderer, 240, 240, 240, 255);
                SDL_SetRenderDrawColor(renderer, 240, 217, 181, 255);      //Farbe linchess
            }
            else {
                //SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
                SDL_SetRenderDrawColor(renderer, 181, 136, 99, 255);       //Farbe linchess
            }
            SDL_FRect rect = { col * squareSize, row * squareSize, squareSize, squareSize };

            SDL_RenderFillRect(renderer, &rect);
            
        }
    }

    return 0;
}

void RenderChessTextures(SDL_Window* window, SDL_Renderer* renderer, Brett& Spielfeld) {
    int w, h;
    constexpr int boardFields = 8;
    SDL_GetWindowSize(window, &w, &h);
    const float squareSize = (w * 1.0f) / (boardFields * 1.0f);
    int row;
    int col;

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (Spielfeld.Felder[i][j] == NULL) continue;
            else {
                row = Spielfeld.Felder[i][j]->Get_Zeile();
                col = Spielfeld.Felder[i][j]->Get_Spalte();
                row = 8 - row;
                col = col - 1;
                SDL_FRect rect = { col * squareSize, row * squareSize, squareSize, squareSize };
                SDL_RenderTexture(renderer, Spielfeld.Felder[i][j]->Get_Texture(), NULL, &rect);
            }
        }
    }
}

void createTexture(void* appstate, Brett& Spielfeld) {
    const auto* state = static_cast<AppState*>(appstate);

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (Spielfeld.Felder[i][j] == NULL) continue;
            else {
                string path = Spielfeld.Felder[i][j]->Get_Dateipfad();
                const char* c_path = path.c_str();
                SDL_Surface* surface = SDL_LoadPNG(c_path);
                if (!surface) {
                    cout << "Fehler beim Laden von :" << Spielfeld.Felder[i][j]->Get_Name()
                        << " Position: "<< i << " " << j << SDL_GetError() << endl;
                }

                // Textur erstellen
                SDL_Texture* texture = SDL_CreateTextureFromSurface(state->renderer, surface);
                Spielfeld.Felder[i][j]->Set_Texture(texture);
                SDL_DestroySurface(surface);
            }
        }
    }
}


void calculateFieldFromCoordinates(void* appstate, const float& mouseX, const float& mouseY, int* selectedRow,int* selectedCol) {
    const auto* state = static_cast<AppState*>(appstate);
    int w, h;
    SDL_GetWindowSize(state->window, &w, &h);
    constexpr int boardFields = 8;

    float squareSize = w / static_cast<float>(boardFields);     //da Feld quadratisch egal ob Breite oder H�he
    *selectedRow = 8 - (static_cast<int>(mouseY / squareSize));
    *selectedCol = (static_cast<int>(mouseX / squareSize))+1;
 
}


/**
 * Handles SDL events
 * @param appstate AppState struct to store information of the apps state in
 * @param event Pointer of the event to handle
 * @param mouseX
 * @param mouseY
* @return SDL_APP_FAILURE to terminate with an error, SDL_APP_SUCCESS to
 *        terminate with success, SDL_APP_CONTINUE to continue.
 */
SDL_AppResult AppEvent(void* appstate, SDL_Event* event, float* mouseX, float* mouseY) {
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
    case SDL_EVENT_MOUSE_BUTTON_DOWN: {
        if (event->button.button == SDL_BUTTON_LEFT) {
            *mouseX = event->button.x;          //X Werte von der Maus
            *mouseY = event->button.y;          //Y Werte von der Maus
        }
    }
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
void AppQuit(void* appstate, SDL_AppResult result) {
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
int run(Brett& Spielfeld) {
    // init SDL
    void* appstate = nullptr;
    SDL_AppResult result = SDL_AppInit(&appstate);
    if (result == SDL_APP_CONTINUE) {

        createTexture(appstate,Spielfeld);                //Datenpfad in Textur

        // main loop
        //bool running = true;
        SDL_Event event;

        float mouseX;
        float mouseY;
        int selectedRow = 0;
        int selectedCol = 0;
        int a = selectedRow;     //nur�zum testen
        int b = selectedCol;

        while (true) {
            // handle events
            while (SDL_PollEvent(&event)) {    //Holt Event und speichert in event (0 = Kein Event in Warteschlange)
                result = AppEvent(appstate, &event, &mouseX,&mouseY);    // Events (auch Mausklick)
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
            calculateFieldFromCoordinates(appstate, mouseX, mouseY, &selectedRow, &selectedCol);
            // logic
            AppIterate(appstate, Spielfeld);

            if (a != selectedRow || b != selectedCol) {                 //Um calculateFieldFromCoordinates zu testen
                cout << "Ausgewaehlte Reihe: " << selectedRow << endl;
                cout << "Ausgewaehlte Spalte: " << selectedCol << endl;
                a = selectedRow;    
                b = selectedCol;
            }
        }
    }

    // Deconstruct
    AppQuit(appstate, result);
    return 0;
}
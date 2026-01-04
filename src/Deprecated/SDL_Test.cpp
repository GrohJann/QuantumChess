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
#include "SDL_Test.h"
#include "Spiel_Logik.h"
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
SDL_AppResult AppInit(void** appstate) {
    // allocate memory for AppState struct
    if (!(*appstate = SDL_malloc(sizeof(AppState)))) {     //SDL_malloc gibt Zeiger auf reservierten Speicherbreich zurück
        return SDL_APP_FAILURE;                        //Wenn SDL_malloc nullpointer zurückgibt
    }
    auto* state = static_cast<AppState*>(*appstate);   //lokaler Zeiger , static_cast, da malloc void* zurückgibt
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
SDL_AppResult AppIterate(void* appstate, Brett& Spielfeld, vector <Moegliches_Feld> Vector_Moegliche_felder) {
    auto* state = static_cast<AppState*>(appstate);

    if (state->redraw) {
        state->redraw = false;
        // TODO: redraw Frame
        // clear frame buffer
        SDL_SetRenderDrawColor(state->renderer, 0, 0, 0, 255);
        SDL_RenderClear(state->renderer);

        // draw chessboard
        drawChessboard(state->window, state->renderer);
        // Render textures/ figures
        RenderTextures(state->window, state->renderer, Spielfeld, Vector_Moegliche_felder);

        // swap frame buffer
        SDL_RenderPresent(state->renderer);

        //determine the possible fields to which a piece could be moved
      //   setPossibleFields(Spielfeld);
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

void RenderTextures(SDL_Window* window, SDL_Renderer* renderer, Brett& Spielfeld, vector <Moegliches_Feld> Vector_Moegliche_felder) {
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
    for (int i = 0; i < Vector_Moegliche_felder.size(); i++) {
        col = Vector_Moegliche_felder[i].spalte - 1;
        row = 8 - Vector_Moegliche_felder[i].zeile;
        //cout <<"Spalte: "<<  col << "  Zeile:" << row << endl;    Nur zum Testen
        SDL_FRect rect = { col * squareSize, row * squareSize, squareSize, squareSize };
        SDL_SetRenderDrawColor(renderer, 57, 255, 20, 255);
        SDL_RenderFillRect(renderer, &rect);
    }
}

void setPossibleFields(Brett& Spielfeld) {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (Spielfeld.Felder[i][j] == NULL) continue;
            Spielfeld.Felder[i][j]->Set_Moegliche_Felder(Spielfeld);
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
                        << " Position: " << i << " " << j << SDL_GetError() << endl;
                }

                // Textur erstellen
                SDL_Texture* texture = SDL_CreateTextureFromSurface(state->renderer, surface);
                Spielfeld.Felder[i][j]->Set_Texture(texture);
                SDL_DestroySurface(surface);
            }
        }
    }


    // set texture
}



/*
void loadTextureWithSDL3(vector<figures>& InfoFigures, void* appstate) {
    const auto* state = static_cast<AppState*>(appstate);

    for (int i = 0; i < InfoFigures.size(); i++) {

        SDL_Surface* surface = SDL_LoadPNG(InfoFigures[i].path);
        if (!surface) {
            cout << "Fehler beim Laden von Figur:" << InfoFigures[i].name << SDL_GetError() << endl;
        }

        // Textur erstellen
        InfoFigures[i].texture = SDL_CreateTextureFromSurface(state->renderer, surface);
        SDL_DestroySurface(surface);
    }


}

*/
void calculateFieldFromCoordinates(void* appstate, const float& mouseX, const float& mouseY, int* selectedRow, int* selectedCol) {
    const auto* state = static_cast<AppState*>(appstate);
    int w, h;
    SDL_GetWindowSize(state->window, &w, &h);
    constexpr int boardFields = 8;
      
    float squareSize = w / static_cast<float>(boardFields);     //da Feld quadratisch egal ob Breite oder Höhe
    *selectedRow = 8 - (static_cast<int>(mouseY / squareSize));
    *selectedCol = (static_cast<int>(mouseX / squareSize)) + 1;

}


/**
 * Handles SDL events
 * @param appstate AppState struct to store information of the apps state in
 * @param event Pointer of the event to handle
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
            state->redraw = true;
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
int main() {
    // init SDL
    void* appstate = nullptr;
    SDL_AppResult result = AppInit(&appstate);







    if (result == SDL_APP_CONTINUE) {


        Brett Spielfeld;

        vector <Bauer> bauern;
        vector <Springer> springer;
        vector <Laeufer> laeufer;
        vector <Turm> tuerme;
        vector <Dame> damen;
        vector <Koenig> koenige;

        Spielfeld_Reset(Spielfeld);
        Startaufstellung_Bauern(bauern, Spielfeld);
        Startaufstellung_Springer(springer, Spielfeld);
        Startaufstellung_Laeufer(laeufer, Spielfeld);
        Startaufstellung_Tuerme(tuerme, Spielfeld);
        Startaufstellung_Damen(damen, Spielfeld);
        Startaufstellung_Koenige(koenige, Spielfeld);




        createTexture(appstate, Spielfeld);                //Datenpfad in Textur

        // main loop
        //bool running = true;
        SDL_Event event;

        float mouseX = 0;  //mouseclick x coordinates
        float mouseY = 0;  //mouseclick y coordinates
        int selectedRow = 0;    //current selectedRow
        int selectedCol = 0;    //current selectedCol
        int a = selectedRow;   //selectedRow the click before
        int b = selectedCol;   //selectedCol the click before
        vector <Moegliches_Feld> Vector_Moegliche_felder;

        bool piece_moved = false;
        
        
        while (true) {
            // handle events
            while (SDL_PollEvent(&event)) {    //Holt Event und speichert in event (0 = Kein Event in Warteschlange)
                result = AppEvent(appstate, &event, &mouseX, &mouseY);    // Events (auch Mausklick)
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

            // calculate on wich field the mouseclick was
            calculateFieldFromCoordinates(appstate, mouseX, mouseY, &selectedRow, &selectedCol);
            
            
            
            // If left mouse click on different field: 
            if (a != selectedRow || b != selectedCol && !Spielfeld.schachmatt) {
                Erstes_Feld(selectedCol, selectedRow, Spielfeld);

                if (Ceck_For_Promotion(Spielfeld, damen)) {
                    createTexture(appstate, Spielfeld);
                }

                cout << "Ausgewaehlte Reihe: " << selectedRow << endl;
                cout << "Ausgewaehlte Spalte: " << selectedCol << endl;
                
                a = selectedRow;
                b = selectedCol;
                
                if (Spielfeld.Felder[selectedCol - 1][selectedRow - 1] != nullptr && Spielfeld.piece_selected ) {
                    Spielfeld.Felder[selectedCol - 1][selectedRow - 1]->Set_Moegliche_Felder(Spielfeld);
                    Vector_Moegliche_felder = Spielfeld.Felder[selectedCol - 1][selectedRow - 1]->Get_Moegliche_Felder();
                }
                else {
                    Vector_Moegliche_felder.clear();
                }
            }
            if (Spielfeld.piece_selected) {
                AppIterate(appstate, Spielfeld, Vector_Moegliche_felder);
            }
            else {
                AppIterate(appstate, Spielfeld, {});
            }
            

        }
    }

    // Deconstruct
    AppQuit(appstate, result);
    return 0;
}

/*
#include <SDL3/SDL.h>
#include <vector>
#include <iostream>

using namespace std;
int main() {
    // 1. SDL korrekt initialisieren
    if (!SDL_Init(SDL_INIT_VIDEO)) {            //SDL_INIT_VIDEO initialisiert den Grafikteil von SDL
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
    }


    // 2. Fenster erstellen
    SDL_Window* window = SDL_CreateWindow("Test", 800, 600, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, nullptr);

    // 3. BMP OHNE .bmp laden (weil Ihre Datei so heiﬂt!)
    SDL_Surface* surface = SDL_LoadBMP("chessboard.bmp");  // KEIN .bmp!
    

    if (!surface) {
        std::cout << "Lade-Fehler: " << SDL_GetError() << std::endl;
        std::cout << "Datei 'chessboard' muss im selben Ordner liegen!" << std::endl;
    }
    else {
        std::cout << "BMP erfolgreich geladen!" << std::endl;
        SDL_DestroySurface(surface);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
*/
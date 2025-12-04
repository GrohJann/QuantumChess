#include <SDL3/SDL.h>
#include <vector>
#include <iostream>

using namespace std;

int main() {
    if (!SDL_Init(SDL_INIT_VIDEO)) {            //SDL_INIT_VIDEO initialisiert den Grafikteil von SDL
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
    }

    //Hier kann man die Groeße des Fensters einstellen
    int width = 1200;
    int height = 1000;
    SDL_Window* window = SDL_CreateWindow("Karte", width, height, SDL_WINDOW_RESIZABLE); ///Fenster wird erzeugt (Größe veränderbar)
    if (!window) {
        SDL_Log("Fehler beim Fenster erstellen: %s", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, nullptr); //Renderer bzw. Grafikausgabe erzeugen
    if (!renderer) {
        SDL_Log("Fehler beim Renderer erstellen: %s", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
}
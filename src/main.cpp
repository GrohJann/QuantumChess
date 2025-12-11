#include <iostream>

#include "GUI/SDL.h"
#include "GUI/SDL_Test.h"
#include "Network/Client_Network.h"
#include "Spiel_Logik/Quanten_Schach.h"


int main(int argc, char* argv[]) {
    if (argc > 1) {
        std::string arg = argv[1];

        if (arg == "gui") {
            std::cout << "Running in GUI mode" << std::endl;
            return runSDL();
        } else if (arg == "gui_test") {
            std::cout << "GUI Test mode" << std::endl;
            return run();
        } else if (arg == "network") {
            std::cout << "Running in Network mode" << std::endl;
            return startClient();
        } else if (arg == "logic") {
            std::cout << "Running in Logic mode" << std::endl;
            //return logik_main();
        } else {
            std::cout << "Unknown mode" << std::endl;
        }
    }

    return 0;
}
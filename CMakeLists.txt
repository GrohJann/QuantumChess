cmake_minimum_required(VERSION 3.29)

# --- Fetch SDL3 ---------------------------------------------------------------
include(FetchContent)

set(FETCHCONTENT_UPDATES_DISCONNECTED TRUE)
FetchContent_Declare(SDL3
        GIT_REPOSITORY https://github.com/libsdl-org/SDL
        GIT_TAG release-3.2.16
)

FetchContent_GetProperties(SDL3)
if(NOT SDL3_POPULATED)
    FetchContent_MakeAvailable(SDL3)
endif()

# ------------------------------------------------------------------------------

# --- Fetch SDL3_image ---------------------------------------------------------
# Enable common image formats
set(SDL3IMAGE_PNG  ON)
#set(SDL3IMAGE_JPG  ON)
FetchContent_Declare(SDL3_image
        GIT_REPOSITORY https://github.com/libsdl-org/SDL_image
        GIT_TAG release-3.2.4
)

FetchContent_GetProperties(SDL3_image)
if(NOT SDL3_image_POPULATED)
    FetchContent_MakeAvailable(SDL3_image)
endif()

# ------------------------------------------------------------------------------



project(QuantumChess)

set(CMAKE_CXX_STANDARD 20)

add_executable(QuantumChess src/main.cpp
        src/GUI/SDL.cpp
        src/GUI/SDL_Test.cpp
        src/GUI/SDL_Test.h
        src/Network/Client_Network.cpp
        src/Network/Client_Network.h
        src/GUI/SDL.h
        #src/Spiel_Logik/Bauer.cpp
        #src/Spiel_Logik/Bauer.h
        #src/Spiel_Logik/Dame.cpp
        #src/Spiel_Logik/Dame.h
        src/Spiel_Logik/Figuren.cpp
        src/Spiel_Logik/Figuren.h
        #src/Spiel_Logik/Koenig.cpp
        #src/Spiel_Logik/Koenig.h
        #src/Spiel_Logik/Laeufer.cpp
        #src/Spiel_Logik/Laeufer.h
        #src/Spiel_Logik/Quanten_Schach.cpp
        #src/Spiel_Logik/Quanten_Schach.h
        #src/Spiel_Logik/Springer.cpp
        #src/Spiel_Logik/Springer.h
        #src/Spiel_Logik/Turm.cpp
        #src/Spiel_Logik/Turm.h
)


target_link_libraries(QuantumChess
        PRIVATE
            SDL3::SDL3
            SDL3_image::SDL3_image
)
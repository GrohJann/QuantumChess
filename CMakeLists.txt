cmake_minimum_required(VERSION 4.0)

# --- Fetch SDL3 ---------------------------------------------------------------
include(FetchContent)

set(FETCHCONTENT_UPDATES_DISCONNECTED TRUE)
FetchContent_Declare(SDL3
        GIT_REPOSITORY https://github.com/libsdl-org/SDL
        GIT_TAG release-3.2.26
)

FetchContent_GetProperties(SDL3)
if(NOT SDL3_POPULATED)
    FetchContent_MakeAvailable(SDL3)
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
)


target_link_libraries(QuantumChess PRIVATE SDL3::SDL3)
cmake_minimum_required(VERSION 3.26)

project(QuantumChess)


# --- Fetch SDL3 ---------------------------------------------------------------
include(FetchContent)

set(FETCHCONTENT_UPDATES_DISCONNECTED TRUE)
FetchContent_Declare(SDL3
        GIT_REPOSITORY https://github.com/libsdl-org/SDL
        GIT_TAG release-3.4.0
)

FetchContent_GetProperties(SDL3)
if(NOT SDL3_POPULATED)
    FetchContent_MakeAvailable(SDL3)
endif()

# ------------------------------------------------------------------------------



set(CMAKE_CXX_STANDARD 20)

add_executable(QuantumChess src/main.cpp #src/main_tmp.cpp
        #src/GUI/SDL_Test.cpp
        #src/GUI/SDL_Test.h
        src/Network/Client_Network.cpp
        src/Network/Client_Network.h
        src/Model/Bauer.cpp
        src/Model/Bauer.h
        src/Model/Dame.cpp
        src/Model/Dame.h
        src/Model/Figuren.cpp
        src/Model/Figuren.h
        src/Model/Koenig.cpp
        src/Model/Koenig.h
        src/Model/Laeufer.cpp
        src/Model/Laeufer.h
        #src/Spiel_Logik/Quanten_Schach.cpp
        #src/Spiel_Logik/Quanten_Schach.h
        src/Model/Springer.cpp
        src/Model/Springer.h
        src/Model/Turm.cpp
        src/Model/Turm.h
        src/GUI/SDL_Helper.cpp
        src/GUI/SDL_Helper.h
        src/GUI/ChesssBoardView.cpp
        src/GUI/ChesssBoardView.h
        src/Model/Structs.h
        src/Logic/GameLogic.cpp
        src/Logic/GameLogic.h
        #src/Spiel_Logik/SDL_Test.cpp
        #src/Spiel_Logik/SDL_Test.h
)

add_custom_command(
        TARGET QuantumChess POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets
        $<TARGET_FILE_DIR:QuantumChess>/assets
)

if (WIN32)
    add_custom_command(TARGET QuantumChess POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_FILE:SDL3::SDL3>
            $<TARGET_FILE:SDL3_image::SDL3_image>
            $<TARGET_FILE_DIR:QuantumChess>
    )
endif()


target_link_libraries(QuantumChess
        PRIVATE
        SDL3::SDL3
)
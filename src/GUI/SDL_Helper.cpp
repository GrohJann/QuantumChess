/**
 * @file SDL_Helper.cpp
 * @brief A set of Functions usefull when using SDL
 *
 * @author GrohJann
 * @date 05/12/2025
 */

#include "SDL_Helper.h"

/**
 * Checks whether the given point is located inside the area of an SDL_FRect
 * @param x x coordinate of the point
 * @param y y coordinate of the point
 * @param rect SDL_FRect to check against
 * @return true when the given point is inside the SDL_FRect, otherwise false
 */
bool PointInRect(const float* x, const float* y, const SDL_FRect* rect) {
    return *x >= rect->x &&
           *x <= rect->x + rect->w &&
           *y >= rect->y &&
           *y <= rect->y + rect->h;
}

/**
 * Calculates the position on the chess that (mouseX, mouseY) is inside of
 * @param mouseX x position
 * @param mouseY y position
 * @param board SDL_FRect that is the size of the chess board
 * @return struct containing the location
 */
TilePos GetTileFromMousePos(const float& mouseX, const float& mouseY, const SDL_FRect* board) {
    float local_x = mouseX - board->x;
    float local_y = mouseY - board->y;
    float square_length = board->w / 8.0f;

    return {
        static_cast<Uint8>(local_y / square_length),
        static_cast<Uint8>(local_x / square_length)
    };
}
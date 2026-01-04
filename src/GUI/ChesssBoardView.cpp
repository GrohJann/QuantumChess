
#include <SDL3/SDL.h>

#include "ChesssBoardView.h"

#include <iostream>


void Graphics::CreateChessTextures(SDL_Renderer* renderer, Brett &Spielfeld) {
    SDL_Texture* wPawnTex = GetTextureFromImage(renderer, "../assets/chess_pieces/pawn_w.png");
    SDL_Texture* bPawnTex = GetTextureFromImage(renderer, "../assets/chess_pieces/pawn_b.png");
    SDL_Texture* wRookTex = GetTextureFromImage(renderer, "../assets/chess_pieces/rook_w.png");
    SDL_Texture* bRookTex = GetTextureFromImage(renderer, "../assets/chess_pieces/rook_b.png");
    SDL_Texture* wKnightTex = GetTextureFromImage(renderer, "../assets/chess_pieces/knight_w.png");
    SDL_Texture* bKnightTex = GetTextureFromImage(renderer, "../assets/chess_pieces/knight_b.png");
    SDL_Texture* wBishopTex = GetTextureFromImage(renderer, "../assets/chess_pieces/bishop_w.png");
    SDL_Texture* bBishopTex = GetTextureFromImage(renderer, "../assets/chess_pieces/bishop_b.png");
    SDL_Texture* wKingTex = GetTextureFromImage(renderer, "../assets/chess_pieces/king_w.png");
    SDL_Texture* bKingTex = GetTextureFromImage(renderer, "../assets/chess_pieces/king_b.png");
    SDL_Texture* wQueenTex = GetTextureFromImage(renderer, "../assets/chess_pieces/queen_w.png");
    SDL_Texture* bQueenTex = GetTextureFromImage(renderer, "../assets/chess_pieces/queen_b.png");


    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (Spielfeld.Felder[i][j] == NULL) continue;
            else {
                switch (Spielfeld.Felder[i][j]->Get_Name()) {
                    case 'R':
                        if (Spielfeld.Felder[i][j]->Get_Farbe()) // white
                            Spielfeld.Felder[i][j]->Set_Texture(wRookTex);
                        else
                            Spielfeld.Felder[i][j]->Set_Texture(bRookTex);
                        break;
                    case 'k':
                        if (Spielfeld.Felder[i][j]->Get_Farbe()) // white
                            Spielfeld.Felder[i][j]->Set_Texture(wKnightTex);
                        else
                            Spielfeld.Felder[i][j]->Set_Texture(bKnightTex);
                        break;
                    case 'B':
                        if (Spielfeld.Felder[i][j]->Get_Farbe()) // white
                            Spielfeld.Felder[i][j]->Set_Texture(wBishopTex);
                        else
                            Spielfeld.Felder[i][j]->Set_Texture(bBishopTex);
                        break;
                    case 'Q':
                        if (Spielfeld.Felder[i][j]->Get_Farbe()) // white
                            Spielfeld.Felder[i][j]->Set_Texture(wQueenTex);
                        else
                            Spielfeld.Felder[i][j]->Set_Texture(bQueenTex);
                        break;
                    case 'K':
                        if (Spielfeld.Felder[i][j]->Get_Farbe()) // white
                            Spielfeld.Felder[i][j]->Set_Texture(wKingTex);
                        else
                            Spielfeld.Felder[i][j]->Set_Texture(bKingTex);
                        break;
                    case 'P':
                        if (Spielfeld.Felder[i][j]->Get_Farbe()) // white
                            Spielfeld.Felder[i][j]->Set_Texture(wPawnTex);
                        else
                            Spielfeld.Felder[i][j]->Set_Texture(bPawnTex);
                        break;

                    default:
                        std::cout << "ERROR::ChesssBoardView::MoveChessPieceNormal()" << std::endl
                        <<"Figur auf i:" << i << ", j:" << j << "hatt keinen erkannten namen: "
                        << Spielfeld.Felder[i][j]->Get_Name() << std::endl;
                        break;
                }
            }
        }
    }
}

void Graphics::CreateMoveBtnTextures(SDL_Renderer *renderer, MoveBtnTex &move_btn_tex) {
    move_btn_tex.normal = GetTextureFromImage(renderer, "../assets/move_type/arrow.png");
    move_btn_tex.split = GetTextureFromImage(renderer, "../assets/move_type/split.png");
    move_btn_tex.merge = GetTextureFromImage(renderer, "../assets/move_type/merge.png");
}

SDL_Texture* Graphics::GetTextureFromImage(SDL_Renderer* renderer, const char* img_location) {
    SDL_Surface* surface = SDL_LoadPNG(img_location);
    if (!surface) {
        SDL_Log("PNG load failed: %s", SDL_GetError());
    }
    return SDL_CreateTextureFromSurface(renderer, surface);
}

// TODO: add javadoc
void Graphics::DrawChessboard(SDL_Renderer* renderer, ColorScheme color_scheme) {
    int w, h;
    constexpr int boardFields = 8;
    //SDL_GetWindowSize(window, &w, &h);
    SDL_GetCurrentRenderOutputSize(renderer, &w, &h); // similar to SDL_GetWindowSize, but uses the current render destination

    // get size of squares
    const float squareSize = (w * 1.0f) / (boardFields * 1.0f);    //*1.f -> float/float und nicht mehr int/int

    // render squares
    for (int row = 0; row < boardFields; row++) {
        for (int col = 0; col < boardFields; col++) {

            // Alternate colors
            if ((row + col) % 2 == 0) {
                SDL_SetRenderDrawColor(renderer, color_scheme.white.r, color_scheme.white.g, color_scheme.white.b, color_scheme.white.a);
            }
            else {
                SDL_SetRenderDrawColor(renderer, color_scheme.black.r, color_scheme.black.g, color_scheme.black.b, color_scheme.black.a);
            }
            SDL_FRect rect = { col * squareSize, row * squareSize, squareSize, squareSize };

            SDL_RenderFillRect(renderer, &rect);

        }
    }
}

void Graphics::RenderChessTextures(SDL_Renderer* renderer, Brett& Spielfeld) {
    int w, h;
    constexpr int boardFields = 8;
    //SDL_GetWindowSize(window, &w, &h);
    SDL_GetCurrentRenderOutputSize(renderer, &w, &h); // similar to SDL_GetWindowSize, but uses the current render destination
    const float squareSize = (w * 1.0f) / (boardFields * 1.0f);
    int row;
    int col;

    for (int i = 0; i < boardFields; i++) {
        for (int j = 0; j < boardFields; j++) {
            if (Spielfeld.Felder[i][j] == NULL) continue;
            else {
                row = Spielfeld.Felder[i][j]->Get_Zeile()+1;
                col = Spielfeld.Felder[i][j]->Get_Spalte()+1;
                row = 8 - row;
                col = col - 1;
                int padding = 10;
                SDL_FRect rect = { col*squareSize + padding, row*squareSize + padding, squareSize - 2*padding, squareSize - 2*padding };
                SDL_SetTextureAlphaMod(Spielfeld.Felder[i][j]->Get_Texture(), static_cast<Uint8>(255.0f * Spielfeld.Felder[i][j]->Get_Wahrscheinlichkeit()));
                SDL_RenderTexture(renderer, Spielfeld.Felder[i][j]->Get_Texture(), NULL, &rect);
            }
        }
    }
}

void Graphics::RenderSidebar(SDL_Renderer* renderer, ColorScheme color_scheme, const MoveMode move_mode, const MoveBtnTex &move_btn_tex) {
    int w, h;
    SDL_GetCurrentRenderOutputSize(renderer, &w, &h);
    // TODO check if all three buttons together would be out of bounds
    float sqr_w = static_cast<float>(w);

    for (uint8_t btn = NORMAL; btn < MERGE+1; btn++) {
        SDL_Texture* tex = nullptr;
        Color color{};
        if (btn == move_mode)
             color = color_scheme.black;
        else
             color = color_scheme.white;

        switch (btn) {
            case NORMAL:
                tex = move_btn_tex.normal;
                break;
            case SPLIT:
                tex = move_btn_tex.split;
                break;
            case MERGE:
                tex = move_btn_tex.merge;
                break;
            default:
                break;

        }

        SDL_FRect rect = {
            0,
            btn * sqr_w,
            sqr_w,
            sqr_w
        };
        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
        SDL_RenderFillRect(renderer, &rect);
        SDL_RenderTextureRotated( renderer, tex, NULL, &rect, 90.0f, NULL, SDL_FLIP_NONE);
    }
}
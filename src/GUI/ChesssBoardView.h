#ifndef QUANTUMCHESS_CHESSSBOARDVIEW_H
#define QUANTUMCHESS_CHESSSBOARDVIEW_H

#include "../Model/Structs.h"
#include "../Deprecated/Brett.h"

class Graphics {

public:
    Graphics() = delete; // prevent creating instances

    static void CreateChessTextures(SDL_Renderer* renderer, Brett &Spielfeld);
    static void CreateMoveBtnTextures(SDL_Renderer* renderer, MoveBtnTex &move_btn_tex);
    static void DrawChessboard(SDL_Renderer* renderer, ColorScheme color_scheme);
    static void RenderChessTextures(SDL_Renderer* renderer, Brett& Spielfeld);
    static void RenderSidebar(SDL_Renderer *renderer, ColorScheme, MoveMode move_mode, const MoveBtnTex &move_btn_tex);

private:
    static SDL_Texture* GetTextureFromImage(SDL_Renderer* renderer, const char* img_location);

};


#endif //QUANTUMCHESS_CHESSSBOARDVIEW_H

#ifndef QUANTUMCHESS_GAMELOGIC_H
#define QUANTUMCHESS_GAMELOGIC_H

#include "../Model/Structs.h"
#include "../Model/Turm.h"
#include "../Model/Springer.h"
#include "../Model/Laeufer.h"
#include "../Model/Dame.h"
#include "../Model/Koenig.h"
#include "../Model/Bauer.h"

class GameLogic {

public:
    GameLogic() = delete; // prevent creating instances

    static Brett InitGameBoard();

    static void HandleNormalChessMoveEvent(TilePos* clicked_tile, TilePos*& selected_piece, std::vector<TilePos>& moves, Brett& board);
    static void HandleSplitChessMoveEvent(TilePos* clicked_tile, TilePos*& selected_piece, std::vector<TilePos>& moves, Brett& board);
    static void HandleMergeChessMoveEvent(TilePos* clicked_tile, TilePos*& selected_piece, std::vector<TilePos>& moves, Brett& board);


private:
    static std::unique_ptr<Turm> CreateRook(bool geschlagen, bool gezogen, bool isWhite, int row, int col);
    static std::unique_ptr<Springer> CreateKnight(bool geschlagen, bool isWhite, int row, int col);
    static std::unique_ptr<Laeufer> CreateBishop(bool geschlagen, bool isWhite, int row, int col);
    static std::unique_ptr<Dame> CreateQueen(bool geschlagen, bool isWhite, int row, int col);
    static std::unique_ptr<Koenig> CreateKing(bool geschlagen, bool gezogen, bool isWhite, int row, int col);
    static std::unique_ptr<Bauer>CreatePawn(bool geschlagen, bool gezogen, bool isWhite, int row, int col);

    static void MoveChessPieceNormal();
};


#endif //QUANTUMCHESS_GAMELOGIC_H
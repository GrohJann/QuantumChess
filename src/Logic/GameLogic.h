
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

    static void HandleNormalChessMoveEvent(
        TilePos& clicked_tile,
        TilePos& selected_piece,
        std::vector<TilePos>& possible_moves,
        Brett& board,
        bool& is_white_turn
    );

    static void HandleSplitChessMoveEvent(
        TilePos& clicked_tile,
        TilePos& selected_piece,
        std::vector<TilePos>& moves,
        std::vector<TilePos>& possible_moves,
        Brett& board,
        bool& is_white_turn
    );

    static void HandleMergeChessMoveEvent(
        TilePos& clicked_tile,
        TilePos& selected_piece,
        std::vector<TilePos>& moves,
        std::vector<TilePos>& possible_moves,
        Brett& board,
        bool& is_white_turn
    );


private:
    static Turm* CreateRook(bool geschlagen, bool gezogen, bool isWhite, int row, int col);
    static Springer* CreateKnight(bool geschlagen, bool isWhite, int row, int col);
    static Laeufer* CreateBishop(bool geschlagen, bool isWhite, int row, int col);
    static Dame* CreateQueen(bool geschlagen, bool isWhite, int row, int col);
    static Koenig* CreateKing(bool geschlagen, bool gezogen, bool isWhite, int row, int col);
    static Bauer* CreatePawn(bool geschlagen, bool gezogen, bool isWhite, int row, int col);

    static void MoveChessPieceNormal(TilePos& clicked_tile, TilePos& selected_piece, Brett& board);
    static void MoveChessPieceSplit(std::vector<TilePos>& moves, TilePos & selected_piece, Brett & board);
    static void MoveChessPieceMerge(TilePos& move, std::vector<TilePos>& selected_pieces, Brett & board);

    static bool CollapseQuantumState(const TilePos & selected_piece, Brett & board);

    static bool PieceExists(float probability);
};


#endif //QUANTUMCHESS_GAMELOGIC_H
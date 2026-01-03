
#include "GameLogic.h"

#include "Spiel_Logik/Koenig.h"


Brett GameLogic::InitGameBoard() {
    // static declaration to insure gameBoard persists outside its original scope
    Brett gameBoard;

    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            const bool isWhite = row < 4;

            if (row == 0 || row == 7) {
                // Uppermost and lowest row
                if (col == 0 || col == 7) {
                    gameBoard.Felder[row][col] = CreateRook(false, false, isWhite, row, col);//&rook; //std::make_unique<Turm>();
                } else if (col == 1 || col == 6) {
                    gameBoard.Felder[row][col] = CreateKnight(false, isWhite, row, col);
                } else if (col == 2 || col == 5) {
                    gameBoard.Felder[row][col] = CreateBishop(false, isWhite, row, col);
                } else if (col == 3) {
                    if (isWhite)
                        gameBoard.Felder[row][col] = CreateQueen(false, isWhite, row, col);
                    else
                        gameBoard.Felder[row][col] = CreateKing(false, false, isWhite, row, col);
                } else if (col == 4) {
                    if (isWhite)
                        gameBoard.Felder[row][col] = CreateKing(false, false, isWhite, row, col);
                    else
                        gameBoard.Felder[row][col] = CreateQueen(false, isWhite, row, col);
                }
            } else if (row == 1 || row == 6) {
                gameBoard.Felder[row][col] = CreatePawn(false, false, isWhite, row, col);
            } else {
                gameBoard.Felder[row][col] = nullptr;
            }
        }
    }

    return gameBoard;
}

std::unique_ptr<Turm> GameLogic::CreateRook(const bool geschlagen, const bool gezogen, const bool isWhite, const int row, const int col) {
    auto rook = std::make_unique<Turm>(); // allocate memory
    rook->Set_Geschlagen(geschlagen);
    rook->Set_Gezogen(gezogen);
    rook->Set_Farbe(isWhite);
    rook->Set_Zeile(row);
    rook->Set_Name('R');
    rook->Set_Spalte(col);
    rook->Set_Wahrscheinlichkeit(1.0f);

    return rook;
}

std::unique_ptr<Springer> GameLogic::CreateKnight(const bool geschlagen, const bool isWhite, const int row, const int col) {
    auto knight = std::make_unique<Springer>();
    knight->Set_Geschlagen(geschlagen);
    knight->Set_Farbe(isWhite);
    knight->Set_Zeile(row);
    knight->Set_Name('k');
    knight->Set_Spalte(col);
    knight->Set_Wahrscheinlichkeit(1.0f);

    return knight;
}

std::unique_ptr<Laeufer> GameLogic::CreateBishop(const bool geschlagen, const bool isWhite, const int row, const int col) {
    auto bishop = std::make_unique<Laeufer>();
    bishop->Set_Geschlagen(geschlagen);
    bishop->Set_Farbe(isWhite);
    bishop->Set_Zeile(row);
    bishop->Set_Name('B');
    bishop->Set_Spalte(col);
    bishop->Set_Wahrscheinlichkeit(1.0f);

    return bishop;
}

std::unique_ptr<Dame> GameLogic::CreateQueen(const bool geschlagen, const bool isWhite, const int row, const int col) {
    auto queen = std::make_unique<Dame>();
    queen->Set_Geschlagen(geschlagen);
    queen->Set_Farbe(isWhite);
    queen->Set_Zeile(row);
    queen->Set_Name('Q');
    queen->Set_Spalte(col);
    queen->Set_Wahrscheinlichkeit(1.0f);

    return queen;
}

std::unique_ptr<Koenig> GameLogic::CreateKing(const bool geschlagen, const bool gezogen, const bool isWhite, const int row, const int col) {
    auto king = std::make_unique<Koenig>();
    king->Set_Geschlagen(geschlagen);
    king->Set_Gezogen(gezogen);
    king->Set_Farbe(isWhite);
    king->Set_Zeile(row);
    king->Set_Name('K');
    king->Set_Spalte(col);
    king->Set_Wahrscheinlichkeit(1.0f);

    return king;
}

std::unique_ptr<Bauer> GameLogic::CreatePawn(const bool geschlagen, const bool gezogen, const bool isWhite, const int row, const int col) {
    auto king = std::make_unique<Bauer>();
    king->Set_Geschlagen(geschlagen);
    king->Set_Gezogen(gezogen);
    king->Set_Farbe(isWhite);
    king->Set_Zeile(row);
    king->Set_Name('P');
    king->Set_Spalte(col);
    king->Set_Wahrscheinlichkeit(1.0f);

    return king;
}



void GameLogic::HandleNormalChessMoveEvent(TilePos* clicked_tile, TilePos*& selected_piece, std::vector<TilePos>& moves, Brett& board) {
    if (selected_piece == nullptr) {
        // first chess piece selected
        if (board.Felder[clicked_tile->row][clicked_tile->col] != nullptr) {
            // clicked tile has a figure on it
            selected_piece = clicked_tile;
        }
    } else {
        if (clicked_tile == selected_piece) {
            //deselect tile
            selected_piece = nullptr;
            return;
        }
        // move
        MoveChessPieceNormal();
    }
}

void GameLogic::MoveChessPieceNormal() {
    // TODO: implement this
}

void GameLogic::HandleSplitChessMoveEvent(TilePos* clicked_tile, TilePos*& selected_piece, std::vector<TilePos>& moves, Brett& board) {
    // TODO: implement this
}

void GameLogic::HandleMergeChessMoveEvent(TilePos* clicked_tile, TilePos*& selected_piece, std::vector<TilePos>& moves, Brett& board) {
    // TODO: implement this
}

#include "../Logic/GameLogic.h"

#include <iostream>
#include <ostream>
#include <random>
#include <unordered_set>


Brett GameLogic::InitGameBoard() {
    // static declaration to insure gameBoard persists outside its original scope
    Brett gameBoard;

    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            const bool isWhite = row < 4;

            if (row == 0 || row == 7) {
                // Uppermost and lowest row
                if (col == 0 || col == 7) {
                    gameBoard.Felder[col][row] = CreateRook(false, false, isWhite, row, col);
                    //&rook; //std::make_unique<Turm>();
                } else if (col == 1 || col == 6) {
                    gameBoard.Felder[col][row] = CreateKnight(false, isWhite, row, col);
                } else if (col == 2 || col == 5) {
                    gameBoard.Felder[col][row] = CreateBishop(false, isWhite, row, col);
                } else if (col == 3) {
                    if (isWhite)
                        gameBoard.Felder[col][row] = CreateQueen(false, isWhite, row, col);
                    else
                        gameBoard.Felder[col][row] = CreateKing(false, false, isWhite, row, col);
                } else if (col == 4) {
                    if (isWhite)
                        gameBoard.Felder[col][row] = CreateKing(false, false, isWhite, row, col);
                    else
                        gameBoard.Felder[col][row] = CreateQueen(false, isWhite, row, col);
                }
            } else if (row == 1 || row == 6) {
                gameBoard.Felder[col][row] = CreatePawn(false, false, isWhite, row, col);
            } else {
                gameBoard.Felder[col][row] = nullptr;
            }
        }
    }

    return gameBoard;
}

Turm *GameLogic::CreateRook(const bool geschlagen, const bool gezogen, const bool isWhite, const int row, const int col) {
    const auto rook = new Turm(); //std::make_unique<Turm>(); // allocate memory
    rook->Set_Geschlagen(geschlagen);
    rook->Set_Gezogen(gezogen);
    rook->Set_Farbe(isWhite);
    rook->Set_Zeile(row + 1);
    rook->Set_Name('R');
    rook->Set_Spalte(col + 1);
    rook->Set_Wahrscheinlichkeit(1.0f);
    rook->Set_ID(
        (!isWhite << 31) |
        (row << 17) |
        col
    );

    return rook;
}

Springer *GameLogic::CreateKnight(const bool geschlagen, const bool isWhite, const int row, const int col) {
    auto knight = new Springer();
    knight->Set_Geschlagen(geschlagen);
    knight->Set_Farbe(isWhite);
    knight->Set_Zeile(row + 1);
    knight->Set_Name('k');
    knight->Set_Spalte(col + 1);
    knight->Set_Wahrscheinlichkeit(1.0f);
    knight->Set_ID(
        (!isWhite << 31) |
        (row << 17) |
        col
    );

    return knight;
}

Laeufer *GameLogic::CreateBishop(const bool geschlagen, const bool isWhite, const int row, const int col) {
    auto bishop = new Laeufer();
    bishop->Set_Geschlagen(geschlagen);
    bishop->Set_Farbe(isWhite);
    bishop->Set_Zeile(row + 1);
    bishop->Set_Name('B');
    bishop->Set_Spalte(col + 1);
    bishop->Set_Wahrscheinlichkeit(1.0f);
    bishop->Set_ID(
        (!isWhite << 31) |
        (row << 17) |
        col
    );

    return bishop;
}

Dame *GameLogic::CreateQueen(const bool geschlagen, const bool isWhite, const int row, const int col) {
    auto queen = new Dame();
    queen->Set_Geschlagen(geschlagen);
    queen->Set_Farbe(isWhite);
    queen->Set_Zeile(row + 1);
    queen->Set_Name('Q');
    queen->Set_Spalte(col + 1);
    queen->Set_Wahrscheinlichkeit(1.0f);
    queen->Set_ID(
        (!isWhite << 31) |
        (row << 17) |
        col
    );

    return queen;
}

Koenig *GameLogic::CreateKing(const bool geschlagen, const bool gezogen, const bool isWhite, const int row, const int col) {
    auto king = new Koenig();
    king->Set_Geschlagen(geschlagen);
    king->Set_Gezogen(gezogen);
    king->Set_Farbe(isWhite);
    king->Set_Zeile(row + 1);
    king->Set_Name('K');
    king->Set_Spalte(col + 1);
    king->Set_Wahrscheinlichkeit(1.0f);
    king->Set_ID(
        (!isWhite << 31) |
        (row << 17) |
        col
    );

    return king;
}

Bauer *GameLogic::CreatePawn(const bool geschlagen, const bool gezogen, const bool isWhite, const int row, const int col) {
    auto pawn = new Bauer();
    pawn->Set_Geschlagen(geschlagen);
    pawn->Set_Gezogen(gezogen);
    pawn->Set_Farbe(isWhite);
    pawn->Set_Zeile(row + 1);
    pawn->Set_Name('P');
    pawn->Set_Spalte(col + 1);
    pawn->Set_Wahrscheinlichkeit(1.0f);
    pawn->Set_ID(
        (!isWhite << 31) |
        (row << 17) |
        col
    );

    return pawn;
}



void GameLogic::HandleNormalChessMoveEvent(TilePos &clicked_tile, TilePos &selected_piece, std::vector<TilePos> &possible_moves, Brett &board, bool &is_white_turn) {
    constexpr TilePos comp{
        255,
        255
    };
    if (selected_piece == comp) {
        // first chess piece selected
        Uint8 actual_row, actual_col;
        actual_row = 7 - clicked_tile.row; // swap because board has white on top but board is with white on bottom
        //actual_col = clicked_tile.col + 1;
        if (board.Felder[clicked_tile.col][actual_row] != nullptr && board.Felder[clicked_tile.col][actual_row]->
            Get_Farbe() == is_white_turn) {
            // clicked tile has a figure on it
            selected_piece = clicked_tile;
            board.Felder[clicked_tile.col][actual_row]->Set_Moegliche_Felder(board);
            vector<Moegliches_Feld> possible = board.Felder[clicked_tile.col][actual_row]->Get_Moegliche_Felder();
            for (const Moegliches_Feld &feld: possible) {
                possible_moves.push_back(
                    {
                        static_cast<Uint8>(8 - feld.zeile),
                        static_cast<Uint8>(feld.spalte - 1)
                    }
                );
            }
        }
    } else {
        if (clicked_tile == selected_piece) {
            //deselect tile
            selected_piece = comp;
            possible_moves.clear();
            return;
        }
        // move
        TilePos temp = {
            clicked_tile.row,
            clicked_tile.col
        };
        if (std::ranges::find(possible_moves.begin(), possible_moves.end(), temp) != possible_moves.end()) {
            MoveChessPieceNormal(clicked_tile, selected_piece, board);
            selected_piece = comp;
            possible_moves.clear();
            is_white_turn = !is_white_turn;
        }
    }
}

void GameLogic::MoveChessPieceNormal(TilePos &clicked_tile, TilePos &selected_piece, Brett &board) {
    Uint8 actual_selected_row = 7 - selected_piece.row;
    Uint8 actual_clicked_row = 7 - clicked_tile.row;

    if (board.Felder[clicked_tile.col][actual_clicked_row] != nullptr) {
        // chesspiece might get captured
        if (board.Felder[selected_piece.col][actual_selected_row]->Get_Wahrscheinlichkeit() != 1.0f) {
            if (!CollapseQuantumState(selected_piece, board)) {
                // selected piece does not exist
                return;
            }
        }
        // TODO: handle castle and en passant
        if (board.Felder[clicked_tile.col][actual_clicked_row]->Get_Wahrscheinlichkeit() != 1.0f) {
            // chess piece captured
            CollapseQuantumState(clicked_tile, board);
        }
    }
    // move chess piece
    board.Felder[clicked_tile.col][actual_clicked_row] = board.Felder[selected_piece.col][actual_selected_row];
    board.Felder[clicked_tile.col][actual_clicked_row]->Set_Zeile(actual_clicked_row + 1);
    board.Felder[clicked_tile.col][actual_clicked_row]->Set_Spalte(clicked_tile.col + 1);
    board.Felder[clicked_tile.col][actual_clicked_row]->Set_Gezogen(true);
    board.Felder[selected_piece.col][actual_selected_row] = nullptr;
}



void GameLogic::HandleSplitChessMoveEvent(TilePos &clicked_tile, TilePos &selected_piece, std::vector<TilePos> &moves, std::vector<TilePos> &possible_moves, Brett &board, bool &is_white_turn) {
    constexpr TilePos comp{
        255,
        255
    };
    if (selected_piece == comp) {
        // first chess piece selected
        const Uint8 actual_row = 7 - clicked_tile.row;
        // swap because board has white on top but board is with white on bottom
        if (board.Felder[clicked_tile.col][actual_row] != nullptr && board.Felder[clicked_tile.col][actual_row]->
            Get_Farbe() == is_white_turn) {
            // clicked tile has a figure on it
            selected_piece = clicked_tile;
            board.Felder[clicked_tile.col][actual_row]->Set_Moegliche_Felder(board);
            vector<Moegliches_Feld> possible = board.Felder[clicked_tile.col][actual_row]->Get_Moegliche_Felder();
            for (const Moegliches_Feld &feld: possible) {
                possible_moves.push_back(
                    {
                        static_cast<Uint8>(8 - feld.zeile),
                        static_cast<Uint8>(feld.spalte - 1)
                    }
                );
            }
        }
    } else {
        if (clicked_tile == selected_piece) {
            //deselect tile
            selected_piece = comp;
            possible_moves.clear();
            return;
        }

        const TilePos temp = {
            clicked_tile.row,
            clicked_tile.col
        };
        if (std::ranges::find(possible_moves.begin(), possible_moves.end(), temp) != possible_moves.end()) {
            moves.push_back(clicked_tile);
        }
        if (moves.size() >= 2) {
            // move
            MoveChessPieceSplit(moves, selected_piece, board);
            selected_piece = comp;
            possible_moves.clear();
            is_white_turn = !is_white_turn;
            moves.clear();
        }
    }
}

void GameLogic::MoveChessPieceSplit(std::vector<TilePos> &moves, TilePos &selected_piece, Brett &board) {
    const Uint8 actual_selected_row = 7 - selected_piece.row;

    // TODO: implement castling
    for (auto &move: moves) {
        const Uint8 actual_move_row = 7 - move.row;

        if (board.Felder[move.col][actual_move_row] != nullptr) {
            return; // possibly capturing on a split move is not a legitimate move
        }
        const bool isWhite = board.Felder[selected_piece.col][actual_selected_row]->Get_Farbe();
        const int row = actual_move_row;
        const int col = move.col;
        const int ID = board.Felder[selected_piece.col][actual_selected_row]->Get_ID();
        const float new_possibility = board.Felder[selected_piece.col][actual_selected_row]->Get_Wahrscheinlichkeit() /
                                      moves.size();
        SDL_Texture *texture = board.Felder[selected_piece.col][actual_selected_row]->Get_Texture();

        switch (board.Felder[selected_piece.col][actual_selected_row]->Get_Name()) {
            case 'P':
                board.Felder[move.col][actual_move_row] = CreatePawn(false, true, isWhite, row, col);
                board.Felder[move.col][actual_move_row]->Set_ID(ID);
                board.Felder[move.col][actual_move_row]->Set_Wahrscheinlichkeit(new_possibility);
                board.Felder[move.col][actual_move_row]->Set_Texture(texture);
                break;
            case 'K':
                board.Felder[move.col][actual_move_row] = CreateKing(false, true, isWhite, row, col);
                board.Felder[move.col][actual_move_row]->Set_ID(ID);
                board.Felder[move.col][actual_move_row]->Set_Wahrscheinlichkeit(new_possibility);
                board.Felder[move.col][actual_move_row]->Set_Texture(texture);
                break;
            case 'Q':
                board.Felder[move.col][actual_move_row] = CreateQueen(false, isWhite, row, col);
                board.Felder[move.col][actual_move_row]->Set_ID(ID);
                board.Felder[move.col][actual_move_row]->Set_Wahrscheinlichkeit(new_possibility);
                board.Felder[move.col][actual_move_row]->Set_Texture(texture);
                break;
            case 'B':
                board.Felder[move.col][actual_move_row] = CreateBishop(true, isWhite, row, col);
                board.Felder[move.col][actual_move_row]->Set_ID(ID);
                board.Felder[move.col][actual_move_row]->Set_Wahrscheinlichkeit(new_possibility);
                board.Felder[move.col][actual_move_row]->Set_Texture(texture);
                break;
            case 'k':
                board.Felder[move.col][actual_move_row] = CreateKnight(false, isWhite, row, col);
                board.Felder[move.col][actual_move_row]->Set_ID(ID);
                board.Felder[move.col][actual_move_row]->Set_Wahrscheinlichkeit(new_possibility);
                board.Felder[move.col][actual_move_row]->Set_Texture(texture);
                break;
            case 'R':
                board.Felder[move.col][actual_move_row] = CreateRook(false, true, isWhite, row, col);
                board.Felder[move.col][actual_move_row]->Set_ID(ID);
                board.Felder[move.col][actual_move_row]->Set_Wahrscheinlichkeit(new_possibility);
                board.Felder[move.col][actual_move_row]->Set_Texture(texture);
                break;
            default:
                //TODO: use SDL3 error handling instead
                std::cout << "Error in GameLogic::MoveChessPieceSplit: ChessPiece with name "
                        << board.Felder[selected_piece.col][actual_selected_row]->Get_Name() << " was not recognized" <<
                        std::endl;
                break;
        }
    }

    board.Felder[selected_piece.col][actual_selected_row] = nullptr;
}



// needs two selected pieces and one clicked_tile
void GameLogic::HandleMergeChessMoveEvent(TilePos &clicked_tile, TilePos &move, std::vector<TilePos> &selected_pieces, std::vector<TilePos> &possible_moves, Brett &board, bool &is_white_turn) {
    constexpr TilePos comp{
        255,
        255
    };
    const Uint8 actual_clicked_row = 7 - clicked_tile.row;
    if (selected_pieces.empty() && board.Felder[clicked_tile.col][actual_clicked_row]->Get_Farbe() == is_white_turn) {
        // Todo: add first chess piece
        // first chess piece selected

        if (board.Felder[clicked_tile.col][actual_clicked_row] != nullptr && board.Felder[clicked_tile.col][actual_clicked_row]->Get_Farbe() == is_white_turn) {
            // clicked tile has a figure on it
            selected_pieces.push_back(clicked_tile);
            board.Felder[clicked_tile.col][actual_clicked_row]->Set_Moegliche_Felder(board);
            vector<Moegliches_Feld> possible = board.Felder[clicked_tile.col][actual_clicked_row]->Get_Moegliche_Felder();
            for (const Moegliches_Feld & feld: possible) {
                possible_moves.push_back(
                    {
                            static_cast<Uint8>(8-feld.zeile),
                            static_cast<Uint8>(feld.spalte-1)
                        }
                    );
            }
        }
    } else if (selected_pieces.size() == 1) {
        for (auto it = selected_pieces.begin(); it != selected_pieces.end(); ++it) {
            if (*it == clicked_tile) {
                // deselect tile
                selected_pieces.erase(it);
                possible_moves.clear();
                return;
            }
        }

        selected_pieces.push_back(clicked_tile);
        if (selected_pieces.size() >= 2) {
            // Check if valid move
            //TODO: check valid move
            const Uint8 actual_first_selected_row = 7 - selected_pieces.begin()->row;

            const int id = board.Felder[selected_pieces.begin()->col][actual_first_selected_row]->Get_ID();
            for (auto it = selected_pieces.begin(); it != selected_pieces.end(); ++it) {
                if (board.Felder[it->col][it->row] == nullptr
                    || board.Felder[it->col][it->row]->Get_ID() != id) {
                    selected_pieces.erase(it);
                }
            }

/*----------------------------------------------------------------------------------------------------------------------
                        auto it = selected_pieces.begin();
                        ++it;
                        for (; it != selected_pieces.end(); ++it) {
                            const Uint8 actual_row = 7 - it->row;
                            auto moegliche_felder = board.Felder[it->col][actual_row]->Get_Moegliche_Felder();
                            for (auto mf_it = moegliche_felder.begin(); mf_it != moegliche_felder.end(); ++mf_it) {
                                TilePos pos = {
                                    static_cast<Uint8>(mf_it->zeile),
                                     static_cast<Uint8>(mf_it->spalte)
                                };
                                auto pm_it = std::ranges::find(possible_moves.begin(), possible_moves.end(), pos);
                                if ( pm_it == possible_moves.end()) {
                                    // possible move not found
                                    //possible_moves.erase(pm_it);
                                }
                            }
                        }
//--------------------------------------------------------------------------------------------------------------------*/
            // Update possible_moves
            //TODO: update possible moves

            possible_moves.clear();
            std::vector<Moegliches_Feld> moegliche_felder = board.Felder[selected_pieces.begin()->col][actual_first_selected_row]->Get_Moegliche_Felder();
            std::unordered_set<Moegliches_Feld, MoeglichesFeldHash> set(moegliche_felder.begin(), moegliche_felder.end());
            for (const auto& moegliches_feld : board.Felder[(++selected_pieces.begin())->col][7-(++selected_pieces.begin())->row]->Get_Moegliche_Felder()) {
                if (set.contains(moegliches_feld)) {
                    possible_moves.push_back({static_cast<Uint8>(8-moegliches_feld.zeile), static_cast<Uint8>(moegliches_feld.spalte-1)});
                }
            }

        }
    } else if (selected_pieces.size() >= 2) {
        //move
        const TilePos temp = {
            clicked_tile.row,
            clicked_tile.col
        };
        if (std::ranges::find(possible_moves.begin(), possible_moves.end(), temp) != possible_moves.end()) {
            MoveChessPieceMerge(move, selected_pieces, board);
            selected_pieces.clear();
            move = {
                255,
                255
            };
            is_white_turn = !is_white_turn;
            possible_moves.clear();
        }
    }
    /*   if (selected_piece == comp) {
           // first chess piece selected
           const Uint8 actual_row = 7 - clicked_tile.row; // swap because board has white on top but board is with white on bottom

           if (board.Felder[clicked_tile.col][actual_row] != nullptr && board.Felder[clicked_tile.col][actual_row]->Get_Farbe() == is_white_turn) {
               // clicked tile has a figure on it
               selected_piece = clicked_tile;
               board.Felder[clicked_tile.col][actual_row]->Set_Moegliche_Felder(board);
               vector<Moegliches_Feld> possible = board.Felder[clicked_tile.col][actual_row]->Get_Moegliche_Felder();
               for (const Moegliches_Feld & feld: possible) {
                   possible_moves.push_back(
                       {
                               static_cast<Uint8>(8-feld.zeile),
                               static_cast<Uint8>(feld.spalte-1)
                           }
                       );
               }
           }
       }//*/
}

void GameLogic::MoveChessPieceMerge(TilePos &move, std::vector<TilePos> &selected_pieces, Brett &board) {

}



/**
    * Collapses quantum states of chess pieces based on the probability of the selected chess piece.
 * If the selected chess piece exitists then the probability of it exsiting is set to 1.0f and all other possible
 * locations of that chess piece are removed. If the selected chess piece does not exist then it's probability is split
 * equally to all other possible chess piece locations and the selected chess piece is removed.
 * @param selected_piece the selected piece to collapse
 * @param board the entire gameboard
 * @return true when the selected piece exists otherwise false
 */
bool GameLogic::CollapseQuantumState(const TilePos &selected_piece, Brett &board) {
    Uint8 actual_piece_row = 7 - selected_piece.row;

    if (PieceExists(board.Felder[selected_piece.col][actual_piece_row]->Get_Wahrscheinlichkeit())) {
        board.Felder[selected_piece.col][actual_piece_row]->Set_Wahrscheinlichkeit(1.0f);
        int ID, col, row;
        ID = board.Felder[selected_piece.col][actual_piece_row]->Get_ID();
        col = board.Felder[selected_piece.col][actual_piece_row]->Get_Spalte();
        row = board.Felder[selected_piece.col][actual_piece_row]->Get_Zeile();
        TilePos pos = {
            static_cast<Uint8>(row),
            static_cast<Uint8>(col)
        };
        for (auto &spalte: board.Felder) {
            for (auto &piece: spalte) {
                if (piece != nullptr && piece->Get_ID() == ID) {
                    TilePos piece_pos = {
                        static_cast<Uint8>(piece->Get_Zeile()),
                        static_cast<Uint8>(piece->Get_Spalte())
                    };
                    if (pos != piece_pos) {
                        piece = nullptr;
                    }
                }
            }
        }
        return true;
    } else {
        // piece doesn't exist
        int ID = board.Felder[selected_piece.col][actual_piece_row]->Get_ID();
        float possibility = board.Felder[selected_piece.col][actual_piece_row]->Get_Wahrscheinlichkeit();
        board.Felder[selected_piece.col][actual_piece_row] = nullptr;
        vector<TilePos> other_pieces;
        for (Uint8 i = 0; i < 8; i++) {
            for (Uint8 j = 0; j < 8; j++) {
                if (board.Felder[i][j] != nullptr && board.Felder[i][j]->Get_ID() == ID) {
                    other_pieces.push_back({i, j});
                }
            }
        }
        possibility = possibility / static_cast<float>(other_pieces.size());
        for (auto &[row, col]: other_pieces) {
            const float pos = board.Felder[row][col]->Get_Wahrscheinlichkeit();
            board.Felder[row][col]->Set_Wahrscheinlichkeit(pos + possibility);
        }
        return false;
    }
}

/**
 * Calculates whether a Piece exists by the probability passed using a bernoulli distribution
 * @param probability probability that the piece exists
 * @return true when the piece exists otherwise false
 */
bool GameLogic::PieceExists(const float probability) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::bernoulli_distribution d(probability);
    return d(gen);
}

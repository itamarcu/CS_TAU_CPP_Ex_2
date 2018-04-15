#include <fstream>
#include <map>
#include <iostream>
#include <sstream>
#include "BoardIO.h"


LoadBoardResult BoardIO::_add_load_into_board(Game &game, bool player) {
    std::string player_num = player ? "1" : "2";
    std::string file_path = "player" + player_num + ".rps_board";
    std::ifstream fin(file_path);
    if (fin.eof()) {
        std::cerr << "Unable to find/open this file path: " << file_path << std::endl;
        return LoadBoardResult(0, UnableToOpenPath);
    }

    auto remainingCounts = std::map<GamePieceType, int>();
    remainingCounts[GamePieceType::Rock] = R;
    remainingCounts[GamePieceType::Paper] = P;
    remainingCounts[GamePieceType::Scissors] = S;
    remainingCounts[GamePieceType::Bomb] = B;
    remainingCounts[GamePieceType::Flag] = F;
    int remainingJokerCount = J; // Joker

    int line_num = 0; // Line starts at 1!
    std::string line;
    while (std::getline(fin, line)) {
        line_num += 1;
        auto delimiter = std::string(" "); // sadly, can't use " "s
        auto contents = split_string_using_delimiter(line, delimiter);
        if (contents->size() > 4 || contents->size() < 3)
            return LoadBoardResult(line_num, BadFormat);

        auto piece = GamePiece(player);
        if (contents->size() == 4) { // is a Joker
            if ((*contents)[0] != "J") // NOTE - this is a string, not a char
                return LoadBoardResult(line_num, BadFormat);
            piece.isJoker = true;
            piece.type = type_from_char((*contents)[3][0]);
            if (piece.type == None || piece.type == Flag) // Only allowed: R P S B
                return LoadBoardResult(line_num, InvalidJokerPieceType);
            remainingJokerCount--;
            if (remainingJokerCount < 0)
                return LoadBoardResult(line_num, TooManyOfSamePiece);
        } else { // is not a Joker
            piece.type = type_from_char((*contents)[0][0]);
            if (piece.type == None)
                return LoadBoardResult(line_num, InvalidPieceType);
            remainingCounts[piece.type]--;
            if (remainingCounts[piece.type] < 0)
                return LoadBoardResult(line_num, TooManyOfSamePiece);
        }

        piece.player = player;

        int r = std::stoi((*contents)[1]);
        int c = std::stoi((*contents)[2]);
        if (r < 1 || r > M || c < 1 || c > N)
            return LoadBoardResult(line_num, CoordinatesOutOfBound);
        r -= 1; // because 0-indexing
        c -= 1; // ^

        auto *piece_ptr = new GamePiece(piece); // uses implicit Copy Constructor

        if (game.board[r][c] == nullptr)
            game.board[r][c] = piece_ptr;
        else if (game.board[r][c]->player == player) {
            delete piece_ptr;
            return LoadBoardResult(line_num, TwoPiecesSamePlayerSamePosition);
        } else {
            //This code is here because otherwise we'll have to store 2 boards and merge
            actually_fight(game, piece_ptr, game.board[r][c], Cell(r, c));
            //if piece lost the fight, pointer was deleted
        }
    }

    if (remainingCounts[GamePieceType::Flag] != 0)
        return LoadBoardResult(line_num, NotAllFlagsWerePlaced);

    return LoadBoardResult(line_num, BoardLoadingSuccess);
}


void _load_player_moves(GameMoves &gameMoves, bool player) {
    std::string player_num = player ? "1" : "2";
    std::string file_path = "player" + player_num + ".rps_moves";
    std::ifstream fin(file_path);
    if (fin.eof()) {
        std::cerr << "Unable to find/open this file path: " << file_path << std::endl;
        return;
    }

    std::vector<PlannedMove> &moves = player ? gameMoves.p1_moves : gameMoves.p2_moves;
    moves.clear();

    std::string line;
    while (std::getline(fin, line)) {
        if (line.empty() || line.length() <= 1)
            break;
        auto delimiter = std::string(" ");
        auto contents = split_string_using_delimiter(line, delimiter);
        if (contents->size() != 4 && contents->size() != 8) {
            std::cout << "bad format line:    \"" << line << "\" (was split into " <<
                      contents->size() << ")" << std::endl;
            moves.push_back(PlannedMove(false));
            continue;
        }


        int r1 = std::stoi((*contents)[0]);
        int c1 = std::stoi((*contents)[1]);
        int r2 = std::stoi((*contents)[2]);
        int c2 = std::stoi((*contents)[3]);
        if (r1 < 1 || r1 > M || c1 < 1 || c1 > N ||
            r2 < 1 || r2 > M || c2 < 1 || c2 > N) {
            moves.push_back(PlannedMove(false));
            continue;
        }
        r1 -= 1; // because 0-indexing
        c1 -= 1; // ^
        r2 -= 1; // ^
        c2 -= 1; // ^

        if (contents->size() == 8) {
            if ((*contents)[4] != "J:") {
                moves.push_back(PlannedMove(false));
                continue;
            };

            int jr = std::stoi((*contents)[5]);
            int jc = std::stoi((*contents)[6]);
            if (jr < 1 || jr > M || jc < 1 || jc > N) {
                moves.push_back(PlannedMove(false));
                continue;
            }
            jr -= 1;
            jc -= 1;
            GamePieceType jokerType = type_from_char((*contents)[7][0]);
            if (jokerType == None) {
                moves.push_back(PlannedMove(false));
                continue;
            }
            moves.push_back(PlannedMove(r1, c1, r2, c2, jr, jc, jokerType));
        } else
            moves.push_back(PlannedMove(r1, c1, r2, c2));
    }

}

void BoardIO::load_moves(GameMoves &gameMoves) {
    _load_player_moves(gameMoves, true);
    _load_player_moves(gameMoves, false);
}

void BoardIO::setup_game(Game &game) {
    LoadBoardResult load_of_1 = BoardIO::_add_load_into_board(game, true);
    LoadBoardResult load_of_2 = BoardIO::_add_load_into_board(game, false);
    if (load_of_1.type != BoardLoadingSuccess && load_of_2.type != BoardLoadingSuccess) {
        std::stringstream s;
        s << "Bad Positioning input file for both players - ";
        s << "player 1: line " << load_of_1.line_num;
        s << ", ";
        s << "player 2: line " << load_of_2.line_num;
        game.endGame(TIE, s.str());
        std::cout << "error 1 is " << load_of_1.type <<
                  ", error 2 is " << load_of_2.type << std::endl;
    } else if (load_of_1.type != BoardLoadingSuccess) {
        std::stringstream s;
        s << "Bad Positioning input file for player 1 - ";
        s << "line " << load_of_1.line_num;
        game.endGame(PLAYER_2_VICTORY, s.str());
        std::cout << "error 1 is " << load_of_1.type << std::endl;
    } else if (load_of_2.type != BoardLoadingSuccess) {
        std::stringstream s;
        s << "Bad Positioning input file for player 2 - ";
        s << "line " << load_of_2.line_num;
        std::cout << "error 2 is " << load_of_2.type << std::endl;
        game.endGame(PLAYER_1_VICTORY, s.str());
    }
}

void BoardIO::store_game(Game &game) {
    std::ofstream fout("rps.output");
    fout << "Winner: " << game.getGameWinner() << std::endl;
    fout << "Reason: " << game.getGameEndReason() << std::endl;
    fout << std::endl;

    //Prints transposed

    for (int col = 0; col < N; col++) {
        for (int row = 0; row < M; row++) {
            char ch = ' ';
            if (game.board[row][col] != nullptr) {
                ch = game.board[row][col]->to_char();
            }
            fout << ch;
        }
        fout << std::endl;
    }

    // Prints normally

    //    for (int row = 0; row < M; row++) {
    //        for (int col = 0; col < N; col++) {
    //            char ch = ' ';
    //            if (game.board[row][col] != nullptr) {
    //                ch = game.board[row][col]->to_char();
    //            }
    //            fout << ch;
    //        }
    //        fout << std::endl;
    //    }

    fout.flush();
}

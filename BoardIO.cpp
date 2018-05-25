#include <fstream>
#include <map>
#include <iostream>
#include <sstream>
#include "BoardIO.h"

LoadBoardResult BoardIO::load_board(MyBoard &board, bool player){
    std::string player_num = player ? "1" : "2";
    std::string file_path = "player" + player_num + ".rps_board";
    std::ifstream fin(file_path);
    if (fin.fail()) {
        std::cerr << "Unable to find/open this file path: " << file_path << std::endl;
        return LoadBoardResult(0, UnableToOpenPath);
    }
    std::map<GamePieceType, int> remainingCounts;
    int remainingJokerCount;
    settingCounts(remainingCounts, remainingJokerCount);

    int line_num = 0; // Line starts at 1!
    std::string line;
    while (std::getline(fin, line)) {
        line_num += 1;
        auto delimiter = std::string(" "); // sadly, can't use " "s
        auto contents = split_string_using_delimiter(line, delimiter);
        if (contents->size() > 4 || contents->size() < 3)
            return LoadBoardResult(line_num, BadFormat);

        auto piece = GamePiece(player, GamePieceType::None);
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


        std::shared_ptr<GamePiece> piece_ptr(new GamePiece {piece});
        if (board.grid[r][c] == nullptr)
            board.grid[r][c] = piece_ptr;
        else if (board.grid[r][c]->player == player) {
            return LoadBoardResult(line_num, TwoPiecesSamePlayerSamePosition);
        }
    }

    if (remainingCounts[GamePieceType::Flag] != 0)
        return LoadBoardResult(line_num, NotAllFlagsWerePlaced);

    return LoadBoardResult(line_num, BoardLoadingSuccess);
}

/**
 * setting counts for loading board file
 * @param remainingCounts remaining counts map of pieces
 * @param remainingJokerCount remaining counts of joker
 */
void BoardIO::settingCounts(std::map<GamePieceType, int> &remainingCounts, int &remainingJokerCount) {
    remainingCounts= std::map<GamePieceType, int>();
    remainingJokerCount= J;
    remainingCounts[Rock] = R;
    remainingCounts[Paper] = P;
    remainingCounts[Scissors] = S;
    remainingCounts[Bomb] = B;
    remainingCounts[Flag] = F;// Joker

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
            moves.emplace_back(PlannedMove(false));
            continue;
        }


        int x1 = std::stoi((*contents)[0]);
        int y1 = std::stoi((*contents)[1]);
        int x2 = std::stoi((*contents)[2]);
        int y2 = std::stoi((*contents)[3]);
        if (x1 < 1 || x1 > M || y1 < 1 || y1 > N ||
            x2 < 1 || x2 > M || y2 < 1 || y2 > N) {
            moves.emplace_back(PlannedMove(false));
            continue;
        }
        x1 -= 1; // because 0-indexing
        y1 -= 1; // ^
        x2 -= 1; // ^
        y2 -= 1; // ^

        if (contents->size() == 8) {
            if ((*contents)[4] != "J:") {
                moves.emplace_back(PlannedMove(false));
                continue;
            };

            int jx = std::stoi((*contents)[5]);
            int jy = std::stoi((*contents)[6]);
            if (jx < 1 || jx > M || jy < 1 || jy > N) {
                moves.emplace_back(PlannedMove(false));
                continue;
            }
            jx -= 1;
            jy -= 1;
            GamePieceType jokerType = type_from_char((*contents)[7][0]);
            if (jokerType == None) {
                moves.emplace_back(PlannedMove(false));
                continue;
            }
            moves.emplace_back(PlannedMove(x1, y1, x2, y2, jx, jy, jokerType));
        } else
            moves.emplace_back(PlannedMove(x1, y1, x2, y2));
    }

}

void BoardIO::load_moves(GameMoves &gameMoves) {
    _load_player_moves(gameMoves, true);
    _load_player_moves(gameMoves, false);
}

void BoardIO::setup_game(Game &game) {
    LoadBoardResult load_of_1 = BoardIO::load_board(game.board, true);
    LoadBoardResult load_of_2 = BoardIO::load_board(game.board, false);
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

    for (int y = 0; y < N; y++) {
        for (int x = 0; x < M; x++) {
            char ch = ' ';
            if (game.board.grid[x][y] != nullptr) {
                ch = game.board.grid[x][y]->to_char();
            }
            fout << ch;
        }
        fout << std::endl;
    }

    // Prints normally

    //    for (int x = 0; x < M; x++) {
    //        for (int y = 0; y < N; y++) {
    //            char ch = ' ';
    //            if (game.board.grid[x][y] != nullptr) {
    //                ch = game.board.grid[x][y]->to_char();
    //            }
    //            fout << ch;
    //        }
    //        fout << std::endl;
    //    }

    fout.flush();
}

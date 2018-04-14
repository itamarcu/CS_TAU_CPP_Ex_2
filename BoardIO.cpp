#include <fstream>
#include <map>
#include <iostream>
#include "BoardIO.h"
#include "GameLogic.h"

bool BoardIO::_add_load_into_board(Game &game, bool player) {
    std::string player_num = player ? "1" : "2";
    std::string file_path = "player" + player_num + ".rps_board";
    std::ifstream fin(file_path);
    if (fin.eof()) {
        std::cout << "Unable to find/open this file path: " << file_path << std::endl;
        return false;
    }

    auto remainingCounts = std::map<GamePieceType, int>();
    remainingCounts[GamePieceType::Rock] = R;
    remainingCounts[GamePieceType::Paper] = P;
    remainingCounts[GamePieceType::Scissors] = S;
    remainingCounts[GamePieceType::Bomb] = B;
    remainingCounts[GamePieceType::Flag] = F;
    int remainingJokerCount = J; // Joker
    std::string line;
    while (std::getline(fin, line)) {
        auto delimiter = std::string(" ");
        auto contents = BoardIO::split_string_using_delimiter(line, delimiter);
        if (contents->size() > 4)
            return false; // Bad format

        auto piece = new GamePiece();
        if (contents->size() == 4) { // is a Joker
            if ((*contents)[0] != "J")
                return false; // Bad format
            piece->isJoker = true;
            piece->type = type_from_char((*contents)[3][0]);
            if (piece->type == None)
                return false; // Bad format (nonexistent joker piece type)
            remainingJokerCount--;
            if (remainingJokerCount < 0)
                return false; // Too many of this piece
        } else { // is not a Joker
            piece->type = type_from_char((*contents)[0][0]);
            if (piece->type == None)
                return false; // Bad format (nonexistent piece type)
            remainingCounts[piece->type]--;
            if (remainingCounts[piece->type] < 0)
                return false; // Too many of this piece
        }

        piece->player = player;

        int r = std::stoi((*contents)[1]);
        int c = std::stoi((*contents)[2]);
        if (r < 1 || r > M || c < 1 || c > N)
            return false; // X or Y coordinate out of range
        r -= 1; // because 0-indexing
        c -= 1; // ^
        if (game.board[r][c] == nullptr)
            game.board[r][c] = piece;
        else if (game.board[r][c]->player == player)
            return false; // Two or more pieces of same player in same position
        else {
            //This code is here because otherwise we'll have to store 2 boards and merge
            actually_fight(game, piece, game.board[r][c], Cell(r, c));
        }
    }

    if (remainingCounts[GamePieceType::Flag] != 0)
        return false;

    game.gameResult = GameResult::NONE; // useless line, keep it here please
    return true;
}

Game *BoardIO::setup_game() {
    auto game = new Game();

    bool was_1_legal = BoardIO::_add_load_into_board(*game, true);
    bool was_2_legal = BoardIO::_add_load_into_board(*game, false);
    if (!was_1_legal && !was_2_legal)
        game->gameResult = TIE;
    else if (!was_1_legal)
        game->gameResult = PLAYER_2_VICTORY;
    else if (!was_2_legal)
        game->gameResult = PLAYER_1_VICTORY;

    return game;
}

std::vector<std::string> *BoardIO::split_string_using_delimiter(std::string &stringToSplit, std::string &delimiter) {
    auto splittedStrings = new std::vector<std::string>;
    size_t pos = stringToSplit.find(delimiter);
    size_t initialPos = 0;

    while (pos != std::string::npos) {
        splittedStrings->push_back(stringToSplit.substr(initialPos, pos - initialPos));
        initialPos = pos + delimiter.length();

        pos = stringToSplit.find(delimiter, initialPos);
    }

    // Add the last one
    splittedStrings->push_back(
            stringToSplit.substr(initialPos, std::min(pos, stringToSplit.length()) - initialPos + 1));

    return splittedStrings;

}

std::vector<PlannedMove> BoardIO::load_moves(bool player) {
    // TODO load_moves()
    return std::vector<PlannedMove>();
}

void BoardIO::store_game(Game &game) {
    // TODO store_game()
}

//
// Created by itamar on 2018-04-12.
//

#include <vector>
#include "Auxiliary.h"
#include "GamePiece.h"

#ifndef CS_TAU_C_PLUS_PLUS_FIRST_EXERCISE_GAME_H
#define CS_TAU_C_PLUS_PLUS_FIRST_EXERCISE_GAME_H

#endif //CS_TAU_C_PLUS_PLUS_FIRST_EXERCISE_GAME_H

class Cell {
    int row;
    int column;
};

enum GameResult {
    NONE, PLAYER_1_VICTORY, PLAYER_2_VICTORY, TIE
};

class PlannedMove {
    int from_r, from_c, to_r, to_c;
    bool has_joker_change;
    int joker_r, joker_c;
    GamePieceType new_joker_type;
};

class Game {
public:
    std::vector<std::vector<GamePiece *>> board;
    bool currentPlayer;
    GameResult gameResult;

    explicit Game() : board(M, std::vector<GamePiece *>(N, nullptr)), currentPlayer(true), gameResult(NONE) {}

    void make_move(GamePiece &movingPiece, Cell &destination);

};
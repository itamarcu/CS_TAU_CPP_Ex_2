//
// Created by itamar on 2018-04-12.
//

#ifndef CS_TAU_C_PLUS_PLUS_FIRST_EXERCISE_BOARD_H
#define CS_TAU_C_PLUS_PLUS_FIRST_EXERCISE_BOARD_H
#include <iostream>
#include <vector>
#include "GamePiece.h"

class Board
{

    public:
        explicit Board(const std::vector<std::vector<GamePiece*>> &board);
        void make_move(GamePiece& firstGamePiece,Cell& destination);

    private:
        std::vector<std::vector<GamePiece*>> board;
};

#endif //CS_TAU_C_PLUS_PLUS_FIRST_EXERCISE_BOARD_H

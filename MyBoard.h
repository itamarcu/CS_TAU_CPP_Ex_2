//
// Created by Daniel Meltzer on 22/05/2018.
//

#ifndef CS_TAU_CPP_EX_2_MYBOARD_H
#define CS_TAU_CPP_EX_2_MYBOARD_H


#include "Board.h"
#include "GamePiece.h"
#include "Auxiliary.h"

class MyBoard : public Board {
public:
    std::vector<std::vector<GamePiece *>> grid;
public:
    int getPlayer(const Point &pos) const override; // 1 for player 1's piece, 2 for 2, 0 if empty
    ~MyBoard() override;

    MyBoard() : grid(M, std::vector<GamePiece *>(N, nullptr)) {}
};


#endif //CS_TAU_CPP_EX_2_MYBOARD_H

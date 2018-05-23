//
// Created by Daniel Meltzer on 22/05/2018.
//

#include "MyBoard.h"
#include "Point.h"
/*
 * MyBoard
 */
int MyBoard::getPlayer(const Point &pos) const {
    GamePiece *piece = grid[pos.getX()][pos.getY()];
    if (piece == nullptr)
        return 0;
    return bool_to_player(piece->player);
}

MyBoard::~MyBoard() = default; // vector of vectors is freed on its own

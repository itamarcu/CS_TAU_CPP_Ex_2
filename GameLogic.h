//
// Created by itamar on 2018-04-12.
//

#ifndef CS_TAU_C_PLUS_PLUS_FIRST_EXERCISE_GAMELOGIC_H
#define CS_TAU_C_PLUS_PLUS_FIRST_EXERCISE_GAMELOGIC_H

#include "GamePiece.h"

enum MoveResult{
    movedPieceWon,movedPieceLost,tie

};

MoveResult move_piece_fight(GamePiece& pieceToMove,GamePiece& piecePreviouslyOccupyingSlot );
#endif //CS_TAU_C_PLUS_PLUS_FIRST_EXERCISE_GAMELOGIC_H

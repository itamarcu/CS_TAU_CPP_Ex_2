#ifndef CS_TAU_C_PLUS_PLUS_FIRST_EXERCISE_GAMELOGIC_H
#define CS_TAU_C_PLUS_PLUS_FIRST_EXERCISE_GAMELOGIC_H

#include "Classes.h"
#include "Game.h"
enum FightResult {
    attackerWon, defenderWon, bothPiecesLost
};
enum MoveResult{
    RegularMove,atePiece,wasEaten,tiedWithPiece,TriedToMoveEmptySpace,TriedToMoveUnMovablePiece,OutOfBorderMove,DefaultIllegalMove
};

/**
 * move a piece
 * @param game game to move the piece in
 * @param from cell to move from
 * @param to cell to move to
 * @return MoveResult case
 */
MoveResult move_piece_from_to(Game &game, Cell from, Cell to);

/**
 * fight between pieces if needed
 * @warning public because needed elsewhere
 * @param game game to play in
 * @param attacker attacker of fight
 * @param defender defender fight
 * @param position position the pieces fight in
 * @return MoveResult case
 */
MoveResult actually_fight(Game &game, GamePiece *attacker,
                    GamePiece *defender, Cell position);

#endif //CS_TAU_C_PLUS_PLUS_FIRST_EXERCISE_GAMELOGIC_H

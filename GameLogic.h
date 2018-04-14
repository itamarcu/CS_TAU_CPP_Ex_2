#ifndef CS_TAU_C_PLUS_PLUS_FIRST_EXERCISE_GAMELOGIC_H
#define CS_TAU_C_PLUS_PLUS_FIRST_EXERCISE_GAMELOGIC_H

#include "Classes.h"

enum FightResult {
    attackerWon, defenderWon, bothPiecesLost
};

FightResult simulate_fight(const GamePiece &attacker,
                           const GamePiece &defender);

void move_piece_from_to(Game &game, Cell from, Cell to);

void actually_fight(Game &game, GamePiece *attacker,
                    GamePiece *defender, Cell position);

#endif //CS_TAU_C_PLUS_PLUS_FIRST_EXERCISE_GAMELOGIC_H

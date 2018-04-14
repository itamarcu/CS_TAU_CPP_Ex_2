//
// Created by daniel meltzer on 13/04/2018.
//

#ifndef CS_TAU_C_PLUS_PLUS_FIRST_EXERCISE_GAMEPIECE_H
#define CS_TAU_C_PLUS_PLUS_FIRST_EXERCISE_GAMEPIECE_H
#define M 10  // Rows
#define N 10  // Columns
#define R 2  // Rocks
#define P 5  // Papers
#define S 1  // Scissors
#define B 2  // Bombs
#define J 2  // Jokers
#define F 1  // Flags
class Cell{
    int row;
    int column;
};
 enum GamePieceType{
   Rock,Paper,Scissors, Bomb, Flag
};

class GamePiece{
    Cell gamePieceCell;
    bool isJoker;
    GamePieceType gamePieceType;
};
#endif //CS_TAU_C_PLUS_PLUS_FIRST_EXERCISE_GAMEPIECE_H

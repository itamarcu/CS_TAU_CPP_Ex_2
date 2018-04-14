//
// Created by daniel meltzer on 13/04/2018.
//

#ifndef CS_TAU_C_PLUS_PLUS_FIRST_EXERCISE_GAMEPIECE_H
#define CS_TAU_C_PLUS_PLUS_FIRST_EXERCISE_GAMEPIECE_H


enum GamePieceType {
    None, // empty spaces are this type
    Rock, Paper, Scissors, Bomb, Flag //Jokers have a current type but also the boolean
};

class GamePiece {

public:
    GamePieceType type;
    bool isJoker;
    bool player;

    GamePiece() : type(None), isJoker(false), player(true) {};

    static GamePieceType type_from_char(char c);
};

#endif //CS_TAU_C_PLUS_PLUS_FIRST_EXERCISE_GAMEPIECE_H

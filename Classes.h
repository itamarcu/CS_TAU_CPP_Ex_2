#ifndef CS_TAU_C_PLUS_PLUS_FIRST_EXERCISE_CLASSES_H
#define CS_TAU_C_PLUS_PLUS_FIRST_EXERCISE_CLASSES_H

#include <vector>
#include "Auxiliary.h"


class Cell {
public:
    int row;
    int column;

    Cell(int r, int c) : row(r), column(c) {}
};

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

};

enum GameResult {
    NONE, PLAYER_1_VICTORY, PLAYER_2_VICTORY, TIE
};

class PlannedMove {
    Cell origin;
    Cell destination;
    bool has_joker_change;
    Cell joker_position;
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

GamePieceType type_from_char(char c);

#endif //CS_TAU_C_PLUS_PLUS_FIRST_EXERCISE_CLASSES_H

#ifndef CS_TAU_C_PLUS_PLUS_FIRST_EXERCISE_CLASSES_H
#define CS_TAU_C_PLUS_PLUS_FIRST_EXERCISE_CLASSES_H


#include <vector>
#include "Auxiliary.h"

/**
 * Cell that represents a position on board
 * @public row: row of cell
 * @public column: column of cell
 */
class Cell {
public:
    int row;
    int column;

    /**
     * constructor for Cell
     * @param cellsRow the cells row
     * @param cellsColumn the cells column
     */
    Cell(int cellsRow, int cellsColumn) : row(cellsRow), column(cellsColumn) {}
};

/**
 * game piece type according doesn't takes to account whether it's a joker
 */
enum GamePieceType {
    None, // empty spaces are this type
    Rock, Paper, Scissors, Bomb,//Jokers have a current type but also the boolean
    Flag // jokers can't be flags
};

class GamePiece {
public:
    GamePieceType type;
    bool isJoker;
    bool player;

    /**
     * initalize game piece
     * @param pieceType the type of piece
     * @param pieceIsJoker is the piece a joker - meaning it can change type
     * @param player - true if it's the first false if it's the second
     */
    explicit GamePiece(bool player, GamePieceType pieceType = None, bool pieceIsJoker = false) : player(player),
                                                                                                 type(pieceType),
                                                                                                 isJoker(pieceIsJoker) {}

    /**
     *
     * @return char representing type and player. Jokers give J always.
     */
    char to_char();
};

enum GameWinner {
    GAME_NOT_ENDED = 3,
    PLAYER_1_VICTORY = 1,
    PLAYER_2_VICTORY = 2,
    TIE = 0
};

class PlannedMove {
    // Fields
private:
    bool is_good_format;
    Cell origin;
    Cell destination;
    bool has_joker_changed;
    Cell joker_position;
    GamePieceType new_joker_type;

    //Constructors
public:
    //For invalid moves:
    explicit PlannedMove(bool format) : is_good_format(format), origin(0, 0),
                                        destination(0, 0), has_joker_changed(false),
                                        joker_position(0, 0), new_joker_type(None) {}

    //For non-joker moves:
    explicit PlannedMove(int r1, int c1, int r2, int c2)
            : is_good_format(true), origin(r1, c1),
              destination(r2, c2), has_joker_changed(false),
              joker_position(0, 0), new_joker_type(None) {}

    //For joker moves:
    explicit PlannedMove(int r1, int c1, int r2, int c2,
                         int jr, int jc, GamePieceType jtype)
            : is_good_format(true), origin(r1, c1),
              destination(r2, c2), has_joker_changed(true),
              joker_position(jr, jc), new_joker_type(jtype) {}

    //GETTERS
public:
    const Cell &getOrigin() const;

    const Cell &getDestination() const;

    bool isHas_joker_changed() const;

    const Cell &getJoker_position() const;

    GamePieceType getNew_joker_type() const;
};


GamePieceType type_from_char(char c);

#endif //CS_TAU_C_PLUS_PLUS_FIRST_EXERCISE_CLASSES_H

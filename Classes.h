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
    GamePiece(GamePieceType pieceType = None,bool pieceIsJoker = false,bool player) : type(pieceType), isJoker(pieceIsJoker), player(player) {};

};

enum GameResult {
    NONE, PLAYER_1_VICTORY, PLAYER_2_VICTORY, TIE
};

class PlannedMove {
    //GETTERS
public:
    const Cell &getOrigin() const;

    const Cell &getDestination() const;

    bool isHas_joker_changed() const;

    const Cell &getJoker_position() const;

    GamePieceType getNew_joker_type() const;

    //SETTERS
public:
    void setOrigin(const Cell &origin);

    void setDestination(const Cell &destination);

    void setHas_joker_changed(bool has_joker_changed);

    void setJoker_position(const Cell &joker_position);

    void setNew_joker_type(GamePieceType new_joker_type);


//Private ivars
private:
    Cell origin;
    Cell destination;
    bool has_joker_changed;
    Cell joker_position;
    GamePieceType new_joker_type;


};



GamePieceType type_from_char(char c);

#endif //CS_TAU_C_PLUS_PLUS_FIRST_EXERCISE_CLASSES_H

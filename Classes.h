#ifndef CS_TAU_CPP_RPS_CLASSES_H
#define CS_TAU_CPP_RPS_CLASSES_H


#include <vector>
#include "Auxiliary.h"
#include "Point.h"

class MyPoint : public Point {
public:
    int x;
    int y;

    MyPoint(int x, int y);

    ~MyPoint() override;

    explicit MyPoint(const Point &p) : x(p.getX()), y(p.getY()) {}

    int getX() const override;

    int getY() const override;
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
    bool player;
    GamePieceType type;
    bool isJoker;

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

    /**
     *
     * @return true if this unit can move (if it is not a flag or a bomb or a bomb-joker)
     */
    bool canMove();
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
    MyPoint origin;
    MyPoint destination;
    bool has_joker_changed;
    MyPoint joker_position;
    GamePieceType new_joker_type;

    //Constructors
public:
    //For invalid moves:
    explicit PlannedMove(bool format) : is_good_format(format), origin(0, 0),
                                        destination(0, 0), has_joker_changed(false),
                                        joker_position(0, 0), new_joker_type(None) {}

    //For non-joker moves:
    explicit PlannedMove(int x1, int y1, int x2, int y2)
            : is_good_format(true), origin(x1, y1),
              destination(x2, y2), has_joker_changed(false),
              joker_position(0, 0), new_joker_type(None) {}

    //For joker moves:
    explicit PlannedMove(int x1, int y1, int x2, int y2,
                         int jx, int jy, GamePieceType jtype)
            : is_good_format(true), origin(x1, y1),
              destination(x2, y2), has_joker_changed(true),
              joker_position(jx, jy), new_joker_type(jtype) {}

    //GETTERS
public:
    const Point &getOrigin() const;

    const Point &getDestination() const;

    bool isHas_joker_changed() const;

    const Point &getJoker_position() const;

    GamePieceType getNew_joker_type() const;
};


GamePieceType type_from_char(char c);

#endif //CS_TAU_CPP_RPS_CLASSES_H

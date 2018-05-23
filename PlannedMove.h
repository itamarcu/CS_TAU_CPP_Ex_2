//
// Created by Daniel Meltzer on 22/05/2018.
//

#ifndef CS_TAU_CPP_EX_2_PLANNEDMOVER_H
#define CS_TAU_CPP_EX_2_PLANNEDMOVER_H

#include "GamePiece.h"
#include "Point.h"
#include "MyPoint.h"

/**
 *
 */
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



#endif //CS_TAU_CPP_EX_2_PLANNEDMOVER_H
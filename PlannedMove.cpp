//
// Created by Daniel Meltzer on 22/05/2018.
//

#include "PlannedMove.h"
const Point &PlannedMove::getOrigin() const {
    return origin;
}

const Point &PlannedMove::getDestination() const {
    return destination;
}

bool PlannedMove::isHas_joker_changed() const {
    return has_joker_changed;
}

const Point &PlannedMove::getJoker_position() const {
    return joker_position;
}

GamePieceType PlannedMove::getNew_joker_type() const {
    return new_joker_type;
}

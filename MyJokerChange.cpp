//
// Created by Daniel Meltzer on 23/05/2018.
//

#include "MyJokerChange.h"

const Point &MyJokerChange::getJokerChangePosition() const {
    return positionChange;
}

char MyJokerChange::getJokerNewRep() const {
    return jokerRepresentation;
}

MyJokerChange::~MyJokerChange() = default;


MyJokerChange::MyJokerChange(const MyPoint &positionChange, char jokerRepresentation) : positionChange(
        positionChange), jokerRepresentation(jokerRepresentation) {}

MyJokerChange::MyJokerChange(const MyPoint &positionChange, GamePieceType jokerRepresentation) : positionChange(
        positionChange), jokerRepresentation(nonjoker_lowercase_type_from_char(jokerRepresentation)) {}

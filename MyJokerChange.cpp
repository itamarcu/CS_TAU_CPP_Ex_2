//
// Created by Daniel Meltzer on 23/05/2018.
//

#include "MyJokerChange.h"

const Point &MyJokerChange::getJokerChangePosition() const {
    return positionChange;
}

char MyJokerChange::getJokerNewRep() const {
    return 0;
}

MyJokerChange::~MyJokerChange() = default;



MyJokerChange::MyJokerChange(const MyPoint &positionChange, char jokerRepresentation) : positionChange(
        positionChange), newJokerRepresentation(jokerRepresentation) {

}

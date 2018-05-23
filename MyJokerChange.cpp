//
// Created by Daniel Meltzer on 23/05/2018.
//

#include "MyJokerChange.h"

const Point &MyJokerChange::getJokerChangePosition() const {
    return <#initializer#>;
}

char MyJokerChange::getJokerNewRep() const {
    return 0;
}

MyJokerChange::~MyJokerChange() {

}

MyJokerChange::MyJokerChange(const std::shared_ptr<Point> &positionChange, char newCharRepresentation) : positionChange(
        positionChange), newJokerRepresntation(newCharRepresentation) {}
